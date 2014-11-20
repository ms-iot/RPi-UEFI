/*
 * Copyright (C) 2008 Michael Brown <mbrown@fensystems.co.uk>.
 * Copyright (C) 2008 Mellanox Technologies Ltd.
 *
 * This program and the accompanying materials
 * are licensed and made available under the terms and conditions of the BSD License
 * which accompanies this distribution.  The full text of the license may be found at
 * http://opensource.org/licenses/bsd-license.php
 *
 * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 *
 **/

#include "hermon.h"

extern unsigned poll_verbosity;

extern VOID
Mellanox_Callback_GetReceiveData(VOID *PrivateData, VOID *Packet, UINT32 Length);

void WRITE_REG(struct hermon *hermon, unsigned int d, unsigned int *a)
{
  EFI_PCI_IO_PROTOCOL *pci = hermon->pci;
  DBG("WriteReg 0x%p 0x%x\n", a, (d));
  if (((UINT64)a & (UINT64)hermon->uar) == (UINT64)hermon->uar)
    pci->Mem.Write(pci, EfiPciIoWidthUint32, HERMON_PCI_UAR_BAR, (UINT64)a - (UINT64)hermon->uar, 1, &d);
  else if (((UINT64)a & (UINT64)hermon->config) == (UINT64)hermon->config) {
    pci->Mem.Write(pci, EfiPciIoWidthUint32, HERMON_PCI_CONFIG_BAR, (UINT64)a - (UINT64)hermon->config, 1, &d);
  }
  else
    DBG("Can't write to PCI mem: %p\n", a);
}

unsigned int READ_REG(struct hermon *hermon, unsigned int *a)
{
  EFI_PCI_IO_PROTOCOL *pci = hermon->pci;
	unsigned int d = 0;
	if (((UINT64)a & (UINT64)hermon->uar) == (UINT64)hermon->uar)
    pci->Mem.Read(pci, EfiPciIoWidthUint32, HERMON_PCI_UAR_BAR, (UINT64)a - (UINT64)hermon->uar, 1, &d);
	else if (((UINT64)a & (UINT64)hermon->config) == (UINT64)hermon->config) {
    pci->Mem.Read(pci, EfiPciIoWidthUint32, HERMON_PCI_CONFIG_BAR, (UINT64)a - (UINT64)hermon->config, 1, &d);
	}
  else
    DBG("Can't read PCI mem: %p\n", a);
	DBG("ReadReg 0x%p 0x%x\n", a, (d));
	return d;
}

/**
 * @file
 *
 * Mellanox ConnectX3 Infiniband HCA
 *
 */

/***************************************************************************
 *
 * Queue number allocation
 *
 ***************************************************************************
 */

/**
 * Allocate offsets within usage bitmask
 *
 * @v bits		Usage bitmask
 * @v bits_len		Length of usage bitmask
 * @v num_bits		Number of contiguous bits to allocate within bitmask
 * @ret bit		First free bit within bitmask, or negative error
 */
static int hermon_bitmask_alloc ( hermon_bitmask_t *bits,
				  unsigned int bits_len,
				  unsigned int num_bits ) {
	unsigned int bit = 0;
	hermon_bitmask_t mask = 1;
	unsigned int found = 0;

	/* Search bits for num_bits contiguous free bits */
	while ( bit < bits_len ) {
		if ( ( mask & *bits ) == 0 ) {
			if ( ++found == num_bits )
				goto found;
		} else {
			found = 0;
		}
		bit++;
		mask = ( mask << 1 ) | ( mask >> ( 8 * sizeof ( mask ) - 1 ) );
		if ( mask == 1 )
			bits++;
	}
	return -ENFILE;

 found:
	/* Mark bits as in-use */
	do {
		*bits |= mask;
		if ( mask == 1 )
			bits--;
		mask = ( mask >> 1 ) | ( mask << ( 8 * sizeof ( mask ) - 1 ) );
	} while ( --found );

	return ( bit - num_bits + 1 );
}

/**
 * Free offsets within usage bitmask
 *
 * @v bits		Usage bitmask
 * @v bit		Starting bit within bitmask
 * @v num_bits		Number of contiguous bits to free within bitmask
 */
static void hermon_bitmask_free ( hermon_bitmask_t *bits,
				  int bit, unsigned int num_bits ) {
	hermon_bitmask_t mask;

	for ( ; num_bits ; bit++, num_bits-- ) {
		mask = ( 1 << ( bit % ( 8 * sizeof ( mask ) ) ) );
		bits[ ( bit / ( 8 * sizeof ( mask ) ) ) ] &= ~mask;
	}
}

/***************************************************************************
 *
 * HCA commands
 *
 ***************************************************************************
 */

/**
 * Wait for ConnectX3 command completion
 *
 * @v hermon		ConnectX3 device
 * @v hcr		HCA command registers
 * @ret rc		Return status code
 */
static int hermon_cmd_wait ( struct hermon *hermon,
			     struct hermonprm_hca_command_register *hcr ) {
	unsigned int wait;

	for ( wait = HERMON_HCR_MAX_WAIT_MS ; wait ; wait-- ) {
		hcr->u.dwords[6] =
			READ_REG (hermon, hermon->config + HERMON_HCR_REG ( 6 ) );
		if ( ( MLX_GET ( hcr, go ) == 0 ) &&
		     ( MLX_GET ( hcr, t ) == hermon->toggle ) )
			return 0;
		mdelay ( 1 );
	}
	return -EBUSY;
}

/**
 * Return physical function for specific commands
 *
 * @v hermon		ConnectX3 device
 * @v opcode		HCA command opcode
 */
static u8 hermon_cmd_get_function ( struct hermon *hermon,
				    int opcode ) {
	switch ( opcode ) {
	case HERMON_HCR_SW2HW_EQ:
	case HERMON_HCR_SW2HW_CQ:
	case HERMON_HCR_RST2INIT_QP:
	case HERMON_HCR_INIT2RTR_QP:
	case HERMON_HCR_RTR2RTS_QP:
	case HERMON_HCR_SW2HW_MPT:
	case HERMON_HCR_2RST_QP:
	case HERMON_HCR_HW2SW_CQ:
	case HERMON_HCR_HW2SW_EQ:
		return hermon->physical_function;
		break;
	default:
		return 0;
	}

	return 0;
}

/**
 * Issue HCA command
 *
 * @v hermon		ConnectX3 device
 * @v command		Command opcode, flags and input/output lengths
 * @v op_mod		Opcode modifier (0 if no modifier applicable)
 * @v in		Input parameters
 * @v in_mod		Input modifier (0 if no modifier applicable)
 * @v out		Output parameters
 * @ret rc		Return status code
 */
static int hermon_cmd ( struct hermon *hermon, unsigned long command,
			unsigned int op_mod, const void *in,
			unsigned int in_mod, void *out ) {
	struct hermonprm_hca_command_register hcr;
	unsigned int	opcode	= HERMON_HCR_OPCODE ( command );
	size_t		in_len	= HERMON_HCR_IN_LEN ( command );
	size_t		out_len	= HERMON_HCR_OUT_LEN ( command );
	void		*in_buffer;
	void		*out_buffer;
	u8		physical_function;
	unsigned int	status;
	unsigned int	i;
	int		rc;

	assert ( in_len <= HERMON_MBOX_SIZE );
	assert ( out_len <= HERMON_MBOX_SIZE );

	DBGC2 ( hermon, "ConnectX3 %p command %02x in %x%s out %x%s\n",
		hermon, opcode, in_len,
		( ( command & HERMON_HCR_IN_MBOX ) ? L"(mbox)" : L"" ), out_len,
		( ( command & HERMON_HCR_OUT_MBOX ) ? L"(mbox)" : L"" ) );

	/* Check that HCR is free */
	if ( ( rc = hermon_cmd_wait ( hermon, &hcr ) ) != 0 ) {
		DBGC ( hermon, "ConnectX3 %p command interface locked\n",
		       hermon );
		return rc;
	}

	/* Flip HCR toggle */
	hermon->toggle = ( 1 - hermon->toggle );

	/* Get physical function */
	physical_function = hermon_cmd_get_function ( hermon, opcode );

	/* Prepare HCR */
	memset ( &hcr, 0, sizeof ( hcr ) );
	in_buffer = &hcr.u.dwords[0];
	if ( in_len && ( command & HERMON_HCR_IN_MBOX ) ) {
		memset ( hermon->mailbox_in, 0, HERMON_MBOX_SIZE );
		in_buffer = hermon->mailbox_in;
		MLX_FILL_H ( &hcr, 0, in_param_h, virt_to_bus ( in_buffer ) );
		MLX_FILL_1 ( &hcr, 1, in_param_l, virt_to_bus ( in_buffer ) |
			     physical_function );
	} else
		MLX_FILL_1 ( &hcr, 1, in_param_l, physical_function );
	memcpy ( in_buffer, in, in_len );
	MLX_FILL_1 ( &hcr, 2, input_modifier, in_mod );
	out_buffer = &hcr.u.dwords[3];
	if ( out_len && ( command & HERMON_HCR_OUT_MBOX ) ) {
		out_buffer = hermon->mailbox_out;
		MLX_FILL_H ( &hcr, 3, out_param_h,
			     virt_to_bus (  out_buffer ) );
		MLX_FILL_1 ( &hcr, 4, out_param_l,
			     virt_to_bus (  out_buffer ) );
	}
	MLX_FILL_4 ( &hcr, 6,
		     opcode, opcode,
		     opcode_modifier, op_mod,
		     go, 1,
		     t, hermon->toggle );
	DBGC ( hermon, "ConnectX3 %p issuing command %04x\n",
	       hermon, opcode );
	DBGC2_HDA ( hermon, virt_to_phys ( hermon->config + HERMON_HCR_BASE ),
		    &hcr, sizeof ( hcr ) );
	if ( in_len && ( command & HERMON_HCR_IN_MBOX ) ) {
		DBGC2 ( hermon, "Input mailbox:\n" );
		DBGC2_HDA ( hermon, virt_to_phys ( in_buffer ), in_buffer,
			    ( ( in_len < 512 ) ? in_len : 512 ) );
	}

	/* Issue command */
	for ( i = 0 ; i < ( sizeof ( hcr ) / sizeof ( hcr.u.dwords[0] ) ) ;
	      i++ ) {
		WRITE_REG (hermon, hcr.u.dwords[i],
			 hermon->config + HERMON_HCR_REG ( i ) );
		barrier();
	}

	/* Wait for command completion */
	if ( ( rc = hermon_cmd_wait ( hermon, &hcr ) ) != 0 ) {
		ERROR ("ConnectX3 %p timed out waiting for command:\n",
		       hermon );
		DBGC_HDA ( hermon,
			   virt_to_phys ( hermon->config + HERMON_HCR_BASE ),
			   &hcr, sizeof ( hcr ) );
		return rc;
	}

	/* Check command status */
	status = MLX_GET ( &hcr, status );
	if ( status != 0 ) {
	  ERROR ( "ConnectX3 %p command failed with status %02x:\n",
		       hermon, status );
		DBGC_HDA ( hermon,
			   virt_to_phys ( hermon->config + HERMON_HCR_BASE ),
			   &hcr, sizeof ( hcr ) );
		return -EIO;
	}

	/* Read output parameters, if any */
	hcr.u.dwords[3] = READ_REG (hermon, hermon->config + HERMON_HCR_REG ( 3 ) );
	hcr.u.dwords[4] = READ_REG (hermon, hermon->config + HERMON_HCR_REG ( 4 ) );
	memcpy ( out, out_buffer, out_len );
	if ( out_len ) {
		DBGC2 ( hermon, "Output%s:\n",
			( command & HERMON_HCR_OUT_MBOX ) ? L" mailbox" : L"" );
		DBGC2_HDA ( hermon, virt_to_phys ( out_buffer ), out_buffer,
			    ( ( out_len < 512 ) ? out_len : 512 ) );
	}

	return 0;
}

static inline int
hermon_cmd_query_dev_cap ( struct hermon *hermon,
			   struct hermonprm_query_dev_cap *dev_cap ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_OUT_CMD ( HERMON_HCR_QUERY_DEV_CAP,
						 1, sizeof ( *dev_cap ) ),
			    0, NULL, 0, dev_cap );
}

static inline int
hermon_cmd_query_fw ( struct hermon *hermon, struct hermonprm_query_fw *fw ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_OUT_CMD ( HERMON_HCR_QUERY_FW,
						 1, sizeof ( *fw ) ),
			    0, NULL, 0, fw );
}

static inline int
hermon_cmd_init_hca ( struct hermon *hermon,
		      const struct hermonprm_init_hca *init_hca ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_IN_CMD ( HERMON_HCR_INIT_HCA,
						1, sizeof ( *init_hca ) ),
			    0, init_hca, 0, NULL );
}

static inline int
hermon_cmd_close_hca ( struct hermon *hermon ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_VOID_CMD ( HERMON_HCR_CLOSE_HCA ),
			    0, NULL, 0, NULL );
}

static inline int
hermon_cmd_init_port ( struct hermon *hermon, unsigned int port ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_VOID_CMD ( HERMON_HCR_INIT_PORT ),
			    0, NULL, port, NULL );
}

static inline int
hermon_cmd_close_port ( struct hermon *hermon, unsigned int port ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_VOID_CMD ( HERMON_HCR_CLOSE_PORT ),
			    0, NULL, port, NULL );
}

static inline int
hermon_cmd_set_port ( struct hermon *hermon, int is_ethernet,
		      unsigned int port_selector,
		      const union hermonprm_set_port *set_port ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_IN_CMD ( HERMON_HCR_SET_PORT,
						1, sizeof ( *set_port ) ),
			    is_ethernet, set_port, port_selector, NULL );
}

static inline int
hermon_cmd_sw2hw_mpt ( struct hermon *hermon, unsigned int index,
		       const struct hermonprm_mpt *mpt ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_IN_CMD ( HERMON_HCR_SW2HW_MPT,
						1, sizeof ( *mpt ) ),
			    0, mpt, index, NULL );
}

static inline int
hermon_cmd_write_mtt ( struct hermon *hermon,
		       const struct hermonprm_write_mtt *write_mtt ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_IN_CMD ( HERMON_HCR_WRITE_MTT,
						1, sizeof ( *write_mtt ) ),
			    0, write_mtt, 1, NULL );
}

static inline int
hermon_cmd_map_eq ( struct hermon *hermon, unsigned long index_map,
		    const struct hermonprm_event_mask *mask ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_IN_CMD ( HERMON_HCR_MAP_EQ,
						0, sizeof ( *mask ) ),
			    0, mask, index_map, NULL );
}

static inline int
hermon_cmd_sw2hw_eq ( struct hermon *hermon, unsigned int index,
		      const struct hermonprm_eqc *eqctx ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_IN_CMD ( HERMON_HCR_SW2HW_EQ,
						1, sizeof ( *eqctx ) ),
			    0, eqctx, index, NULL );
}

static inline int
hermon_cmd_hw2sw_eq ( struct hermon *hermon, unsigned int index,
		      struct hermonprm_eqc *eqctx ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_OUT_CMD ( HERMON_HCR_HW2SW_EQ,
						 1, sizeof ( *eqctx ) ),
			    1, NULL, index, eqctx );
}

static inline int
hermon_cmd_query_eq ( struct hermon *hermon, unsigned int index,
		      struct hermonprm_eqc *eqctx ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_OUT_CMD ( HERMON_HCR_QUERY_EQ,
						 1, sizeof ( *eqctx ) ),
			    0, NULL, index, eqctx );
}

static inline int
hermon_cmd_sw2hw_cq ( struct hermon *hermon, unsigned long cqn,
		      const struct hermonprm_completion_queue_context *cqctx ){
	return hermon_cmd ( hermon,
			    HERMON_HCR_IN_CMD ( HERMON_HCR_SW2HW_CQ,
						1, sizeof ( *cqctx ) ),
			    0, cqctx, cqn, NULL );
}

static inline int
hermon_cmd_hw2sw_cq ( struct hermon *hermon, unsigned long cqn,
		      struct hermonprm_completion_queue_context *cqctx ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_OUT_CMD ( HERMON_HCR_HW2SW_CQ,
						 1, sizeof ( *cqctx ) ),
			    0, NULL, cqn, cqctx );
}

static inline int
hermon_cmd_query_cq ( struct hermon *hermon, unsigned long cqn,
		      struct hermonprm_completion_queue_context *cqctx ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_OUT_CMD ( HERMON_HCR_QUERY_CQ,
						 1, sizeof ( *cqctx ) ),
			    0, NULL, cqn, cqctx );
}

static inline int
hermon_cmd_rst2init_qp ( struct hermon *hermon, unsigned long qpn,
			 const struct hermonprm_qp_ee_state_transitions *ctx ){
	return hermon_cmd ( hermon,
			    HERMON_HCR_IN_CMD ( HERMON_HCR_RST2INIT_QP,
						1, sizeof ( *ctx ) ),
			    0, ctx, qpn, NULL );
}

static inline int
hermon_cmd_init2rtr_qp ( struct hermon *hermon, unsigned long qpn,
			 const struct hermonprm_qp_ee_state_transitions *ctx ){
	return hermon_cmd ( hermon,
			    HERMON_HCR_IN_CMD ( HERMON_HCR_INIT2RTR_QP,
						1, sizeof ( *ctx ) ),
			    0, ctx, qpn, NULL );
}

static inline int
hermon_cmd_rtr2rts_qp ( struct hermon *hermon, unsigned long qpn,
			const struct hermonprm_qp_ee_state_transitions *ctx ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_IN_CMD ( HERMON_HCR_RTR2RTS_QP,
						1, sizeof ( *ctx ) ),
			    0, ctx, qpn, NULL );
}

static inline int
hermon_cmd_rts2rts_qp ( struct hermon *hermon, unsigned long qpn,
			const struct hermonprm_qp_ee_state_transitions *ctx ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_IN_CMD ( HERMON_HCR_RTS2RTS_QP,
						1, sizeof ( *ctx ) ),
			    0, ctx, qpn, NULL );
}

static inline int
hermon_cmd_2rst_qp ( struct hermon *hermon, unsigned long qpn ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_VOID_CMD ( HERMON_HCR_2RST_QP ),
			    0x03, NULL, qpn, NULL );
}

static inline int
hermon_cmd_query_qp ( struct hermon *hermon, unsigned long qpn,
		      struct hermonprm_qp_ee_state_transitions *ctx ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_OUT_CMD ( HERMON_HCR_QUERY_QP,
						 1, sizeof ( *ctx ) ),
			    0, NULL, qpn, ctx );
}

static inline int
hermon_cmd_conf_special_qp ( struct hermon *hermon, unsigned int internal_qps __unused,
			     unsigned long base_qpn ) {
	return hermon_cmd ( hermon, 0x0023, 0x01, NULL, base_qpn, NULL );
}

static inline int
hermon_cmd_mad_ifc ( struct hermon *hermon, unsigned int port,
		     union hermonprm_mad *mad ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_INOUT_CMD ( HERMON_HCR_MAD_IFC,
						   1, sizeof ( *mad ),
						   1, sizeof ( *mad ) ),
			    0x03, mad, port, mad );
}

static inline int
hermon_cmd_read_mcg ( struct hermon *hermon, unsigned int index,
		      struct hermonprm_mcg_entry *mcg ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_OUT_CMD ( HERMON_HCR_READ_MCG,
						 1, sizeof ( *mcg ) ),
			    0, NULL, index, mcg );
}

static inline int
hermon_cmd_write_mcg ( struct hermon *hermon, unsigned int index,
		       const struct hermonprm_mcg_entry *mcg ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_IN_CMD ( HERMON_HCR_WRITE_MCG,
						1, sizeof ( *mcg ) ),
			    0, mcg, index, NULL );
}

static inline int
hermon_cmd_mgid_hash ( struct hermon *hermon, const union ib_gid *gid,
		       struct hermonprm_mgm_hash *hash, u8 protocol ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_INOUT_CMD ( HERMON_HCR_MGID_HASH,
						   1, sizeof ( *gid ),
						   0, sizeof ( *hash ) ),
			    protocol, gid, 0, hash );
}

static inline int
hermon_cmd_mod_stat_cfg ( struct hermon *hermon, unsigned int mode,
			  unsigned int input_mod,
			  struct hermonprm_scalar_parameter *portion ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_INOUT_CMD ( HERMON_HCR_MOD_STAT_CFG,
						   0, sizeof ( *portion ),
						   0, sizeof ( *portion ) ),
			    mode, portion, input_mod, portion );
}

static inline int
hermon_cmd_query_port ( struct hermon *hermon, unsigned int port,
			struct hermonprm_query_port_cap *query_port ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_OUT_CMD ( HERMON_HCR_QUERY_PORT,
						 1, sizeof ( *query_port ) ),
			    0, NULL, port, query_port );
}

static inline int
hermon_cmd_sense_port ( struct hermon *hermon, unsigned int port,
			struct hermonprm_sense_port *port_type ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_OUT_CMD ( HERMON_HCR_SENSE_PORT,
						 0, sizeof ( *port_type ) ),
			    0, NULL, port, port_type );
}

static inline int
hermon_cmd_run_fw ( struct hermon *hermon ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_VOID_CMD ( HERMON_HCR_RUN_FW ),
			    0, NULL, 0, NULL );
}

static inline int
hermon_cmd_unmap_icm ( struct hermon *hermon, unsigned int page_count,
		       const struct hermonprm_scalar_parameter *offset ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_IN_CMD ( HERMON_HCR_UNMAP_ICM,
						0, sizeof ( *offset ) ),
			    0, offset, page_count, NULL );
}

static inline int
hermon_cmd_map_icm ( struct hermon *hermon,
		     const struct hermonprm_virtual_physical_mapping *map ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_IN_CMD ( HERMON_HCR_MAP_ICM,
						1, sizeof ( *map ) ),
			    0, map, 1, NULL );
}

static inline int
hermon_cmd_unmap_icm_aux ( struct hermon *hermon ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_VOID_CMD ( HERMON_HCR_UNMAP_ICM_AUX ),
			    0, NULL, 0, NULL );
}

static inline int
hermon_cmd_map_icm_aux ( struct hermon *hermon,
		       const struct hermonprm_virtual_physical_mapping *map ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_IN_CMD ( HERMON_HCR_MAP_ICM_AUX,
						1, sizeof ( *map ) ),
			    0, map, 1, NULL );
}

static inline int
hermon_cmd_set_icm_size ( struct hermon *hermon,
			  const struct hermonprm_scalar_parameter *icm_size,
			  struct hermonprm_scalar_parameter *icm_aux_size ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_INOUT_CMD ( HERMON_HCR_SET_ICM_SIZE,
						   0, sizeof ( *icm_size ),
						   0, sizeof (*icm_aux_size) ),
			    0, icm_size, 0, icm_aux_size );
}

static inline int
hermon_cmd_unmap_fa ( struct hermon *hermon ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_VOID_CMD ( HERMON_HCR_UNMAP_FA ),
			    0, NULL, 0, NULL );
}

static inline int
hermon_cmd_map_fa ( struct hermon *hermon,
		    const struct hermonprm_virtual_physical_mapping *map ) {
  return hermon_cmd ( hermon,
	                    HERMON_HCR_IN_CMD ( HERMON_HCR_MAP_FA,
	                                        1, sizeof ( *map ) ),
                      0, map, 1, NULL );
}

static inline int
hermon_cmd_get_op_req ( struct hermon *hermon, unsigned int request_type,
			unsigned int report_status,
			struct hermonprm_get_op_req *get_op_req ) {
	return hermon_cmd ( hermon,
			    HERMON_HCR_OUT_CMD ( HERMON_GET_OP_REQ,
						1, sizeof ( *get_op_req ) ),
			    request_type, NULL, report_status, get_op_req );
}

static inline int
hermon_cmd_register_access ( struct hermon *hermon,
			struct hermonprm_register_access *register_access ) {
	return hermon_cmd ( hermon,
				    HERMON_HCR_INOUT_CMD ( HERMON_HCR_REGISTER_ACCESS,
							   1, sizeof ( *register_access ),
							   1, sizeof ( *register_access ) ),
				    0, register_access, 0, register_access );
}


/***************************************************************************
 *
 * Memory translation table operations
 *
 ***************************************************************************
 */

/**
 * Allocate MTT entries
 *
 * @v hermon		ConnectX3 device
 * @v memory		Memory to map into MTT
 * @v len		Length of memory to map
 * @v mtt		MTT descriptor to fill in
 * @ret rc		Return status code
 */
static int hermon_alloc_mtt ( struct hermon *hermon,
			      void *memory, size_t len,
			      struct hermon_mtt *mtt ) {
	struct hermonprm_write_mtt write_mtt;
	physaddr_t start;
	physaddr_t addr;
	unsigned int page_offset;
	unsigned int num_pages;
	int mtt_offset;
	unsigned int mtt_base_addr;
	unsigned int i;
	int rc;

	/* Find available MTT entries */
	start = virt_to_phys ( memory );
	page_offset = ( start & ( HERMON_PAGE_SIZE - 1 ) );
	start -= page_offset;
	len += page_offset;
	DBGC ( hermon, "hermon_alloc_mtt : %lx->%lx\n",virt_to_phys ( memory ), start);
	num_pages = ( ( len + HERMON_PAGE_SIZE - 1 ) / HERMON_PAGE_SIZE );
	mtt_offset = hermon_bitmask_alloc ( hermon->mtt_inuse, HERMON_MAX_MTTS,
					    num_pages );
	if ( mtt_offset < 0 ) {
		ERROR ( "ConnectX3 %p could not allocate %d MTT entries\n",
		       hermon, num_pages );
		rc = mtt_offset;
		goto err_mtt_offset;
	}
	mtt_base_addr = ( ( hermon->cap.reserved_mtts + mtt_offset ) *
			  hermon->cap.mtt_entry_size );
	addr = start;

	/* Fill in MTT structure */
	mtt->mtt_offset = mtt_offset;
	mtt->num_pages = num_pages;
	mtt->mtt_base_addr = mtt_base_addr;
	mtt->page_offset = page_offset;

	/* Construct and issue WRITE_MTT commands */
	for ( i = 0 ; i < num_pages ; i++ ) {
		memset ( &write_mtt, 0, sizeof ( write_mtt ) );
		MLX_FILL_1 ( &write_mtt.mtt_base_addr, 1,
			     value, mtt_base_addr );
		MLX_FILL_H ( &write_mtt.mtt, 0, ptag_h, addr );
		MLX_FILL_2 ( &write_mtt.mtt, 1,
			     p, 1,
			     ptag_l, ( addr >> 3 ) );
		if ( ( rc = hermon_cmd_write_mtt ( hermon,
						   &write_mtt ) ) != 0 ) {
		  ERROR ("ConnectX3 %p could not write MTT at %x\n",
			       hermon, mtt_base_addr );
			goto err_write_mtt;
		}
		addr += HERMON_PAGE_SIZE;
		mtt_base_addr += hermon->cap.mtt_entry_size;
	}

	DBGC ( hermon, "ConnectX3 %p MTT entries [%x,%x] for "
	       "[%08lx,%08lx,%08lx,%08lx)\n", hermon, mtt->mtt_offset,
	       ( mtt->mtt_offset + mtt->num_pages - 1 ), start,
	       ( start + page_offset ), ( start + len ), addr );

	return 0;

 err_write_mtt:
	hermon_bitmask_free ( hermon->mtt_inuse, mtt_offset, num_pages );
 err_mtt_offset:
	return rc;
}

/**
 * Free MTT entries
 *
 * @v hermon		ConnectX3 device
 * @v mtt		MTT descriptor
 */
static void hermon_free_mtt ( struct hermon *hermon,
			      struct hermon_mtt *mtt ) {

	DBGC ( hermon, "ConnectX3 %p MTT entries [%x,%x] freed\n",
	       hermon, mtt->mtt_offset,
	       ( mtt->mtt_offset + mtt->num_pages - 1 ) );
	hermon_bitmask_free ( hermon->mtt_inuse, mtt->mtt_offset,
			      mtt->num_pages );
}

/***************************************************************************
 *
 * Static configuration operations
 *
 ***************************************************************************
 */

/**
 * Calculate offset within static configuration
 *
 * @v field		Field
 * @ret offset		Offset
 */
#define HERMON_MOD_STAT_CFG_OFFSET( field )				     \
	( ( MLX_BIT_OFFSET ( struct hermonprm_mod_stat_cfg_st, field ) / 8 ) \
	  & ~( sizeof ( struct hermonprm_scalar_parameter ) - 1 ) )

/**
 * Query or modify static configuration
 *
 * @v hermon		ConnectX3 device
 * @v port		Port
 * @v mode		Command mode
 * @v offset		Offset within static configuration
 * @v stat_cfg		Static configuration
 * @ret rc		Return status code
 */
static int hermon_mod_stat_cfg ( struct hermon *hermon, unsigned int mport,
				 unsigned int mode, unsigned int offset,
				 unsigned int physical_function, unsigned int setup_mode,
				 struct hermonprm_mod_stat_cfg *stat_cfg ) {
	struct hermonprm_scalar_parameter *portion =
		( ( void * ) &stat_cfg->u.bytes[offset] );
	struct hermonprm_mod_stat_cfg_input_mod mod;
	int rc;

	/* Construct input modifier */
	memset ( &mod, 0, sizeof ( mod ) );
	MLX_FILL_4 ( &mod, 0,
		     portnum, mport,
		     offset, offset,
		     physical_function, physical_function,
		     setup_mode, setup_mode );

	/* Sanity check */
	assert ( ( offset % sizeof ( *portion ) ) == 0 );

	/* Issue command */
	if ( ( rc = hermon_cmd_mod_stat_cfg ( hermon, mode,
					      be32_to_cpu ( mod.u.dwords[0] ),
					      portion ) ) != 0 )
		return rc;

	return 0;
}

/***************************************************************************
 *
 * MAD operations
 *
 ***************************************************************************
 */

/**
 * Issue management datagram
 *
 * @v ibdev		Infiniband device
 * @v mad		Management datagram
 * @ret rc		Return status code
 */
static int hermon_mad ( struct ib_device *ibdev, union ib_mad *mad ) {
  struct hermon *hermon = ib_get_drvdata ( ibdev );
	union hermonprm_mad mad_ifc;
	int rc;

	assert ( sizeof ( *mad ) == sizeof ( mad_ifc.mad ) );

	/* Copy in request packet */
	memcpy ( &mad_ifc.mad, mad, sizeof ( mad_ifc.mad ) );

	/* Issue MAD */
	if ( ( rc = hermon_cmd_mad_ifc ( hermon, ibdev->port,
					 &mad_ifc ) ) != 0 ) {
		ERROR ( "ConnectX3 %p port %d could not issue MAD IFC: "
		       "%s\n", hermon, ibdev->port, strerror ( rc ) );
		return rc;
	}

	/* Copy out reply packet */
	memcpy ( mad, &mad_ifc.mad, sizeof ( *mad ) );

	if ( mad->hdr.status != 0 ) {
		DBGC ( hermon, "ConnectX3 %p port %d MAD IFC status %04x\n",
		       hermon, ibdev->port, ntohs ( mad->hdr.status ) );
		return -EIO;
	}
	return 0;
}

/***************************************************************************
 *
 * Completion queue operations
 *
 ***************************************************************************
 */

/**
 * Dump completion queue context (for debugging only)
 *
 * @v hermon		ConnectX3 device
 * @v cq		Completion queue
 * @ret rc		Return status code
 */
static __attribute__ (( unused )) int
hermon_dump_cqctx ( struct hermon *hermon, struct ib_completion_queue *cq ) {
	struct hermonprm_completion_queue_context cqctx;
	int rc;

	memset ( &cqctx, 0, sizeof ( cqctx ) );
	if ( ( rc = hermon_cmd_query_cq ( hermon, cq->cqn, &cqctx ) ) != 0 ) {
		ERROR ( "ConnectX3 %p CQN %lx QUERY_CQ failed: %s\n",
		       hermon, cq->cqn, strerror ( rc ) );
		return rc;
	}
	DBGC ( hermon, "ConnectX3 %p CQN %lx context:\n", hermon, cq->cqn );
	DBGC_HDA ( hermon, 0, &cqctx, sizeof ( cqctx ) );

	return 0;
}

/**
 * Create completion queue
 *
 * @v ibdev		Infiniband device
 * @v cq		Completion queue
 * @ret rc		Return status code
 */
static int hermon_create_cq ( struct ib_device *ibdev,
			      struct ib_completion_queue *cq ) {
	struct hermon *hermon = ib_get_drvdata ( ibdev );
	struct hermon_completion_queue *hermon_cq;
	struct hermonprm_completion_queue_context cqctx;
	int cqn_offset;
	unsigned int i;
	int rc;

	/* Find a free completion queue number */
	cqn_offset = hermon_bitmask_alloc ( hermon->cq_inuse,
					    HERMON_MAX_CQS, 1 );
	if ( cqn_offset < 0 ) {
		DBGC ( hermon, "ConnectX3 %p out of completion queues\n",
		       hermon );
		rc = cqn_offset;
		goto err_cqn_offset;
	}
	cq->cqn = ( hermon->cap.reserved_cqs + cqn_offset );

	/* Allocate control structures */
	hermon_cq = zalloc ( sizeof ( *hermon_cq ) );
	if ( ! hermon_cq ) {
		rc = -ENOMEM;
		goto err_hermon_cq;
	}

	/* Allocate doorbell */
	hermon_cq->doorbell = malloc_dma ( sizeof ( hermon_cq->doorbell[0] ),
					   sizeof ( hermon_cq->doorbell[0] ) );
	if ( ! hermon_cq->doorbell ) {
		rc = -ENOMEM;
		goto err_doorbell;
	}
	memset ( hermon_cq->doorbell, 0, sizeof ( hermon_cq->doorbell[0] ) );

	/* Allocate completion queue itself */
	hermon_cq->cqe_size = ( cq->num_cqes * sizeof ( hermon_cq->cqe[0] ) );
	hermon_cq->cqe = malloc_dma ( hermon_cq->cqe_size,
				      sizeof ( hermon_cq->cqe[0] ) );
	if ( ! hermon_cq->cqe ) {
		rc = -ENOMEM;
		goto err_cqe;
	}
	memset ( hermon_cq->cqe, 0, hermon_cq->cqe_size );
	for ( i = 0 ; i < cq->num_cqes ; i++ ) {
		MLX_FILL_1 ( &hermon_cq->cqe[i].normal, 7, owner, 1 );
	}
	barrier();

	/* Allocate MTT entries */
	if ( ( rc = hermon_alloc_mtt ( hermon, hermon_cq->cqe,
				       hermon_cq->cqe_size,
				       &hermon_cq->mtt ) ) != 0 )
		goto err_alloc_mtt;

	/* Hand queue over to hardware */
	memset ( &cqctx, 0, sizeof ( cqctx ) );
	MLX_FILL_1 ( &cqctx, 0, st, 0xa /* "Event fired" */ );
	MLX_FILL_1 ( &cqctx, 2,
		     page_offset, ( hermon_cq->mtt.page_offset >> 5 ) );
	MLX_FILL_2 ( &cqctx, 3,
		     usr_page, HERMON_UAR_NON_EQ_PAGE,
		     log_cq_size, fls ( cq->num_cqes - 1 ) );
	MLX_FILL_1 ( &cqctx, 5, c_eqn, hermon->eq.eqn );
	MLX_FILL_H ( &cqctx, 6, mtt_base_addr_h,
		     hermon_cq->mtt.mtt_base_addr );
	MLX_FILL_1 ( &cqctx, 7, mtt_base_addr_l,
		     ( hermon_cq->mtt.mtt_base_addr >> 3 ) );
	MLX_FILL_H ( &cqctx, 14, db_record_addr_h,
		     virt_to_phys ( hermon_cq->doorbell ) );
	MLX_FILL_1 ( &cqctx, 15, db_record_addr_l,
		     ( virt_to_phys ( hermon_cq->doorbell ) >> 3 ) );
	if ( ( rc = hermon_cmd_sw2hw_cq ( hermon, cq->cqn, &cqctx ) ) != 0 ) {
		ERROR ( "ConnectX3 %p CQN %lx SW2HW_CQ failed: %s\n",
		       hermon, cq->cqn, strerror ( rc ) );
		goto err_sw2hw_cq;
	}

	DBGC ( hermon, "ConnectX3 %p CQN %lx ring [%08lx,%08lx), doorbell "
	       "%08lx\n", hermon, cq->cqn, virt_to_phys ( hermon_cq->cqe ),
	       ( virt_to_phys ( hermon_cq->cqe ) + hermon_cq->cqe_size ),
	       virt_to_phys ( hermon_cq->doorbell ));
	ib_cq_set_drvdata ( cq, hermon_cq );
	return 0;

 err_sw2hw_cq:
	hermon_free_mtt ( hermon, &hermon_cq->mtt );
 err_alloc_mtt:
	free_dma ( hermon_cq->cqe, hermon_cq->cqe_size );
 err_cqe:
	free_dma ( hermon_cq->doorbell, sizeof ( hermon_cq->doorbell[0] ) );
 err_doorbell:
	free ( hermon_cq );
 err_hermon_cq:
	hermon_bitmask_free ( hermon->cq_inuse, cqn_offset, 1 );
 err_cqn_offset:
	return rc;
}

/**
 * Destroy completion queue
 *
 * @v ibdev		Infiniband device
 * @v cq		Completion queue
 */
static void hermon_destroy_cq ( struct ib_device *ibdev,
				struct ib_completion_queue *cq ) {
	struct hermon *hermon = ib_get_drvdata ( ibdev );
	struct hermon_completion_queue *hermon_cq = ib_cq_get_drvdata ( cq );
	struct hermonprm_completion_queue_context cqctx;
	int cqn_offset;
	int rc;

	/* Take ownership back from hardware */
	if ( ( rc = hermon_cmd_hw2sw_cq ( hermon, cq->cqn, &cqctx ) ) != 0 ) {
		ERROR ( "ConnectX3 %p CQN %lx FATAL HW2SW_CQ failed: "
		       "%s\n", hermon, cq->cqn, strerror ( rc ) );
		/* Leak memory and return; at least we avoid corruption */
		return;
	}

	/* Free MTT entries */
	hermon_free_mtt ( hermon, &hermon_cq->mtt );

	/* Free memory */
	free_dma ( hermon_cq->cqe, hermon_cq->cqe_size );
	free_dma ( hermon_cq->doorbell, sizeof ( hermon_cq->doorbell[0] ) );
	free ( hermon_cq );

	/* Mark queue number as free */
	cqn_offset = ( cq->cqn - hermon->cap.reserved_cqs );
	hermon_bitmask_free ( hermon->cq_inuse, cqn_offset, 1 );

	ib_cq_set_drvdata ( cq, NULL );
}

/***************************************************************************
 *
 * Queue pair operations
 *
 ***************************************************************************
 */

/**
 * Assign queue pair number
 *
 * @v ibdev		Infiniband device
 * @v qp		Queue pair
 * @ret rc		Return status code
 */
static int hermon_alloc_qpn ( struct ib_device *ibdev,
			      struct ib_queue_pair *qp ) {
	struct hermon *hermon = ib_get_drvdata ( ibdev );
	unsigned int port_offset;
	int qpn_offset;

	/* Calculate queue pair number */
	port_offset = ( ibdev->port - HERMON_PORT_BASE );

	switch ( qp->type ) {
	case IB_QPT_SMI:
		qp->qpn = ( hermon->special_qpn_base + port_offset );
		return 0;
	case IB_QPT_GSI:
		qp->qpn = ( hermon->special_qpn_base + 2 + port_offset );
		return 0;
	case IB_QPT_UD:
	case IB_QPT_RC:
	case IB_QPT_ETH:
		/* Find a free queue pair number */
		qpn_offset = hermon_bitmask_alloc ( hermon->qp_inuse,
						    HERMON_MAX_QPS, 1 );
		if ( qpn_offset < 0 ) {
			DBGC ( hermon, "ConnectX3 %p out of queue pairs\n",
			       hermon );
			return qpn_offset;
		}
		qp->qpn = ( ( random() & HERMON_QPN_RANDOM_MASK ) |
			    ( hermon->qpn_base + qpn_offset ) );
		return 0;
	default:
		ERROR ( "ConnectX3 %p unsupported QP type %d\n",
		       hermon, qp->type );
		return -ENOTSUP;
	}
}

/**
 * Free queue pair number
 *
 * @v ibdev		Infiniband device
 * @v qp		Queue pair
 */
static void hermon_free_qpn ( struct ib_device *ibdev,
			      struct ib_queue_pair *qp ) {
	struct hermon *hermon = ib_get_drvdata ( ibdev );
	int qpn_offset;

	qpn_offset = ( ( qp->qpn & ~HERMON_QPN_RANDOM_MASK )
		       - hermon->qpn_base );
	if ( qpn_offset >= 0 )
		hermon_bitmask_free ( hermon->qp_inuse, qpn_offset, 1 );
}

/**
 * Calculate transmission rate
 *
 * @v av		Address vector
 * @ret hermon_rate	ConnectX3 rate
 */
static unsigned int hermon_rate ( struct ib_address_vector *av ) {
	return ( ( ( av->rate >= IB_RATE_2_5 ) && ( av->rate <= IB_RATE_120 ) )
		 ? ( av->rate + 5 ) : 0 );
}

/**
 * Calculate schedule queue
 *
 * @v ibdev		Infiniband device
 * @v qp		Queue pair
 * @ret sched_queue	Schedule queue
 */
static unsigned int hermon_sched_queue ( struct ib_device *ibdev,
					 struct ib_queue_pair *qp ) {
	return ( ( ( qp->type == IB_QPT_SMI ) ?
		   HERMON_SCHED_QP0 : HERMON_SCHED_DEFAULT ) |
		 ( ( ibdev->port - 1 ) << 6 ) );
}

/** Queue pair transport service type map */
static uint8_t hermon_qp_st[] = {
	[IB_QPT_SMI] = HERMON_ST_MLX,
	[IB_QPT_GSI] = HERMON_ST_MLX,
	[IB_QPT_UD] = HERMON_ST_UD,
	[IB_QPT_RC] = HERMON_ST_RC,
	[IB_QPT_ETH] = HERMON_ST_MLX,
};

/**
 * Dump queue pair context (for debugging only)
 *
 * @v hermon		ConnectX3 device
 * @v qp		Queue pair
 * @ret rc		Return status code
 */
static __attribute__ (( unused )) int
hermon_dump_qpctx ( struct hermon *hermon, struct ib_queue_pair *qp ) {
	struct hermonprm_qp_ee_state_transitions qpctx;
	int rc;

	memset ( &qpctx, 0, sizeof ( qpctx ) );
	if ( ( rc = hermon_cmd_query_qp ( hermon, qp->qpn, &qpctx ) ) != 0 ) {
		ERROR ( "ConnectX3 %p QPN %lx QUERY_QP failed: %s\n",
		       hermon, qp->qpn, strerror ( rc ) );
		return rc;
	}
	DBGC ( hermon, "ConnectX3 %p QPN %lx context:\n", hermon, qp->qpn );
	DBGC_HDA ( hermon, 0, &qpctx.u.dwords[2], ( sizeof ( qpctx ) - 8 ) );

	return 0;
}

/**
 * Create queue pair
 *
 * @v ibdev		Infiniband device
 * @v qp		Queue pair
 * @ret rc		Return status code
 */
static int hermon_create_qp ( struct ib_device *ibdev,
			      struct ib_queue_pair *qp ) {
	struct hermon *hermon = ib_get_drvdata ( ibdev );
	struct hermon_queue_pair *hermon_qp;
	struct hermonprm_qp_ee_state_transitions qpctx;
	int rc;

	/* Calculate queue pair number */
	if ( ( rc = hermon_alloc_qpn ( ibdev, qp ) ) != 0 )
		goto err_alloc_qpn;

	/* Allocate control structures */
	hermon_qp = zalloc ( sizeof ( *hermon_qp ) );
	if ( ! hermon_qp ) {
		rc = -ENOMEM;
		goto err_hermon_qp;
	}

	/* Allocate doorbells */
	hermon_qp->recv.doorbell =
		malloc_dma ( sizeof ( hermon_qp->recv.doorbell[0] ),
			     sizeof ( hermon_qp->recv.doorbell[0] ) );
	if ( ! hermon_qp->recv.doorbell ) {
		rc = -ENOMEM;
		goto err_recv_doorbell;
	}

	memset ( hermon_qp->recv.doorbell, 0,
		 sizeof ( hermon_qp->recv.doorbell[0] ) );
	hermon_qp->send.doorbell =
		( hermon->uar + HERMON_UAR_NON_EQ_PAGE * HERMON_PAGE_SIZE +
		  HERMON_DB_POST_SND_OFFSET );

	/* Allocate work queue buffer */
	hermon_qp->send.num_wqes = ( qp->send.num_wqes /* headroom */ + 1 +
				( 2048 / sizeof ( hermon_qp->send.wqe[0] ) ) );
	hermon_qp->send.num_wqes =
		( 1 << fls ( hermon_qp->send.num_wqes - 1 ) ); /* round up */
	hermon_qp->send.wqe_size = ( hermon_qp->send.num_wqes *
				     sizeof ( hermon_qp->send.wqe[0] ) );
	hermon_qp->recv.wqe_size = ( qp->recv.num_wqes *
				     sizeof ( hermon_qp->recv.wqe[0] ) );
	hermon_qp->wqe_size = ( hermon_qp->send.wqe_size +
				hermon_qp->recv.wqe_size );
	hermon_qp->wqe = malloc_dma ( hermon_qp->wqe_size,
				      sizeof ( hermon_qp->send.wqe[0] ) );
	if ( ! hermon_qp->wqe ) {
		rc = -ENOMEM;
		goto err_alloc_wqe;
	}
	hermon_qp->send.wqe = hermon_qp->wqe;
	memset ( hermon_qp->send.wqe, 0xff, hermon_qp->send.wqe_size );
	hermon_qp->recv.wqe = ( hermon_qp->wqe + hermon_qp->send.wqe_size );
	memset ( hermon_qp->recv.wqe, 0, hermon_qp->recv.wqe_size );

	/* Allocate MTT entries */
	if ( ( rc = hermon_alloc_mtt ( hermon, hermon_qp->wqe,
				       hermon_qp->wqe_size,
				       &hermon_qp->mtt ) ) != 0 ) {
		goto err_alloc_mtt;
	}

	/* Transition queue to INIT state */
	memset ( &qpctx, 0, sizeof ( qpctx ) );
	MLX_FILL_2 ( &qpctx, 2,
		     qpc_eec_data.pm_state, HERMON_PM_STATE_MIGRATED,
		     qpc_eec_data.st, hermon_qp_st[qp->type] );
	MLX_FILL_1 ( &qpctx, 3, qpc_eec_data.pd, HERMON_GLOBAL_PD );
	MLX_FILL_4 ( &qpctx, 4,
		     qpc_eec_data.log_rq_size, fls ( qp->recv.num_wqes - 1 ),
		     qpc_eec_data.log_rq_stride,
		     ( fls ( sizeof ( hermon_qp->recv.wqe[0] ) - 1 ) - 4 ),
		     qpc_eec_data.log_sq_size,
		     fls ( hermon_qp->send.num_wqes - 1 ),
		     qpc_eec_data.log_sq_stride,
		     ( fls ( sizeof ( hermon_qp->send.wqe[0] ) - 1 ) - 4 ) );
	MLX_FILL_1 ( &qpctx, 5,
		     qpc_eec_data.usr_page, HERMON_UAR_NON_EQ_PAGE );
	MLX_FILL_1 ( &qpctx, 33, qpc_eec_data.cqn_snd, qp->send.cq->cqn );
	MLX_FILL_4 ( &qpctx, 38,
		     qpc_eec_data.rre, 1,
		     qpc_eec_data.rwe, 1,
		     qpc_eec_data.rae, 1,
		     qpc_eec_data.page_offset,
		     ( hermon_qp->mtt.page_offset >> 6 ) );
	MLX_FILL_1 ( &qpctx, 41, qpc_eec_data.cqn_rcv, qp->recv.cq->cqn );
	MLX_FILL_H ( &qpctx, 42, qpc_eec_data.db_record_addr_h,
		     virt_to_phys ( hermon_qp->recv.doorbell ) );
	MLX_FILL_1 ( &qpctx, 43, qpc_eec_data.db_record_addr_l,
		     ( virt_to_phys ( hermon_qp->recv.doorbell ) >> 2 ) );
	MLX_FILL_H ( &qpctx, 52, qpc_eec_data.mtt_base_addr_h,
		     hermon_qp->mtt.mtt_base_addr );
	MLX_FILL_1 ( &qpctx, 53, qpc_eec_data.mtt_base_addr_l,
		     ( hermon_qp->mtt.mtt_base_addr >> 3 ) );
	if ( ( rc = hermon_cmd_rst2init_qp ( hermon, qp->qpn,
					     &qpctx ) ) != 0 ) {
		ERROR ( "ConnectX3 %p QPN %lx RST2INIT_QP failed: %s\n",
		       hermon, qp->qpn, strerror ( rc ) );
		goto err_rst2init_qp;
	}
	hermon_qp->state = HERMON_QP_ST_INIT;

	DBGC ( hermon, "ConnectX3 %p QPN 0x%lx send ring [%08lx,%08lx), doorbell "
	       "%08lx\n", hermon, qp->qpn,
	       virt_to_phys ( hermon_qp->send.wqe ),
	       ( virt_to_phys ( hermon_qp->send.wqe ) +
		 hermon_qp->send.wqe_size ),
	       virt_to_phys ( hermon_qp->send.doorbell ) );
	DBGC ( hermon, "ConnectX3 %p QPN 0x%lx receive ring [%08lx,%08lx), "
	       "doorbell %08lx\n", hermon, qp->qpn,
	       virt_to_phys ( hermon_qp->recv.wqe ),
	       ( virt_to_phys ( hermon_qp->recv.wqe ) +
		 hermon_qp->recv.wqe_size ),
	       virt_to_phys ( hermon_qp->recv.doorbell ) );
	DBGC ( hermon, "ConnectX3 %p QPN 0x%lx send CQN %lx receive CQN %lx\n",
	       hermon, qp->qpn, qp->send.cq->cqn, qp->recv.cq->cqn );
	ib_qp_set_drvdata ( qp, hermon_qp );
	return 0;

	hermon_cmd_2rst_qp ( hermon, qp->qpn );
 err_rst2init_qp:
	hermon_free_mtt ( hermon, &hermon_qp->mtt );
 err_alloc_mtt:
	free_dma ( hermon_qp->wqe, hermon_qp->wqe_size );
 err_alloc_wqe:
	free_dma ( hermon_qp->recv.doorbell,
		   sizeof ( hermon_qp->recv.doorbell[0] ) );
 err_recv_doorbell:
	free ( hermon_qp );
 err_hermon_qp:
	hermon_free_qpn ( ibdev, qp );
 err_alloc_qpn:
	return rc;
}

/**
 * Modify queue pair
 *
 * @v ibdev		Infiniband device
 * @v qp		Queue pair
 * @ret rc		Return status code
 */
static int hermon_modify_qp ( struct ib_device *ibdev,
			      struct ib_queue_pair *qp ) {
	struct hermon *hermon = ib_get_drvdata ( ibdev );
	struct hermon_queue_pair *hermon_qp = ib_qp_get_drvdata ( qp );
	struct hermonprm_qp_ee_state_transitions qpctx;
	int rc;

	/* Transition queue to RTR state, if applicable */
	if ( hermon_qp->state < HERMON_QP_ST_RTR ) {
		memset ( &qpctx, 0, sizeof ( qpctx ) );
		MLX_FILL_2 ( &qpctx, 4,
			     qpc_eec_data.mtu,
			     ( ( qp->type == IB_QPT_ETH ) ?
			       HERMON_MTU_ETH : HERMON_MTU_2048 ),
			     qpc_eec_data.msg_max, 31 );
		MLX_FILL_1 ( &qpctx, 7,
			     qpc_eec_data.remote_qpn_een, qp->av.qpn );
		MLX_FILL_1 ( &qpctx, 9,
			     qpc_eec_data.primary_address_path.rlid,
			     qp->av.lid );
		MLX_FILL_1 ( &qpctx, 10,
			     qpc_eec_data.primary_address_path.max_stat_rate,
			     hermon_rate ( &qp->av ) );
		memcpy ( &qpctx.u.dwords[12], &qp->av.gid,
			 sizeof ( qp->av.gid ) );
		MLX_FILL_1 ( &qpctx, 16,
			     qpc_eec_data.primary_address_path.sched_queue,
			     hermon_sched_queue ( ibdev, qp ) );
		MLX_FILL_1 ( &qpctx, 38,
			     qpc_eec_data.physical_function,
			     hermon->physical_function );
		MLX_FILL_1 ( &qpctx, 39,
			     qpc_eec_data.next_rcv_psn, qp->recv.psn );
		if ( ( rc = hermon_cmd_init2rtr_qp ( hermon, qp->qpn,
						     &qpctx ) ) != 0 ) {
			ERROR ( "ConnectX3 %p QPN %lx INIT2RTR_QP failed:"
			       " %s\n", hermon, qp->qpn, strerror ( rc ) );
			return rc;
		}
		hermon_qp->state = HERMON_QP_ST_RTR;
	}

	/* Transition queue to RTS state */
	if ( hermon_qp->state < HERMON_QP_ST_RTS ) {
		memset ( &qpctx, 0, sizeof ( qpctx ) );
		MLX_FILL_1 ( &qpctx, 10,
			     qpc_eec_data.primary_address_path.ack_timeout,
			     14 /* 4.096us * 2^(14) = 67ms */ );
		MLX_FILL_2 ( &qpctx, 30,
			     qpc_eec_data.retry_count, HERMON_RETRY_MAX,
			     qpc_eec_data.rnr_retry, HERMON_RETRY_MAX );
		MLX_FILL_1 ( &qpctx, 32,
			     qpc_eec_data.next_send_psn, qp->send.psn );
		MLX_FILL_1 ( &qpctx, 38,
			     qpc_eec_data.physical_function,
			     hermon->physical_function );
		if ( ( rc = hermon_cmd_rtr2rts_qp ( hermon, qp->qpn,
						    &qpctx ) ) != 0 ) {
			ERROR ( "ConnectX3 %p QPN %lx RTR2RTS_QP failed: "
			       "%s\n", hermon, qp->qpn, strerror ( rc ) );
			return rc;
		}
		hermon_qp->state = HERMON_QP_ST_RTS;
	}

	/* Update parameters in RTS state */
	memset ( &qpctx, 0, sizeof ( qpctx ) );
	MLX_FILL_1 ( &qpctx, 0, opt_param_mask, HERMON_QP_OPT_PARAM_QKEY );
	MLX_FILL_1 ( &qpctx, 38,
			     qpc_eec_data.physical_function,
			     hermon->physical_function );
	MLX_FILL_1 ( &qpctx, 44, qpc_eec_data.q_key, qp->qkey );
	if ( ( rc = hermon_cmd_rts2rts_qp ( hermon, qp->qpn, &qpctx ) ) != 0 ){
		ERROR ( "ConnectX3 %p QPN %lx RTS2RTS_QP failed: %s\n",
		       hermon, qp->qpn, strerror ( rc ) );
		return rc;
	}

	return 0;
}

/**
 * Destroy queue pair
 *
 * @v ibdev		Infiniband device
 * @v qp		Queue pair
 */
static void hermon_destroy_qp ( struct ib_device *ibdev,
				struct ib_queue_pair *qp ) {
	struct hermon *hermon = ib_get_drvdata ( ibdev );
	struct hermon_queue_pair *hermon_qp = ib_qp_get_drvdata ( qp );
	int rc;

	/* Take ownership back from hardware */
	if ( ( rc = hermon_cmd_2rst_qp ( hermon, qp->qpn ) ) != 0 ) {
		ERROR ( "ConnectX3 %p QPN %lx FATAL 2RST_QP failed: %s\n",
		       hermon, qp->qpn, strerror ( rc ) );
		/* Leak memory and return; at least we avoid corruption */
		return;
	}

	/* Free MTT entries */
	hermon_free_mtt ( hermon, &hermon_qp->mtt );

	/* Free memory */
	free_dma ( hermon_qp->wqe, hermon_qp->wqe_size );
	free_dma ( hermon_qp->recv.doorbell,
		   sizeof ( hermon_qp->recv.doorbell[0] ) );
	free ( hermon_qp );

	/* Mark queue number as free */
	hermon_free_qpn ( ibdev, qp );

	ib_qp_set_drvdata ( qp, NULL );
}

/***************************************************************************
 *
 * Work request operations
 *
 ***************************************************************************
 */

/**
 * Construct UD send work queue entry
 *
 * @v ibdev		Infiniband device
 * @v qp		Queue pair
 * @v av		Address vector
 * @v iobuf		I/O buffer
 * @v wqe		Send work queue entry
 * @ret opcode		Control opcode
 */
static __attribute__ (( unused )) unsigned int
hermon_fill_nop_send_wqe ( struct ib_device *ibdev __unused,
			   struct ib_queue_pair *qp __unused,
			   struct ib_address_vector *av __unused,
			   struct io_buffer *iobuf __unused,
			   union hermon_send_wqe *wqe ) {

	MLX_FILL_1 ( &wqe->ctrl, 1, ds, ( sizeof ( wqe->ctrl ) / 16 ) );
	MLX_FILL_1 ( &wqe->ctrl, 2, c, 0x03 /* generate completion */ );
	return HERMON_OPCODE_NOP;
}

/**
 * Construct UD send work queue entry
 *
 * @v ibdev		Infiniband device
 * @v qp		Queue pair
 * @v av		Address vector
 * @v iobuf		I/O buffer
 * @v wqe		Send work queue entry
 * @ret opcode		Control opcode
 */
static unsigned int
hermon_fill_ud_send_wqe ( struct ib_device *ibdev,
			  struct ib_queue_pair *qp __unused,
			  struct ib_address_vector *av,
			  struct io_buffer *iobuf,
			  union hermon_send_wqe *wqe )
{
	struct hermon *hermon = ib_get_drvdata ( ibdev );

	MLX_FILL_1 ( &wqe->ud.ctrl, 1, ds,
		     ( ( offsetof ( typeof ( wqe->ud ), data[1] ) / 16 ) ) );
	MLX_FILL_1 ( &wqe->ud.ctrl, 2, c, 0x03 /* generate completion */ );
	MLX_FILL_2 ( &wqe->ud.ud, 0,
		     ud_address_vector.pd, HERMON_GLOBAL_PD,
		     ud_address_vector.port_number, ibdev->port );
	MLX_FILL_2 ( &wqe->ud.ud, 1,
		     ud_address_vector.rlid, av->lid,
		     ud_address_vector.g, av->gid_present );
	MLX_FILL_1 ( &wqe->ud.ud, 2,
		     ud_address_vector.max_stat_rate, hermon_rate ( av ) );
	MLX_FILL_1 ( &wqe->ud.ud, 3, ud_address_vector.sl, av->sl );
	memcpy ( &wqe->ud.ud.u.dwords[4], &av->gid, sizeof ( av->gid ) );
	MLX_FILL_1 ( &wqe->ud.ud, 8, destination_qp, av->qpn );
	MLX_FILL_1 ( &wqe->ud.ud, 9, q_key, av->qkey );
	MLX_FILL_1 ( &wqe->ud.data[0], 0, byte_count, iob_len ( iobuf ) );
	MLX_FILL_1 ( &wqe->ud.data[0], 1, l_key, hermon->lkey );
	MLX_FILL_H ( &wqe->ud.data[0], 2,
		     local_address_h, virt_to_bus (iobuf->data ) );
	MLX_FILL_1 ( &wqe->ud.data[0], 3,
		     local_address_l, virt_to_bus (iobuf->data ) );
	return HERMON_OPCODE_SEND;
}

/**
 * Construct RC send work queue entry
 *
 * @v ibdev		Infiniband device
 * @v qp		Queue pair
 * @v av		Address vector
 * @v iobuf		I/O buffer
 * @v wqe		Send work queue entry
 * @ret opcode		Control opcode
 */
static unsigned int
hermon_fill_rc_send_wqe ( struct ib_device *ibdev,
			  struct ib_queue_pair *qp __unused,
			  struct ib_address_vector *av __unused,
			  struct io_buffer *iobuf,
			  union hermon_send_wqe *wqe )
{
	struct hermon *hermon = ib_get_drvdata ( ibdev );

	MLX_FILL_1 ( &wqe->rc.ctrl, 1, ds,
		     ( ( offsetof ( typeof ( wqe->rc ), data[1] ) / 16 ) ) );
	MLX_FILL_1 ( &wqe->rc.ctrl, 2, c, 0x03 /* generate completion */ );
	MLX_FILL_1 ( &wqe->rc.data[0], 0, byte_count, iob_len ( iobuf ) );
	MLX_FILL_1 ( &wqe->rc.data[0], 1, l_key, hermon->lkey );
	MLX_FILL_H ( &wqe->rc.data[0], 2,
		     local_address_h, virt_to_bus ( iobuf->data ) );
	MLX_FILL_1 ( &wqe->rc.data[0], 3,
		     local_address_l, virt_to_bus ( iobuf->data ) );
	return HERMON_OPCODE_SEND;
}

/**
 * Construct Ethernet send work queue entry
 *
 * @v ibdev		Infiniband device
 * @v qp		Queue pair
 * @v av		Address vector
 * @v iobuf		I/O buffer
 * @v wqe		Send work queue entry
 * @ret opcode		Control opcode
 */
static unsigned int
hermon_fill_eth_send_wqe ( struct ib_device *ibdev,
			   struct ib_queue_pair *qp __unused,
			   struct ib_address_vector *av __unused,
			   struct io_buffer *iobuf,
			   union hermon_send_wqe *wqe )
{
	struct hermon *hermon = ib_get_drvdata ( ibdev );

	/* Fill work queue entry */
	MLX_FILL_1 ( &wqe->eth.ctrl, 1, ds,
		     ( ( offsetof ( typeof ( wqe->mlx ), data[1] ) / 16 ) ) );
	MLX_FILL_2 ( &wqe->eth.ctrl, 2,
		     c, 0x03 /* generate completion */,
		     s, 1 /* inhibit ICRC */ );
	MLX_FILL_1 ( &wqe->eth.data[0], 0,
		     byte_count, iob_len ( iobuf ) );
	MLX_FILL_1 ( &wqe->eth.data[0], 1, l_key, hermon->lkey );
	MLX_FILL_H ( &wqe->eth.data[0], 2,
		     local_address_h, virt_to_bus (iobuf->data ) );
	MLX_FILL_1 ( &wqe->eth.data[0], 3,
		     local_address_l, virt_to_bus (iobuf->data ) );
	return HERMON_OPCODE_SEND;
}

/** Work queue entry constructors */
static unsigned int
( * hermon_fill_send_wqe[] ) ( struct ib_device *ibdev,
			       struct ib_queue_pair *qp,
			       struct ib_address_vector *av,
			       struct io_buffer *iobuf,
			       union hermon_send_wqe *wqe ) = {
//	[IB_QPT_SMI] = hermon_fill_mlx_send_wqe,
//	[IB_QPT_GSI] = hermon_fill_mlx_send_wqe,
	[IB_QPT_UD] = hermon_fill_ud_send_wqe,
	[IB_QPT_RC] = hermon_fill_rc_send_wqe,
	[IB_QPT_ETH] = hermon_fill_eth_send_wqe,
};

/**
 * Post send work queue entry
 *
 * @v ibdev		Infiniband device
 * @v qp		Queue pair
 * @v av		Address vector
 * @v iobuf		I/O buffer
 * @ret rc		Return status code
 */
static int hermon_post_send ( struct ib_device *ibdev,
			      struct ib_queue_pair *qp,
			      struct ib_address_vector *av,
			      struct io_buffer *iobuf )
{
	struct hermon *hermon __unused = ib_get_drvdata ( ibdev );
	struct hermon_queue_pair *hermon_qp = ib_qp_get_drvdata ( qp );
	struct ib_work_queue *wq = &qp->send;
	struct hermon_send_work_queue *hermon_send_wq = &hermon_qp->send;
	union hermon_send_wqe *wqe;
	union hermonprm_doorbell_register db_reg;
	unsigned long wqe_idx_mask;
	unsigned long wqe_idx;
	unsigned int owner;
	unsigned int opcode;

	/* Allocate work queue entry */
	wqe_idx = ( wq->next_idx & ( hermon_send_wq->num_wqes - 1 ) );
	owner = ( ( wq->next_idx & hermon_send_wq->num_wqes ) ? 1 : 0 );
	wqe_idx_mask = ( wq->num_wqes - 1 );
	if ( wq->iobufs[ wqe_idx & wqe_idx_mask ] ) {
		DBGC ( hermon, "ConnectX3 %p QPN %lx send queue full",
		       hermon, qp->qpn );
		return -ENOBUFS;
	}
	wq->iobufs[ wqe_idx & wqe_idx_mask ] = iobuf;
	wqe = &hermon_send_wq->wqe[wqe_idx];
	/* Construct work queue entry */
	memset ( ( ( ( void * ) wqe ) + 4 /* avoid ctrl.owner */ ), 0,
		   ( sizeof ( *wqe ) - 4 ) );
	assert ( qp->type < ( sizeof ( hermon_fill_send_wqe ) /
			      sizeof ( hermon_fill_send_wqe[0] ) ) );
	assert ( hermon_fill_send_wqe[qp->type] != NULL );
	opcode = hermon_fill_send_wqe[qp->type] ( ibdev, qp, av, iobuf, wqe );
	barrier();
	MLX_FILL_2 ( &wqe->ctrl, 0,
		     opcode, opcode,
		     owner, owner );
	DBGCP ( hermon, "ConnectX3 %p QPN %lx posting send WQE %lx[v = %p p = %lx]:\n",
		hermon, qp->qpn, wqe_idx, wqe, virt_to_phys( wqe ));
	DBGCP_HDA ( hermon, virt_to_phys ( wqe ), wqe, sizeof ( *wqe ) );
	/* Ring doorbell register */
	MLX_FILL_1 ( &db_reg.send, 0, qn, qp->qpn );
	barrier();
	WRITE_REG (hermon, db_reg.dword[0], hermon_send_wq->doorbell );

	/* Update work queue's index */
	wq->next_idx++;

	return 0;
}

/**
 * Post receive work queue entry
 *
 * @v ibdev		Infiniband device
 * @v qp		Queue pair
 * @v iobuf		I/O buffer
 * @ret rc		Return status code
 */
static int hermon_post_recv ( struct ib_device *ibdev,
			      struct ib_queue_pair *qp,
			      struct io_buffer *iobuf )
{
	struct hermon			*hermon		= ib_get_drvdata ( ibdev );
	struct hermon_queue_pair	*hermon_qp	= ib_qp_get_drvdata ( qp );
	struct ib_work_queue		*wq		= &qp->recv;
	struct hermon_recv_work_queue	*hermon_recv_wq	= &hermon_qp->recv;
	struct hermonprm_recv_wqe	*wqe;
	unsigned int wqe_idx_mask;


	/* Allocate work queue entry */
	wqe_idx_mask = ( wq->num_wqes - 1 );
	if ( wq->iobufs[wq->next_idx & wqe_idx_mask] ) {
		DBGC ( hermon, "ConnectX3 %p QPN %lx receive queue full",
		       hermon, qp->qpn );
		return -ENOBUFS;
	}
	wq->iobufs[wq->next_idx & wqe_idx_mask] = iobuf;
	wqe = &hermon_recv_wq->wqe[wq->next_idx & wqe_idx_mask].recv;

	/* Construct work queue entry */
	MLX_FILL_1 ( &wqe->data[0], 0, byte_count, iob_tailroom ( iobuf ) );
	MLX_FILL_1 ( &wqe->data[0], 1, l_key, hermon->lkey );
	MLX_FILL_H ( &wqe->data[0], 2,
		     local_address_h, virt_to_bus ( iobuf->data ) );
	MLX_FILL_1 ( &wqe->data[0], 3,
		     local_address_l, virt_to_bus ( iobuf->data ) );

	/* Update work queue's index */
	wq->next_idx++;

	/* Update doorbell record */
	barrier();
	MLX_FILL_1 ( hermon_recv_wq->doorbell, 0, receive_wqe_counter,
		     ( wq->next_idx & 0xffff ) );

	return 0;
}

/**
 * Handle completion
 *
 * @v ibdev		Infiniband device
 * @v cq		Completion queue
 * @v cqe		Hardware completion queue entry
 * @ret rc		Return status code
 */
static int hermon_complete ( struct ib_device *ibdev,
			     struct ib_completion_queue *cq,
			     union hermonprm_completion_entry *cqe ) {
	struct hermon *hermon __unused = ib_get_drvdata ( ibdev );
	struct ib_work_queue *wq;
	struct ib_queue_pair *qp;
	struct io_buffer *iobuf;
	struct ib_address_vector recv_av;
	struct ib_global_route_header *grh;
	struct ib_address_vector *av;
	unsigned int opcode;
	unsigned long qpn;
	int is_send;
	unsigned long wqe_idx;
	unsigned long wqe_idx_mask;
	size_t len;
	int rc = 0;

	/* check if hermon is still operational */
	if (unlikely(!hermon->open_count)) {
		DBGC( hermon, "ConnectX3 %p hermon NIC is closed. Cowardly refuse to execute hermon_complete\n",
		      hermon);
		return -EINVAL;
	}

	poll_verbosity = 1;
	/* Parse completion */
	qpn		= MLX_GET ( &cqe->normal, qpn );
	is_send		= MLX_GET ( &cqe->normal, s_r );
	opcode		= MLX_GET ( &cqe->normal, opcode );
	if ( opcode >= HERMON_OPCODE_RECV_ERROR ) {
		/* "s" field is not valid for error opcodes */
		is_send = ( opcode == HERMON_OPCODE_SEND_ERROR );
		DBGC ( hermon, "ConnectX3 %p CQN %lx syndrome %x vendor %x\n",
		       hermon, cq->cqn, MLX_GET ( &cqe->error, syndrome ),
		       MLX_GET ( &cqe->error, vendor_error_syndrome ) );
		rc = -EIO;
		/* Don't return immediately; propagate error to completer */
	}

	/* Identify work queue */
	wq = ib_find_wq ( cq, qpn, is_send );
	if ( ! wq ) {
		DBGC ( hermon, "ConnectX3 %p CQN %lx unknown %s QPN %lx\n",
		       hermon, cq->cqn, ( is_send ? L"send" : L"recv" ), qpn );
		return -EIO;
	}
	qp = wq->qp;

	/* Identify work queue entry */
	wqe_idx = MLX_GET ( &cqe->normal, wqe_counter );
	wqe_idx_mask = ( wq->num_wqes - 1 );
	DBGCP ( hermon, "ConnectX3 %p CQN %lx QPN %lx %s WQE %lx completed:\n",
		hermon, cq->cqn, qp->qpn, ( is_send ? L"send" : L"recv" ),
		wqe_idx );
	DBGCP_HDA ( hermon, virt_to_phys ( cqe ), cqe, sizeof ( *cqe ) );

	/* Identify I/O buffer */
	iobuf = wq->iobufs[ wqe_idx & wqe_idx_mask ];
	if ( ! iobuf ) {
		DBGC ( hermon, "ConnectX3 %p CQN %lx QPN %lx empty %s WQE "
		       "%lx\n", hermon, cq->cqn, qp->qpn,
		       ( is_send ? L"send" : L"recv" ), wqe_idx );
		return -EIO;
	}
	wq->iobufs[ wqe_idx & wqe_idx_mask ] = NULL;

	if ( is_send ) {
		/* Hand off to completion handler */
		ib_complete_send ( ibdev, qp, iobuf, rc );
		TAG();
	} else {
		/* Set received length */
		len = MLX_GET ( &cqe->normal, byte_cnt );
		assert ( len <= iob_tailroom ( iobuf ) );
		iob_put ( iobuf, len );
		memset ( &recv_av, 0, sizeof ( recv_av ) );
		switch ( qp->type ) {
		case IB_QPT_SMI:
		case IB_QPT_GSI:
		case IB_QPT_UD:
			assert ( iob_len ( iobuf ) >= sizeof ( *grh ) );
			grh = iobuf->data;
			iob_pull ( iobuf, sizeof ( *grh ) );
			/* Construct address vector */
			av = &recv_av;
			av->qpn = MLX_GET ( &cqe->normal, srq_rqpn );
			av->lid = MLX_GET ( &cqe->normal, slid_smac47_32 );
			av->sl = MLX_GET ( &cqe->normal, sl );
			av->gid_present = MLX_GET ( &cqe->normal, g );
			memcpy ( &av->gid, &grh->sgid, sizeof ( av->gid ) );
			break;
		case IB_QPT_RC:
			av = &qp->av;
			break;
		case IB_QPT_ETH:
			/* Construct address vector */
			av = &recv_av;
			av->vlan_present = MLX_GET ( &cqe->normal, vlan );
			av->vlan = MLX_GET ( &cqe->normal, vid );
			break;
		default:
			assert ( 0 );
			return -EINVAL;
		}
		/* Hand off to completion handler */
		ib_complete_recv ( ibdev, qp, av, iobuf, rc );
	}
	TAG("Out");
	return rc;
}

/**
 * Poll completion queue
 *
 * @v ibdev		Infiniband device
 * @v cq		Completion queue
 */
static void hermon_poll_cq ( struct ib_device *ibdev,
			     struct ib_completion_queue *cq )
{
	struct hermon			*hermon		= ib_get_drvdata ( ibdev );
	struct hermon_completion_queue	*hermon_cq	= ib_cq_get_drvdata ( cq );
	union hermonprm_completion_entry *cqe;
	unsigned int		cqe_idx_mask;
	int rc;

	if (unlikely(!hermon->open_count)) {
		DBGC( hermon, "ConnectX3 %p hermon NIC is closed. Cowardly refuse to execute hermon_poll_cq\n",
		      hermon);
		return;
	}

	/* validate cq data */
	assert( cq->num_cqes <= HERMON_ETH_NUM_CQES);
	
	while ( 1 ) {
		if (unlikely(!hermon->open_count)) {
			DBGC( hermon, "ConnectX3 %p hermon NIC is closed. Cowardly refuse to continue hermon_poll_cq\n",
			      hermon);
			return;
		}

		/* validate next idx */
		assert( cq->next_idx <= 0xFFFFFFUL);

		/* Look for completion entry */
		cqe_idx_mask = ( cq->num_cqes - 1 );
		cqe = &hermon_cq->cqe[cq->next_idx & cqe_idx_mask];
		if ( MLX_GET ( &cqe->normal, owner ) ^
		     ( ( cq->next_idx & cq->num_cqes ) ? 1 : 0 ) ) {
			/* Entry still owned by hardware; end of poll */
			break;
		}

		/* Handle completion */
		if ( ( rc = hermon_complete ( ibdev, cq, cqe ) ) != 0 ) {
			ERROR ( "ConnectX3 %p CQN %lx failed to complete:"
			       " %s\n", hermon, cq->cqn, strerror ( rc ) );
			DBGC_HDA ( hermon, virt_to_phys ( cqe ),
				   cqe, sizeof ( *cqe ) );
		}

		if (unlikely(!hermon->open_count)) {
			DBGC( hermon, "ConnectX3 %p hermon NIC is closed. Cowardly refuse to continue hermon_poll_cq\n",
			      hermon);
			return;
		}

		/* Update completion queue's index */
		cq->next_idx++;

		/* Update doorbell record */
		MLX_FILL_1 ( hermon_cq->doorbell, 0, update_ci,
			     ( cq->next_idx & 0x00ffffffUL ) );
	}
}


/***************************************************************************
 *
 * Multicast group operations
 *
 ***************************************************************************
 */


/**
 * Attach to multicast group entry
 *
 * @v ibdev		Infiniband device
 * @v gid		Multicast GID
 * @v qp		MCG entry index
 * @v prev_index	MCG entry previous entry
 * @v mcg		MCG entry
 * @ret rc		Return status code
 */
static int hermon_find_entry ( struct ib_device *ibdev,
			       union ib_gid *gid,
			       int *index,
			       int *prev_index,
			       struct hermonprm_mcg_entry *mcg )
{
	struct hermon *hermon = ib_get_drvdata ( ibdev );
	struct hermonprm_mgm_hash hash;
	u8 *mcg_gid_p;
	int rc = 0;

	/* Generate hash table index */
	if ( ( rc = hermon_cmd_mgid_hash
			    ( hermon, gid, &hash, ibdev->protocol ) ) != 0 ) {
		ERROR ( "ConnectX3 %p could not hash GID: %s\n",
		       hermon, strerror ( rc ) );
		return rc;
	}

	*index = MLX_GET ( &hash, hash );
	*prev_index = -1;

	/* Check for existing hash table entry */
	do {
		if ( ( rc = hermon_cmd_read_mcg
					( hermon, *index, mcg ) ) != 0 ) {
			ERROR ( "ConnectX3 %p could not read MCG %x: "
			       "%s\n", hermon, *index, strerror ( rc ) );
			return rc;
		}

		if ( MLX_GET ( mcg, hdr.members_count ) == 0 ) {
			if ( *index != (int) MLX_GET ( &hash, hash ) ) {
				DBGC ( hermon, "ConnectX3 %p Found zero MGID"
					       " in AMGM\n", hermon );
				return -EBUSY;
			}
			/* Add new entry */
			return 0;
		}

		mcg_gid_p = (u8 *)mcg;
		mcg_gid_p += 16;
		if ( !memcmp ( mcg_gid_p, gid, sizeof ( *gid ) ) &&
		     ( MLX_GET ( mcg, hdr.protocol ) == ibdev->protocol ) ) {
			DBGC ( hermon, "ConnectX3 %p Found MCG entry with the"
			       " same GID\n", hermon );
			return 0;
		}

		*prev_index = *index;
		*index = MLX_GET ( mcg, hdr.next_mcg );
	} while ( *index );

	/* Entry was not found */
	*index = -1;

	return 0;
}


/**
 * Attach to multicast group
 *
 * @v ibdev		Infiniband device
 * @v qp		Queue pair
 * @v gid		Multicast GID
 * @ret rc		Return status code
 */
static int hermon_mcast_attach ( struct ib_device *ibdev,
				 struct ib_queue_pair *qp,
				 union ib_gid *gid ) {
	struct hermon *hermon = ib_get_drvdata ( ibdev );
	struct hermonprm_mcg_entry mcg;
	int index = 0;
	int prev_index = 0;
	unsigned int members_count;
	u8 link = 0;
	unsigned int i;
	int rc;

	if ( ( rc = hermon_find_entry
			   ( ibdev, gid, &index, &prev_index, &mcg ) ) != 0 ) {
		ERROR ( "ConnectX3 %p failed to search MCG entry %s\n",
		       hermon, strerror ( rc ) );
		return rc;
	}

	if ( index == -1 ) {
		link = 1;
		index = hermon->mcg_aux_index ++;
		DBGC ( hermon, "ConnectX3 %p add new entry with index 0x%x\n",
		       hermon, index );
		memset ( &mcg, 0, sizeof ( mcg ) );
		memcpy ( &mcg.u.dwords[4], gid, sizeof ( *gid ) );
	}

	members_count = MLX_GET ( &mcg, hdr.members_count );

	if ( members_count >= HERMON_MAX_MGM_MEMBERS ) {
		DBGC ( hermon, "ConnectX3 %p MGM is full\n",
		       hermon );
		return -ENOMEM;
	}

	for ( i = 0; i < members_count; ++i ) {
		if ( MLX_GET ( &mcg, qp[i] ) == qp->qpn ) {
			DBGC ( hermon, "ConnectX3 %p QP 0x%lx already member"
			       " in MGM\n", hermon, qp->qpn );
			return 0;
		}
	}

	/* Update hash table entry */
	MLX_FILL_2 ( &mcg, 1, hdr.members_count, ++members_count,
		     hdr.protocol, ibdev->protocol );
	MLX_FILL_1 ( &mcg, ( 8 + (int)members_count - 1 ),
		     qp[members_count - 1].qpn, qp->qpn );
	memcpy ( &mcg.u.dwords[4], gid, sizeof ( *gid ) );
	if ( ( rc = hermon_cmd_write_mcg ( hermon, index, &mcg ) ) != 0 ) {
		ERROR ( "ConnectX3 %p could not write MCG %x: %s\n",
		       hermon, index, strerror ( rc ) );
		return rc;
	}

	if ( !link )
		return 0;

	/* Repair link list */
	if ( ( rc = hermon_cmd_read_mcg ( hermon, prev_index, &mcg ) ) != 0 ) {
	  ERROR ( "ConnectX3 %p could not read MCG %x: %s\n",
		       hermon, prev_index, strerror ( rc ) );
		return rc;
	}

	MLX_FILL_1 ( &mcg, 0, hdr.next_mcg, index );

	if ( ( rc = hermon_cmd_write_mcg
					( hermon, prev_index, &mcg ) ) != 0 ) {
	  ERROR ( "ConnectX3 %p could not write MCG %x: %s\n",
		       hermon, prev_index, strerror ( rc ) );
		return rc;
	}

	return 0;
}

/**
 * Detach from multicast group
 *
 * @v ibdev		Infiniband device
 * @v qp		Queue pair
 * @v gid		Multicast GID
 * @ret rc		Return status code
 */
static void hermon_mcast_detach ( struct ib_device *ibdev,
				  struct ib_queue_pair *qp,
				  union ib_gid *gid ) {
	struct hermon *hermon = ib_get_drvdata ( ibdev );
	struct hermonprm_mcg_entry mcg;
	int index = 0;
	int prev_index = 0;
	int next_index = 0;
	unsigned int members_count;
	int i;
	int rc;
	int qp_index;

	if ( ( rc = hermon_find_entry
			   ( ibdev, gid, &index, &prev_index, &mcg ) ) != 0 ) {
	  ERROR ( "ConnectX3 %p failed to search MCG entry %s\n",
		       hermon, strerror ( rc ) );
		return;
	}

	if (index == -1) {
	  ERROR ( "ConnectX3 %p GID not found in MCG table\n",
		       hermon );
		return;
	}

	members_count = MLX_GET ( &mcg, hdr.members_count );
	for ( qp_index = -1, i = 0; i < (int)members_count; ++i )
		if ( MLX_GET ( &mcg, qp[i] ) == qp->qpn )
			qp_index = i;

	if ( qp_index == -1 ) {
	  ERROR ( "ConnectX3 %p QP not found in MCG entry\n",
		       hermon );
		return;
	}

	MLX_FILL_2 ( &mcg, 1, hdr.members_count, --members_count,
		     hdr.protocol, ibdev->protocol );
	MLX_FILL_1 ( &mcg, ( 8 + qp_index ), qp[qp_index].qpn,
		     MLX_GET ( &mcg, qp[i -1].qpn ) );
	MLX_FILL_1 ( &mcg, ( 8 + i - 1 ), qp[i - 1].qpn, 0 );
	if ( members_count ) {
		if ( ( rc = hermon_cmd_write_mcg
					     ( hermon, index, &mcg ) ) != 0 ) {
		  ERROR ( "ConnectX3 %p could not write MCG %x: %s\n",
			       hermon, index, strerror ( rc ) );
			return;
		}
		return;
	}

	if ( prev_index == -1 ) {
		next_index = MLX_GET ( &mcg, hdr.next_mcg );
		if ( next_index ) {
			if ( ( rc = hermon_cmd_read_mcg
					( hermon, next_index, &mcg ) ) != 0 ) {
			  ERROR ( "ConnectX3 %p could not read MCG "
				       "%x: %s\n", hermon, next_index,
				       strerror ( rc ) );
				return;
			}
		} else
			memset ( &mcg.u.dwords[4], 0, sizeof ( union ib_gid ) );

		if ( ( rc = hermon_cmd_write_mcg
					     ( hermon, index, &mcg ) ) != 0 ) {
			ERROR ( "ConnectX3 %p could not write MCG %x:"
			       " %s\n", hermon, index, strerror ( rc ) );
			return;
		}
	} else {
		/* Remove entry from AMGM */
		next_index = MLX_GET ( &mcg, hdr.next_mcg );

		if ( ( rc = hermon_cmd_read_mcg
					( hermon, prev_index, &mcg ) ) != 0 ) {
		  ERROR ( "ConnectX3 %p could not read MCG %x:"
			       " %s\n", hermon, prev_index, strerror ( rc ) );
			return;
		}

		MLX_FILL_1 ( &mcg, 0, hdr.next_mcg, next_index );
		if ( ( rc = hermon_cmd_write_mcg
					     ( hermon, index, &mcg ) ) != 0 ) {
		  ERROR ( "ConnectX3 %p could not write MCG %x: %s\n",
			       hermon, index, strerror ( rc ) );
			return;
		}
	}

	return;
}


/***************************************************************************
 *
 * Event queues
 *
 ***************************************************************************
 */

/**
 * Create event queue
 *
 * @v hermon		ConnectX3 device
 * @ret rc		Return status code
 */
static int hermon_create_eq ( struct hermon *hermon ) {
	struct hermon_event_queue *hermon_eq = &hermon->eq;
	struct hermonprm_eqc eqctx;
	struct hermonprm_event_mask mask;
	unsigned int i;
	int rc;

	/* Select event queue number */
	hermon_eq->eqn = ( 4 * hermon->cap.reserved_uars );
	if ( hermon_eq->eqn < hermon->cap.reserved_eqs )
		hermon_eq->eqn = hermon->cap.reserved_eqs;

	/* Calculate doorbell address */
	hermon_eq->doorbell =
		( hermon->uar + HERMON_DB_EQ_OFFSET ( hermon_eq->eqn ) );

	/* Allocate event queue itself */
	hermon_eq->eqe_size =
		( HERMON_NUM_EQES * sizeof ( hermon_eq->eqe[0] ) );
	hermon_eq->eqe = malloc_dma ( hermon_eq->eqe_size,
				      sizeof ( hermon_eq->eqe[0] ) );
	if ( ! hermon_eq->eqe ) {
		rc = -ENOMEM;
		goto err_eqe;
	}
	memset ( hermon_eq->eqe, 0, hermon_eq->eqe_size );
	for ( i = 0 ; i < HERMON_NUM_EQES ; i++ ) {
		MLX_FILL_1 ( &hermon_eq->eqe[i].generic, 7, owner, 1 );
	}
	barrier();

	/* Allocate MTT entries */
	if ( ( rc = hermon_alloc_mtt ( hermon, hermon_eq->eqe,
				       hermon_eq->eqe_size,
				       &hermon_eq->mtt ) ) != 0 )
		goto err_alloc_mtt;

	/* Hand queue over to hardware */
	memset ( &eqctx, 0, sizeof ( eqctx ) );
	MLX_FILL_2 ( &eqctx, 0,
		     st, 0xa /* "Fired" */,
		     oi, 1 );
	MLX_FILL_1 ( &eqctx, 2,
		     page_offset, ( hermon_eq->mtt.page_offset >> 5 ) );
	MLX_FILL_1 ( &eqctx, 3, log_eq_size, fls ( HERMON_NUM_EQES - 1 ) );
	MLX_FILL_H ( &eqctx, 6, mtt_base_addr_h,
		     hermon_eq->mtt.mtt_base_addr );
	MLX_FILL_1 ( &eqctx, 7, mtt_base_addr_l,
		     ( hermon_eq->mtt.mtt_base_addr >> 3 ) );
	if ( ( rc = hermon_cmd_sw2hw_eq ( hermon, hermon_eq->eqn,
					  &eqctx ) ) != 0 ) {
	  ERROR ( "ConnectX3 %p EQN %lx SW2HW_EQ failed: %s\n",
		       hermon, hermon_eq->eqn, strerror ( rc ) );
		goto err_sw2hw_eq;
	}

	/* Map all events to this event queue */
	memset ( &mask, 0xff, sizeof ( mask ) );
	if ( ( rc = hermon_cmd_map_eq ( hermon,
					( HERMON_MAP_EQ | hermon_eq->eqn ),
					&mask ) ) != 0 ) {
	  ERROR ( "ConnectX3 %p EQN %lx MAP_EQ failed: %s\n",
		       hermon, hermon_eq->eqn, strerror ( rc )  );
		goto err_map_eq;
	}

	DBGC ( hermon, "ConnectX3 %p EQN %lx ring [%08lx,%08lx), doorbell "
	       "%08lx\n", hermon, hermon_eq->eqn,
	       virt_to_phys ( hermon_eq->eqe ),
	       ( virt_to_phys ( hermon_eq->eqe ) + hermon_eq->eqe_size ),
	       virt_to_phys ( hermon_eq->doorbell ) );
	return 0;

 err_map_eq:
	hermon_cmd_hw2sw_eq ( hermon, hermon_eq->eqn, &eqctx );
 err_sw2hw_eq:
	hermon_free_mtt ( hermon, &hermon_eq->mtt );
 err_alloc_mtt:
	free_dma ( hermon_eq->eqe, hermon_eq->eqe_size );
 err_eqe:
	memset ( hermon_eq, 0, sizeof ( *hermon_eq ) );
	return rc;
}

/**
 * Destroy event queue
 *
 * @v hermon		ConnectX3 device
 */
static void hermon_destroy_eq ( struct hermon *hermon ) {
	struct hermon_event_queue *hermon_eq = &hermon->eq;
	struct hermonprm_eqc eqctx;
	struct hermonprm_event_mask mask;
	int rc;

	/* Unmap events from event queue */
	memset ( &mask, 0xff, sizeof ( mask ) );
	if ( ( rc = hermon_cmd_map_eq ( hermon,
					( HERMON_UNMAP_EQ | hermon_eq->eqn ),
					&mask ) ) != 0 ) {
	  ERROR ( "ConnectX3 %p EQN %lx FATAL MAP_EQ failed to "
		       "unmap: %s\n", hermon, hermon_eq->eqn, strerror ( rc ) );
		/* Continue; HCA may die but system should survive */
	}

	/* Take ownership back from hardware */
	if ( ( rc = hermon_cmd_hw2sw_eq ( hermon, hermon_eq->eqn,
					  &eqctx ) ) != 0 ) {
	  ERROR ( "ConnectX3 %p EQN %lx FATAL HW2SW_EQ failed: %s\n",
		       hermon, hermon_eq->eqn, strerror ( rc ) );
		/* Leak memory and return; at least we avoid corruption */
		return;
	}

	/* Free MTT entries */
	hermon_free_mtt ( hermon, &hermon_eq->mtt );

	/* Free memory */
	free_dma ( hermon_eq->eqe, hermon_eq->eqe_size );
	memset ( hermon_eq, 0, sizeof ( *hermon_eq ) );
}

/**
 * Handle port state event
 *
 * @v hermon		ConnectX3 device
 * @v eqe		Port state change event queue entry
 */
static void hermon_event_port_state_change ( struct hermon *hermon,
					     union hermonprm_event_entry *eqe){
	unsigned int port;
	int link_up;

	/* Get port and link status */
	port = ( MLX_GET ( &eqe->port_state_change, data.p ) - 1 );
	link_up = ( MLX_GET ( &eqe->generic, event_sub_type ) & 0x04 );
	DBGC ( hermon, "ConnectX3 %p port %d link %s\n", hermon, ( port + 1 ),
	       ( link_up ? L"up" : L"down" ) );

	/* Sanity check */
	if ( port >= hermon->num_ports ) {
	  ERROR ( "ConnectX3 %p port %d does not exist!\n",
		       hermon, ( port + 1 ) );
		return;
	}

	/* Notify device of port state change */
	hermon->port[port].type->state_change ( hermon, &hermon->port[port],
						link_up );
}

/**
 * Operation required action
 *
 * @v ibdev		Infiniband device
 * @ret rc		Return status code
 */
static int hermon_opreq_action ( struct hermon *hermon )
{
	struct ib_device *ibdev;
	unsigned int port;
	struct hermonprm_mcg_entry mcg;
	struct hermonprm_eth_mgi mgi;
	struct hermonprm_get_op_req get_op_req;
	struct ib_multicast_gid *mgid;
	struct ib_queue_pair qp;
	int rc;

	if ( ( rc = hermon_cmd_get_op_req ( hermon, 0, 0,
					    &get_op_req ) ) != 0 ) {
	  ERROR ( "ConnectX3 %p could not get op request %s\n",
		       hermon, strerror ( rc ) );
		return rc;
	}

	memcpy ( &mcg, &get_op_req.u.dwords[8],
		 sizeof ( struct hermonprm_mcg_entry ) );
	qp.qpn = MLX_GET ( &mcg, qp[0].qpn );
	memcpy ( &mgi, &get_op_req.u.dwords[12],
		 sizeof ( struct hermonprm_eth_mgi ) );
	port = MLX_GET ( &mgi, portnum );

	ibdev = hermon->port[port - 1].ibdev;
	if ( ibdev->protocol == HERMON_PROT_ETH ) {
		MLX_SET ( &mgi, vep_num, ibdev->vep_number );
	}

	switch ( MLX_GET ( &get_op_req , request_type ) ) {
	case HERMON_OPREQ_ADD_TO_MCG:
		if ( MLX_GET ( &get_op_req, mcg.hdr.member_remove ) ) {
			hermon_mcast_detach
				( ibdev, &qp, ( union ib_gid * ) &mgi );
		} else {
			if ( ( rc = hermon_mcast_attach
			     ( ibdev, &qp, ( union ib_gid * ) &mgi ) ) != 0 ) {
			  ERROR ( "ConnectX3 %p QPN %lx could not "
				       " attach: %s\n", hermon, qp.qpn,
				       strerror ( rc ) );
				return rc;
			}

			/* Add to software multicast GID list */
			mgid = zalloc ( sizeof ( *mgid ) );
			if ( ! mgid ) {
				return -ENOMEM;
			}
			memcpy ( &mgid->gid, &mgi, sizeof ( mgid->gid ) );
			mgid->protocol = ibdev->protocol;
			mgid->qpn = qp.qpn;
			list_add ( &mgid->list, &hermon->ncsi_mgids );
		}
		break;
	default:
	  ERROR ( "ConnectX3 %p Unrecognized NCSI event\n", hermon );
		break;
	}

	if ( ( rc = hermon_cmd_get_op_req
				       ( hermon, 1, 0, &get_op_req ) ) != 0 ) {
	  ERROR ( "ConnectX3 %p could not get op request %s\n",
		       hermon, strerror ( rc ) );
		return rc;
	}

	return	0;
}

/**
 * Poll event queue
 *
 * @v ibdev		Infiniband device
 */
static void hermon_poll_eq ( struct ib_device *ibdev ) {
	struct hermon *hermon = ib_get_drvdata ( ibdev );
	struct hermon_event_queue *hermon_eq = &hermon->eq;
	union hermonprm_event_entry *eqe;
	union hermonprm_doorbell_register db_reg;
	unsigned int eqe_idx_mask;
	unsigned int event_type;

	/* No event is generated upon reaching INIT, so we must poll
	 * separately for link state changes while we remain DOWN.
	 */
	if ( ib_is_open ( ibdev ) &&
	     ( ibdev->port_state == IB_PORT_STATE_DOWN ) ) {
		ib_smc_update ( ibdev, hermon_mad );
	}

	/* Poll event queue */
	while ( 1 ) {
		/* Look for event entry */
		eqe_idx_mask = ( HERMON_NUM_EQES - 1 );
		eqe = &hermon_eq->eqe[hermon_eq->next_idx & eqe_idx_mask];
		if ( MLX_GET ( &eqe->generic, owner ) ^
		     ( ( hermon_eq->next_idx & HERMON_NUM_EQES ) ? 1 : 0 ) ) {
			/* Entry still owned by hardware; end of poll */
			break;
		}
		DBGCP ( hermon, "ConnectX3 %p EQN %lx event:\n",
			hermon, hermon_eq->eqn );
		DBGCP_HDA ( hermon, virt_to_phys ( eqe ),
			    eqe, sizeof ( *eqe ) );
		poll_verbosity = 1;
		/* Handle event */
		event_type = MLX_GET ( &eqe->generic, event_type );
		switch ( event_type ) {
		case HERMON_EV_PORT_STATE_CHANGE:
			hermon_event_port_state_change ( hermon, eqe );
			break;
		case HERMON_EV_PORT_MGMNT_CHANGE:
			ib_smc_update ( ibdev, hermon_mad );
			break;
		case HERMON_EV_TYPE_OP_REQUIRED:
			hermon_opreq_action ( hermon );
			break;
		default:
			DBGC ( hermon, "ConnectX3 %p EQN %lx unrecognised event "
			       "type %x:\n",
			       hermon, hermon_eq->eqn, event_type );
			DBGC_HDA ( hermon, virt_to_phys ( eqe ),
				   eqe, sizeof ( *eqe ) );
			break;
		}

		/* Update event queue's index */
		hermon_eq->next_idx++;

		/* Ring doorbell */
		MLX_FILL_1 ( &db_reg.event, 0,
			     ci, ( hermon_eq->next_idx & 0x00ffffffUL ) );
		WRITE_REG (hermon, db_reg.dword[0], hermon_eq->doorbell );
	}
}

/***************************************************************************
 *
 * Firmware control
 *
 ***************************************************************************
 */

/**
 * Map virtual to physical address for firmware usage
 *
 * @v hermon		ConnectX3 device
 * @v map		Mapping function
 * @v va		Virtual address
 * @v pa		Physical address
 * @v len		Length of region
 * @ret rc		Return status code
 */
static int hermon_map_vpm ( struct hermon *hermon,
			    int ( *map ) ( struct hermon *hermon,
			    const struct hermonprm_virtual_physical_mapping* ),
			    uint64_t va, physaddr_t pa, size_t len ) {
	struct hermonprm_virtual_physical_mapping mapping;
	physaddr_t start;
	physaddr_t low;
	physaddr_t high;
	physaddr_t end;
	size_t size;
	int rc;

	/* Sanity checks */
	assert ( ( va & ( HERMON_PAGE_SIZE - 1 ) ) == 0 );
	assert ( ( pa & ( HERMON_PAGE_SIZE - 1 ) ) == 0 );
	assert ( ( len & ( HERMON_PAGE_SIZE - 1 ) ) == 0 );

	/* Calculate starting points */
	start = pa;
	end = ( start + len );
	size = ( 1UL << ( fls ( start ^ end ) - 1 ) );
	low = high = ( end & ~( size - 1 ) );
	assert ( start < low );
	assert ( high <= end );

	/* Map blocks in descending order of size */
	while ( size >= HERMON_PAGE_SIZE ) {

		/* Find the next candidate block */
		if ( ( low - size ) >= start ) {
			low -= size;
			pa = low;
		} else if ( ( high + size ) <= end ) {
			pa = high;
			high += size;
		} else {
			size >>= 1;
			continue;
		}
		assert ( ( va & ( size - 1 ) ) == 0 );
		assert ( ( pa & ( size - 1 ) ) == 0 );

		/* Map this block */
		memset ( &mapping, 0, sizeof ( mapping ) );
		MLX_FILL_1 ( &mapping, 0, va_h, ( va >> 32 ) );
		MLX_FILL_1 ( &mapping, 1, va_l, ( va >> 12 ) );
		MLX_FILL_H ( &mapping, 2, pa_h, pa );
		MLX_FILL_2 ( &mapping, 3,
			     log2size, ( ( fls ( size ) - 1 ) - 12 ),
			     pa_l, ( pa >> 12 ) );
		if ( ( rc = map ( hermon, &mapping ) ) != 0 ) {
			ERROR ( "ConnectX3 %p could not map %08llx+%x to "
			       "%08lx: %s\n",
			       hermon, va, size, pa, strerror ( rc ) );
			return rc;
		}
		va += size;
	}
	assert ( low == start );
	assert ( high == end );

	return 0;
}

/**
 * Start firmware running
 *
 * @v hermon		ConnectX3 device
 * @ret rc		Return status code
 */
static int hermon_start_firmware ( struct hermon *hermon ) {
	struct hermonprm_query_fw fw;
	unsigned int fw_pages;
	size_t fw_len;
	physaddr_t fw_base;
	int rc;

	/* Get firmware parameters */
	if ( ( rc = hermon_cmd_query_fw ( hermon, &fw ) ) != 0 ) {
		ERROR ( "ConnectX3 %p could not query firmware: %s\n",
		       hermon, strerror ( rc ) );
		goto err_query_fw;
	}
	DBGC ( hermon, "ConnectX3 %p firmware version %d.%d.%d\n", hermon,
	       MLX_GET ( &fw, fw_rev_major ), MLX_GET ( &fw, fw_rev_minor ),
	       MLX_GET ( &fw, fw_rev_subminor ) );
	fw_pages = MLX_GET ( &fw, fw_pages );
	DBGC ( hermon, "ConnectX3 %p requires %d pages (%d kB) for firmware\n",
	       hermon, fw_pages, ( fw_pages * 4 ) );

	/* Allocate firmware pages and map firmware area */
	fw_len = ( fw_pages * HERMON_PAGE_SIZE );
	if ( ! hermon->firmware_area ) {
		hermon->firmware_len = fw_len;
		hermon->firmware_area = (userptr_t)umalloc ( hermon->firmware_len );
		if ( ! hermon->firmware_area ) {
			rc = -ENOMEM;
			goto err_alloc_fa;
		}
	} else {
		assert ( hermon->firmware_len == fw_len );
	}
	fw_base = user_to_phys ( hermon->firmware_area, 0 );
	DBGC ( hermon, "ConnectX3 %p firmware area at physical [%08lx,%08lx)\n",
	       hermon, fw_base, ( fw_base + fw_len ) );
	if ( ( rc = hermon_map_vpm ( hermon, hermon_cmd_map_fa,
				     0, fw_base, fw_len ) ) != 0 ) {
		ERROR ( "ConnectX3 %p could not map firmware: %s\n",
		       hermon, strerror ( rc ) );
		goto err_map_fa;
	}

	/* Start firmware */
	if ( ( rc = hermon_cmd_run_fw ( hermon ) ) != 0 ) {
		ERROR ( "ConnectX3 %p could not run firmware: %s\n",
		       hermon, strerror ( rc ) );
		goto err_run_fw;
	}

	DBGC ( hermon, "ConnectX3 %p firmware started\n", hermon );
	return 0;

 err_run_fw:
 err_map_fa:
	hermon_cmd_unmap_fa ( hermon );
 err_alloc_fa:
 err_query_fw:
	return rc;
}

/**
 * Stop firmware running
 *
 * @v hermon		ConnectX3 device
 */
static void hermon_stop_firmware ( struct hermon *hermon ) {
	int rc;

	if ( ( rc = hermon_cmd_unmap_fa ( hermon ) ) != 0 ) {
		ERROR ( "ConnectX3 %p FATAL could not stop firmware: %s\n",
		       hermon, strerror ( rc ) );
		/* Leak memory and return; at least we avoid corruption */
		hermon->firmware_area = UNULL;
		return;
	}
}

/***************************************************************************
 *
 * Infinihost Context Memory management
 *
 ***************************************************************************
 */

/**
 * Get device limits
 *
 * @v hermon		ConnectX3 device
 * @ret rc		Return status code
 */
static int hermon_get_cap ( struct hermon *hermon ) {
	struct hermonprm_query_dev_cap dev_cap;
	int rc;

	if ( ( rc = hermon_cmd_query_dev_cap ( hermon, &dev_cap ) ) != 0 ) {
		DBGC ( hermon, "ConnectX3 %p could not get device limits: %s\n",
		       hermon, strerror ( rc ) );
		return rc;
	}

	hermon->cap.cmpt_entry_size = MLX_GET ( &dev_cap, c_mpt_entry_sz );
	hermon->cap.reserved_qps =
		( 1 << MLX_GET ( &dev_cap, log2_rsvd_qps ) );
	hermon->cap.qpc_entry_size = MLX_GET ( &dev_cap, qpc_entry_sz );
	hermon->cap.altc_entry_size = MLX_GET ( &dev_cap, altc_entry_sz );
	hermon->cap.auxc_entry_size = MLX_GET ( &dev_cap, aux_entry_sz );
	hermon->cap.reserved_srqs =
		( 1 << MLX_GET ( &dev_cap, log2_rsvd_srqs ) );
	hermon->cap.srqc_entry_size = MLX_GET ( &dev_cap, srq_entry_sz );
	hermon->cap.reserved_cqs =
		( 1 << MLX_GET ( &dev_cap, log2_rsvd_cqs ) );
	hermon->cap.cqc_entry_size = MLX_GET ( &dev_cap, cqc_entry_sz );
	hermon->cap.reserved_eqs = MLX_GET ( &dev_cap, num_rsvd_eqs );
	if ( hermon->cap.reserved_eqs == 0 ) {
		/* Backward compatibility */
		hermon->cap.reserved_eqs =
			( 1 << MLX_GET ( &dev_cap, log2_rsvd_eqs ) );
	}
	hermon->cap.eqc_entry_size = MLX_GET ( &dev_cap, eqc_entry_sz );
	hermon->cap.reserved_mtts =
		( 1 << MLX_GET ( &dev_cap, log2_rsvd_mtts ) );
	hermon->cap.mtt_entry_size = MLX_GET ( &dev_cap, mtt_entry_sz );
	hermon->cap.reserved_mrws =
		( 1 << MLX_GET ( &dev_cap, log2_rsvd_mrws ) );
	hermon->cap.dmpt_entry_size = MLX_GET ( &dev_cap, d_mpt_entry_sz );
	hermon->cap.reserved_uars = MLX_GET ( &dev_cap, num_rsvd_uars );
	hermon->cap.dpdp = MLX_GET ( &dev_cap, dpdp );
	hermon->cap.vep_uc_steering		= MLX_GET ( &dev_cap, vep_uc_steering );
	hermon->cap.vep_mc_steering		= MLX_GET ( &dev_cap, vep_mc_steering );
	hermon->cap.nv_mem_Access_supported	= MLX_GET( &dev_cap, flash_nv_config);
	hermon->cap.ncsi_lag_mode 		= MLX_GET( &dev_cap, ncsi_lag_mode);

	return 0;
}

/**
 * Align ICM table
 *
 * @v icm_offset	Current ICM offset
 * @v len		ICM table length
 * @ret icm_offset	ICM offset
 */
static uint64_t icm_align ( uint64_t icm_offset, size_t len ) {

	/* Round up to a multiple of the table size */
	assert ( len == ( 1UL << ( fls ( len ) - 1 ) ) );
	return ( ( icm_offset + len - 1 ) & ~( ( ( uint64_t ) len ) - 1 ) );
}

/**
 * Map ICM (allocating if necessary)
 *
 * @v hermon		ConnectX3 device
 * @v init_hca		INIT_HCA structure to fill in
 * @ret rc		Return status code
 */
static int hermon_map_icm ( struct hermon *hermon,
			    struct hermonprm_init_hca *init_hca ) {
	struct hermonprm_scalar_parameter icm_size;
	struct hermonprm_scalar_parameter icm_aux_size;
	uint64_t icm_offset = 0;
	unsigned int log_num_qps, log_num_srqs, log_num_cqs, log_num_eqs;
	unsigned int log_num_mtts, log_num_mpts, log_num_mcs;
	size_t cmpt_max_len;
	size_t icm_len, icm_aux_len;
	size_t len;
	physaddr_t icm_phys;
	int i;
	int rc;

	/*
	 * Start by carving up the ICM virtual address space
	 *
	 */

	/* Calculate number of each object type within ICM */
	log_num_qps = fls ( hermon->cap.reserved_qps +
			    HERMON_RSVD_SPECIAL_QPS + HERMON_MAX_QPS - 1 );
	log_num_srqs = fls ( hermon->cap.reserved_srqs - 1 );
	log_num_cqs = fls ( hermon->cap.reserved_cqs + HERMON_MAX_CQS - 1 );
	log_num_eqs = fls ( hermon->cap.reserved_eqs + HERMON_MAX_EQS - 1 );
	log_num_mtts = fls ( hermon->cap.reserved_mtts + HERMON_MAX_MTTS - 1 );
	log_num_mpts = fls ( hermon->cap.reserved_mrws + 1 - 1 );
	log_num_mcs = HERMON_LOG_MULTICAST_HASH_SIZE;

	/* ICM starts with the cMPT tables, which are sparse */
	cmpt_max_len = ( HERMON_CMPT_MAX_ENTRIES *
			 ( ( uint64_t ) hermon->cap.cmpt_entry_size ) );
	len = ( ( ( ( 1 << log_num_qps ) * hermon->cap.cmpt_entry_size ) +
		  HERMON_PAGE_SIZE - 1 ) & ~( HERMON_PAGE_SIZE - 1 ) );
	hermon->icm_map[HERMON_ICM_QP_CMPT].offset = icm_offset;
	hermon->icm_map[HERMON_ICM_QP_CMPT].len = len;
	icm_offset += cmpt_max_len;
	len = ( ( ( ( 1 << log_num_srqs ) * hermon->cap.cmpt_entry_size ) +
		  HERMON_PAGE_SIZE - 1 ) & ~( HERMON_PAGE_SIZE - 1 ) );
	hermon->icm_map[HERMON_ICM_SRQ_CMPT].offset = icm_offset;
	hermon->icm_map[HERMON_ICM_SRQ_CMPT].len = len;
	icm_offset += cmpt_max_len;
	len = ( ( ( ( 1 << log_num_cqs ) * hermon->cap.cmpt_entry_size ) +
		  HERMON_PAGE_SIZE - 1 ) & ~( HERMON_PAGE_SIZE - 1 ) );
	hermon->icm_map[HERMON_ICM_CQ_CMPT].offset = icm_offset;
	hermon->icm_map[HERMON_ICM_CQ_CMPT].len = len;
	icm_offset += cmpt_max_len;
	len = ( ( ( ( 1 << log_num_eqs ) * hermon->cap.cmpt_entry_size ) +
		  HERMON_PAGE_SIZE - 1 ) & ~( HERMON_PAGE_SIZE - 1 ) );
	hermon->icm_map[HERMON_ICM_EQ_CMPT].offset = icm_offset;
	hermon->icm_map[HERMON_ICM_EQ_CMPT].len = len;
	icm_offset += cmpt_max_len;

	hermon->icm_map[HERMON_ICM_OTHER].offset = icm_offset;

	/* Queue pair contexts */
	len = ( ( 1 << log_num_qps ) * hermon->cap.qpc_entry_size );
	icm_offset = icm_align ( icm_offset, len );
	MLX_FILL_1 ( init_hca, 12,
		     qpc_eec_cqc_eqc_rdb_parameters.qpc_base_addr_h,
		     ( icm_offset >> 32 ) );
	MLX_FILL_2 ( init_hca, 13,
		     qpc_eec_cqc_eqc_rdb_parameters.qpc_base_addr_l,
		     ( icm_offset >> 5 ),
		     qpc_eec_cqc_eqc_rdb_parameters.log_num_of_qp,
		     log_num_qps );
	DBGC ( hermon, "ConnectX3 %p ICM QPC is %d x %x at [%08llx,%08llx)\n",
	       hermon, ( 1 << log_num_qps ), hermon->cap.qpc_entry_size,
	       icm_offset, ( icm_offset + len ) );
	icm_offset += len;

	/* Extended alternate path contexts */
	len = ( ( 1 << log_num_qps ) * hermon->cap.altc_entry_size );

	icm_offset = icm_align ( icm_offset, len );
	MLX_FILL_1 ( init_hca, 24,
		     qpc_eec_cqc_eqc_rdb_parameters.altc_base_addr_h,
		     ( icm_offset >> 32 ) );
	MLX_FILL_1 ( init_hca, 25,
		     qpc_eec_cqc_eqc_rdb_parameters.altc_base_addr_l,
		     icm_offset );
	DBGC ( hermon, "ConnectX3 %p ICM ALTC is %d x %x at [%08llx,%08llx)\n",
	       hermon, ( 1 << log_num_qps ), hermon->cap.altc_entry_size,
	       icm_offset, ( icm_offset + len ) );
	icm_offset += len;

	/* Extended auxiliary contexts */
	len = ( ( 1 << log_num_qps ) * hermon->cap.auxc_entry_size );
	icm_offset = icm_align ( icm_offset, len );
	MLX_FILL_1 ( init_hca, 28,
		     qpc_eec_cqc_eqc_rdb_parameters.auxc_base_addr_h,
		     ( icm_offset >> 32 ) );
	MLX_FILL_1 ( init_hca, 29,
		     qpc_eec_cqc_eqc_rdb_parameters.auxc_base_addr_l,
		     icm_offset );
	DBGC ( hermon, "ConnectX3 %p ICM AUXC is %d x %x at [%08llx,%08llx)\n",
	       hermon, ( 1 << log_num_qps ), hermon->cap.auxc_entry_size,
	       icm_offset, ( icm_offset + len ) );
	icm_offset += len;

	/* Shared receive queue contexts */
	len = ( ( 1 << log_num_srqs ) * hermon->cap.srqc_entry_size );
	icm_offset = icm_align ( icm_offset, len );
	MLX_FILL_1 ( init_hca, 18,
		     qpc_eec_cqc_eqc_rdb_parameters.srqc_base_addr_h,
		     ( icm_offset >> 32 ) );
	MLX_FILL_2 ( init_hca, 19,
		     qpc_eec_cqc_eqc_rdb_parameters.srqc_base_addr_l,
		     ( icm_offset >> 5 ),
		     qpc_eec_cqc_eqc_rdb_parameters.log_num_of_srq,
		     log_num_srqs );
	DBGC ( hermon, "ConnectX3 %p ICM SRQC is %d x %x at [%08llx,%08llx)\n",
	       hermon, ( 1 << log_num_srqs ), hermon->cap.srqc_entry_size,
	       icm_offset, ( icm_offset + len ) );
	icm_offset += len;

	/* Completion queue contexts */
	len = ( ( 1 << log_num_cqs ) * hermon->cap.cqc_entry_size );
	icm_offset = icm_align ( icm_offset, len );
	MLX_FILL_1 ( init_hca, 20,
		     qpc_eec_cqc_eqc_rdb_parameters.cqc_base_addr_h,
		     ( icm_offset >> 32 ) );
	MLX_FILL_2 ( init_hca, 21,
		     qpc_eec_cqc_eqc_rdb_parameters.cqc_base_addr_l,
		     ( icm_offset >> 5 ),
		     qpc_eec_cqc_eqc_rdb_parameters.log_num_of_cq,
		     log_num_cqs );
	DBGC ( hermon, "ConnectX3 %p ICM CQC is %d x %x at [%08llx,%08llx)\n",
	       hermon, ( 1 << log_num_cqs ), hermon->cap.cqc_entry_size,
	       icm_offset, ( icm_offset + len ) );
	icm_offset += len;

	/* Event queue contexts */
	len = ( ( 1 << log_num_eqs ) * hermon->cap.eqc_entry_size );
	icm_offset = icm_align ( icm_offset, len );
	MLX_FILL_1 ( init_hca, 32,
		     qpc_eec_cqc_eqc_rdb_parameters.eqc_base_addr_h,
		     ( icm_offset >> 32 ) );
	MLX_FILL_2 ( init_hca, 33,
		     qpc_eec_cqc_eqc_rdb_parameters.eqc_base_addr_l,
		     ( icm_offset >> 5 ),
		     qpc_eec_cqc_eqc_rdb_parameters.log_num_of_eq,
		     log_num_eqs );
	DBGC ( hermon, "ConnectX3 %p ICM EQC is %d x %x at [%08llx,%08llx)\n",
	       hermon, ( 1 << log_num_eqs ), hermon->cap.eqc_entry_size,
	       icm_offset, ( icm_offset + len ) );
	icm_offset += len;

	/* Memory translation table */
	len = ( ( 1 << log_num_mtts ) * hermon->cap.mtt_entry_size );
	icm_offset = icm_align ( icm_offset, len );
	MLX_FILL_1 ( init_hca, 64,
		     tpt_parameters.mtt_base_addr_h, ( icm_offset >> 32 ) );
	MLX_FILL_1 ( init_hca, 65,
		     tpt_parameters.mtt_base_addr_l, icm_offset );
	DBGC ( hermon, "ConnectX3 %p ICM MTT is %d x %x at [%08llx,%08llx)\n",
	       hermon, ( 1 << log_num_mtts ), hermon->cap.mtt_entry_size,
	       icm_offset, ( icm_offset + len ) );
	icm_offset += len;

	/* Memory protection table */
	len = ( ( 1 << log_num_mpts ) * hermon->cap.dmpt_entry_size );
	icm_offset = icm_align ( icm_offset, len );
	MLX_FILL_1 ( init_hca, 60,
		     tpt_parameters.dmpt_base_adr_h, ( icm_offset >> 32 ) );
	MLX_FILL_1 ( init_hca, 61,
		     tpt_parameters.dmpt_base_adr_l, icm_offset );
	MLX_FILL_1 ( init_hca, 62,
		     tpt_parameters.log_dmpt_sz, log_num_mpts );
	DBGC ( hermon, "ConnectX3 %p ICM DMPT is %d x %x at [%08llx,%08llx)\n",
	       hermon, ( 1 << log_num_mpts ), hermon->cap.dmpt_entry_size,
	       icm_offset, ( icm_offset + len ) );
	icm_offset += len;

	/* Multicast table */
	len = ( ( 1 << log_num_mcs ) * sizeof ( struct hermonprm_mcg_entry ) );
	icm_offset = icm_align ( icm_offset, len );
	MLX_FILL_1 ( init_hca, 48,
		     multicast_parameters.mc_base_addr_h,
		     ( icm_offset >> 32 ) );
	MLX_FILL_1 ( init_hca, 49,
		     multicast_parameters.mc_base_addr_l, icm_offset );
	MLX_FILL_1 ( init_hca, 52,
		     multicast_parameters.log_mc_table_entry_sz,
		     fls ( sizeof ( struct hermonprm_mcg_entry ) - 1 ) );
	MLX_FILL_1 ( init_hca, 53,
		     multicast_parameters.log_mc_table_hash_sz,
		     log_num_mcs - 1 );
	MLX_FILL_2 ( init_hca, 54,
		     multicast_parameters.log_mc_table_sz, log_num_mcs,
		     multicast_parameters.uc_group_steering,
		     ( hermon->cap.vep_uc_steering ? 1 : 0 ) );
	DBGC ( hermon, "ConnectX3 %p ICM MC is %d x %x at [%08llx,%08llx)\n",
	       hermon, ( 1 << log_num_mcs ),
	       sizeof ( struct hermonprm_mcg_entry ),
	       icm_offset, ( icm_offset + len ) );
	icm_offset += len;


	hermon->icm_map[HERMON_ICM_OTHER].len =
		( icm_offset - hermon->icm_map[HERMON_ICM_OTHER].offset );

	/*
	 * Allocate and map physical memory for (portions of) ICM
	 *
	 * Map is:
	 *   ICM AUX area (aligned to its own size)
	 *   cMPT areas
	 *   Other areas
	 */

	/* Calculate physical memory required for ICM */
	icm_len = 0;
	for ( i = 0 ; i < HERMON_ICM_NUM_REGIONS ; i++ ) {
		icm_len += hermon->icm_map[i].len;
	}

	/* Get ICM auxiliary area size */
	memset ( &icm_size, 0, sizeof ( icm_size ) );
	MLX_FILL_1 ( &icm_size, 0, value_hi, ( icm_offset >> 32 ) );
	MLX_FILL_1 ( &icm_size, 1, value, icm_offset );
	if ( ( rc = hermon_cmd_set_icm_size ( hermon, &icm_size,
					      &icm_aux_size ) ) != 0 ) {
		ERROR ( "ConnectX3 %p could not set ICM size: %s\n",
		       hermon, strerror ( rc ) );
		goto err_set_icm_size;
	}
	icm_aux_len = ( MLX_GET ( &icm_aux_size, value ) * HERMON_PAGE_SIZE );

	/* Allocate ICM data and auxiliary area */
	DBGC ( hermon, "ConnectX3 %p requires %zd kB ICM and %zd kB AUX ICM\n",
	       hermon, ( icm_len / 1024 ), ( icm_aux_len / 1024 ) );
	if ( ! hermon->icm ) {
		hermon->icm_len = icm_len;
		hermon->icm_aux_len = icm_aux_len;
		hermon->icm = (userptr_t)umalloc ( hermon->icm_aux_len + hermon->icm_len );
		if ( ! hermon->icm ) {
			rc = -ENOMEM;
			goto err_alloc;
		}
	} else {
		assert ( hermon->icm_len == icm_len );
		assert ( hermon->icm_aux_len == icm_aux_len );
	}
	icm_phys = user_to_phys ( hermon->icm, 0 );

	/* Map ICM auxiliary area */
	DBGC ( hermon, "ConnectX3 %p mapping ICM AUX => %08lx\n",
	       hermon, icm_phys );
	if ( ( rc = hermon_map_vpm ( hermon, hermon_cmd_map_icm_aux,
				     0, icm_phys, icm_aux_len ) ) != 0 ) {
		ERROR ( "ConnectX3 %p could not map AUX ICM: %s\n",
		       hermon, strerror ( rc ) );
		goto err_map_icm_aux;
	}
	icm_phys += icm_aux_len;

	/* MAP ICM area */
	for ( i = 0 ; i < HERMON_ICM_NUM_REGIONS ; i++ ) {
		DBGC ( hermon, "ConnectX3 %p mapping ICM %llx+%x => %08lx\n",
		       hermon, hermon->icm_map[i].offset,
		       hermon->icm_map[i].len, icm_phys );
		if ( ( rc = hermon_map_vpm ( hermon, hermon_cmd_map_icm,
					     hermon->icm_map[i].offset,
					     icm_phys,
					     hermon->icm_map[i].len ) ) != 0 ){
			ERROR ( "ConnectX3 %p could not map ICM: %s\n",
			       hermon, strerror ( rc ) );
			goto err_map_icm;
		}
		icm_phys += hermon->icm_map[i].len;
	}

	return 0;

 err_map_icm:
	assert ( i == 0 ); /* We don't handle partial failure at present */
 err_map_icm_aux:
	hermon_cmd_unmap_icm_aux ( hermon );
 err_alloc:
 err_set_icm_size:
	return rc;
}

/**
 * Unmap ICM
 *
 * @v hermon		ConnectX3 device
 */
static void hermon_unmap_icm ( struct hermon *hermon ) {
	struct hermonprm_scalar_parameter unmap_icm;
	int i;

	for ( i = ( HERMON_ICM_NUM_REGIONS - 1 ) ; i >= 0 ; i-- ) {
		memset ( &unmap_icm, 0, sizeof ( unmap_icm ) );
		MLX_FILL_1 ( &unmap_icm, 0, value_hi,
			     ( hermon->icm_map[i].offset >> 32 ) );
		MLX_FILL_1 ( &unmap_icm, 1, value,
			     hermon->icm_map[i].offset );
		hermon_cmd_unmap_icm ( hermon,
				       ( 1 << fls ( ( hermon->icm_map[i].len /
						      HERMON_PAGE_SIZE ) - 1)),
				       &unmap_icm );
	}
	hermon_cmd_unmap_icm_aux ( hermon );
}

/***************************************************************************
 *
 * Initialisation and teardown
 *
 ***************************************************************************
 */
/**
 * Reset device
 *
 * @v hermon		ConnectX3 device
 */
static void hermon_reset ( struct hermon *hermon,
			   unsigned int reset_type ) {
  EFI_PCI_IO_PROTOCOL *pci  = hermon->pci;
	struct pci_config_backup backup;
	static const uint8_t backup_exclude[] =
		PCI_CONFIG_BACKUP_EXCLUDE ( 0x58, 0x5c );

	mdelay ( HERMON_RESET_WAIT_TIME_MS );
	/* Perform device reset and preserve PCI configuration */
	memset(&backup, 0, sizeof(struct pci_config_backup));
	pci_backup ( pci, &backup, backup_exclude );
	WRITE_REG (hermon, reset_type,
		 ( hermon->config + HERMON_RESET_OFFSET ) );
	mdelay ( HERMON_RESET_WAIT_TIME_MS );
	pci_restore ( pci, &backup, backup_exclude );

	/* Reset command interface toggle */
	hermon->toggle = 0;
}

/**
 * Set up memory protection table
 *
 * @v hermon		ConnectX3 device
 * @ret rc		Return status code
 */
static int hermon_setup_mpt ( struct hermon *hermon ) {
	struct hermonprm_mpt mpt;
	uint32_t key;
	int rc;

	/* Derive key */
	key = ( hermon->cap.reserved_mrws | HERMON_MKEY_PREFIX );
	hermon->lkey = ( ( key << 8 ) | ( key >> 24 ) );

	/* Initialise memory protection table */
	memset ( &mpt, 0, sizeof ( mpt ) );
	MLX_FILL_7 ( &mpt, 0,
		     atomic, 1,
		     rw, 1,
		     rr, 1,
		     lw, 1,
		     lr, 1,
		     pa, 1,
		     r_w, 1 );
	MLX_FILL_1 ( &mpt, 2, mem_key, key );
	MLX_FILL_1 ( &mpt, 3,
		     pd, HERMON_GLOBAL_PD );
	MLX_FILL_1 ( &mpt, 10, len64, 1 );
	if ( ( rc = hermon_cmd_sw2hw_mpt ( hermon,
					   hermon->cap.reserved_mrws,
					   &mpt ) ) != 0 ) {
		ERROR ( "ConnectX3 %p could not set up MPT: %s\n",
		       hermon, strerror ( rc ) );
		return rc;
	}

	return 0;
}

/**
 * Configure special queue pairs
 *
 * @v hermon		ConnectX3 device
 * @ret rc		Return status code
 */
static int hermon_configure_special_qps ( struct hermon *hermon ) {
	int rc;

	/* Special QP block must be aligned on its own size */
	hermon->special_qpn_base = ( ( hermon->cap.reserved_qps +
				       HERMON_NUM_SPECIAL_QPS - 1 )
				     & ~( HERMON_NUM_SPECIAL_QPS - 1 ) );
	hermon->qpn_base = ( hermon->special_qpn_base +
			     HERMON_NUM_SPECIAL_QPS );
	DBGC ( hermon, "ConnectX3 %p special QPs at [%lx,%lx]\n", hermon,
	       hermon->special_qpn_base, ( hermon->qpn_base - 1 ) );

	/* Issue command to configure special QPs */
	if ( ( rc = hermon_cmd_conf_special_qp ( hermon, 0x00,
					hermon->special_qpn_base ) ) != 0 ) {
		ERROR ( "ConnectX3 %p could not configure special QPs: "
		       "%s\n", hermon, strerror ( rc ) );
		return rc;
	}

	return 0;
}

/**
 * Start ConnectX3 device
 *
 * @v hermon		ConnectX3 device
 * @v running		Firmware is already running
 * @ret rc		Return status code
 */
static int hermon_start ( struct hermon *hermon, int running ) {
	struct hermonprm_init_hca init_hca;
	unsigned int i;
	int rc;

	/* Start firmware if not already running */
	if ( ! running ) {
		hermon_reset ( hermon, HERMON_RESET_START );
		if ( ( rc = hermon_start_firmware ( hermon ) ) != 0 )
			goto err_start_firmware;
	}

	/* Allocate and map ICM */
	memset ( &init_hca, 0, sizeof ( init_hca ) );
	if ( ( rc = hermon_map_icm ( hermon, &init_hca ) ) != 0 )
		goto err_map_icm;

	/* Initialise HCA */
	MLX_FILL_1 ( &init_hca, 0, version, 0x02 /* "Must be 0x02" */ );
	MLX_FILL_1 ( &init_hca, 5, udp, 1 );
	MLX_FILL_1 ( &init_hca, 74, uar_parameters.log_max_uars, 8 );
	if ( ( rc = hermon_cmd_init_hca ( hermon, &init_hca ) ) != 0 ) {
		ERROR ( "ConnectX3 %p could not initialise HCA: %s\n",
		       hermon, strerror ( rc ) );
		goto err_init_hca;
	}

	/* Set up memory protection */
	if ( ( rc = hermon_setup_mpt ( hermon ) ) != 0 )
		goto err_setup_mpt;
	for ( i = 0 ; i < hermon->num_ports ; i++ )
		hermon->port[i].ibdev->rdma_key = hermon->lkey;

	/* Set up event queue */
	if ( ( rc = hermon_create_eq ( hermon ) ) != 0 )
		goto err_create_eq;

	/* Configure special QPs */
	if ( ( rc = hermon_configure_special_qps ( hermon ) ) != 0 )
		goto err_conf_special_qps;

	hermon->mcg_aux_index = ( MC_TABLE_SIZE / 2 );
	INIT_LIST_HEAD ( &hermon->ncsi_mgids );

	return 0;

 err_conf_special_qps:
	hermon_destroy_eq ( hermon );
 err_create_eq:
 err_setup_mpt:
	hermon_cmd_close_hca ( hermon );
 err_init_hca:
	hermon_unmap_icm ( hermon );
 err_map_icm:
	hermon_stop_firmware ( hermon );
 err_start_firmware:
	return rc;
}

/**
 * Stop ConnectX3 device
 *
 * @v hermon		ConnectX3 device
 */
static void hermon_stop ( struct hermon *hermon ) {

	hermon_destroy_eq ( hermon );
	hermon_cmd_close_hca ( hermon );
	hermon_unmap_icm ( hermon );
	hermon_stop_firmware ( hermon );
	//hermon_reset ( hermon, be32_to_cpu ( HERMON_RESET_END ) );
	/* Reset command interface toggle */
	hermon->toggle = 0;
}

/**
 * Open ConnectX3 device
 *
 * @v hermon		ConnectX3 device
 * @ret rc		Return status code
 */
static int hermon_open ( struct hermon *hermon ) {
	int rc;

	/* Start device if applicable */
	if ( hermon->open_count == 0 ) {
		if ( ( rc = hermon_start ( hermon, 0 ) ) != 0 )
			return rc;
	}
	/* Increment open counter */
	hermon->open_count++;

	return 0;
}

/**
 * Close ConnectX3 device
 *
 * @v hermon		ConnectX3 device
 */
static void hermon_close ( struct hermon *hermon ) {

	/* Decrement open counter */
	assert ( hermon->open_count != 0 );
	hermon->open_count--;

	/* Stop device if applicable */
	if ( hermon->open_count == 0 )
		hermon_stop ( hermon );
}

/***************************************************************************
 *
 * Infiniband link-layer operations
 *
 ***************************************************************************
 */

/**
 * Initialise Infiniband link
 *
 * @v ibdev		Infiniband device
 * @ret rc		Return status code
 */
static int hermon_ib_open ( struct ib_device *ibdev ) {
	struct hermon *hermon = ib_get_drvdata ( ibdev );
	union hermonprm_set_port set_port;
	int rc;

	/* Open hardware */
	if ( ( rc = hermon_open ( hermon ) ) != 0 )
		goto err_open;

	/* Set port parameters */
	memset ( &set_port, 0, sizeof ( set_port ) );
	MLX_FILL_8 ( &set_port.ib, 0,
		     mmc, 1,
		     mvc, 1,
		     mp, 1,
		     mg, 1,
		     mtu_cap, IB_MTU_2048,
		     vl_cap, IB_VL_0,
		     rcm, 1,
		     lss, 1 );
	MLX_FILL_2 ( &set_port.ib, 10,
		     max_pkey, 1,
		     max_gid, 1 );
	MLX_FILL_1 ( &set_port.ib, 28,
		     link_speed_supported, 1 );
	if ( ( rc = hermon_cmd_set_port ( hermon, 0, ibdev->port,
					  &set_port ) ) != 0 ) {
		ERROR ( "ConnectX3 %p port %d could not set port: %s\n",
		       hermon, ibdev->port, strerror ( rc ) );
		goto err_set_port;
	}

	/* Initialise port */
	if ( ( rc = hermon_cmd_init_port ( hermon, ibdev->port ) ) != 0 ) {
		ERROR ( "ConnectX3 %p port %d could not initialise port: "
		       "%s\n", hermon, ibdev->port, strerror ( rc ) );
		goto err_init_port;
	}

	/* Update MAD parameters */
	ib_smc_update ( ibdev, hermon_mad );

	return 0;

 err_init_port:
 err_set_port:
	hermon_close ( hermon );
 err_open:
	return rc;
}

/**
 * Close Infiniband link
 *
 * @v ibdev		Infiniband device
 */
static void hermon_ib_close ( struct ib_device *ibdev ) {
	struct hermon *hermon = ib_get_drvdata ( ibdev );
	int rc;

	/* Close port */
	if ( ( rc = hermon_cmd_close_port ( hermon, ibdev->port ) ) != 0 ) {
		ERROR ( "ConnectX3 %p port %d could not close port: %s\n",
		       hermon, ibdev->port, strerror ( rc ) );
		/* Nothing we can do about this */
	}

	/* Close hardware */
	hermon_close ( hermon );
}

/**
 * Inform embedded subnet management agent of a received MAD
 *
 * @v ibdev		Infiniband device
 * @v mad		MAD
 * @ret rc		Return status code
 */
static int hermon_inform_sma ( struct ib_device *ibdev,
			       union ib_mad *mad ) {
	int rc;

	/* Send the MAD to the embedded SMA */
	if ( ( rc = hermon_mad ( ibdev, mad ) ) != 0 )
		return rc;

	/* Update parameters held in software */
	ib_smc_update ( ibdev, hermon_mad );

	return 0;
}

/**
 * Get number of physical ports
 *
 * @v ibdev		Infiniband device
 * @ret num		Return status code
 */
int hermon_num_phy_ports ( struct ib_device *ibdev ) {
	struct hermon *hermon = ib_get_drvdata ( ibdev );
	return hermon->num_ports;
}



/** ConnectX3 Infiniband operations */
static struct ib_device_operations hermon_ib_operations = {
	.create_cq	= hermon_create_cq,
	.destroy_cq	= hermon_destroy_cq,
	.create_qp	= hermon_create_qp,
	.modify_qp	= hermon_modify_qp,
	.destroy_qp	= hermon_destroy_qp,
	.post_send	= hermon_post_send,
	.post_recv	= hermon_post_recv,
	.poll_cq	= hermon_poll_cq,
	.poll_eq	= hermon_poll_eq,
	.open		= hermon_ib_open,
	.close		= hermon_ib_close,
	.mcast_attach	= hermon_mcast_attach,
	.mcast_detach	= hermon_mcast_detach,
	.set_port_info	= hermon_inform_sma,
	.set_pkey_table	= hermon_inform_sma,
	.num_phy_ports	= hermon_num_phy_ports,
};

/***************************************************************************
 *
 * Ethernet operation
 *
 ***************************************************************************
 */
int hermon_eth_add_steer ( struct ib_device *ibdev,
			   struct ib_queue_pair *eth_qp )
{
	struct hermonprm_eth_mgi mgi;
	int rc;

	/* Join broadcast mutlicast group */
	memset ( &mgi, 0, sizeof ( mgi ) );
	MLX_FILL_3 ( &mgi, 1, vep_num, ibdev->vep_number,
		     portnum, ibdev->port,
		     unicast, MLX4_MC_STEER );
	MLX_FILL_1 ( &mgi, 2, mac_h, 0xffff );
	MLX_FILL_1 ( &mgi, 3, mac_l, 0xffffffffUL );
	if ( ( rc = ib_mcast_attach
			  ( ibdev, eth_qp, ( union ib_gid * ) &mgi ) ) != 0 ) {
		ERROR ( "ConnectX3 %p QPN %lx could not attach to "
		       "multicast group: %s\n", ib_get_drvdata ( ibdev ), eth_qp->qpn,
		       strerror ( rc ) );
		return rc;
	}

	/* Add MAC to unicast group */
	memset ( &mgi, 0, sizeof ( mgi ) );
	MLX_FILL_3 ( &mgi, 1, vep_num, ibdev->vep_number,
		     portnum, ibdev->port,
		     unicast, MLX4_UC_STEER );
	MLX_FILL_1 ( &mgi, 2, mac_h, ibdev->eth_mac_h );
	MLX_FILL_1 ( &mgi, 3, mac_l, ibdev->eth_mac_l );
	if ( ( rc = ib_mcast_attach
			  ( ibdev, eth_qp, ( union ib_gid * ) &mgi ) ) != 0 ) {
		ERROR ( "ConnectX3 %p QPN %lx could not attach to "
		       "multicast group: %s\n", ib_get_drvdata ( ibdev ), eth_qp->qpn,
		       strerror ( rc ) );
		return rc;
	}

	return 0;
}

void hermon_eth_release_steer ( struct ib_device *ibdev,
				struct ib_queue_pair *eth_qp )
{
	union ib_gid gid;
	struct ib_multicast_gid *mgid;
	struct ib_multicast_gid *tmp;
	list_for_each_entry_safe ( mgid, tmp, &eth_qp->mgids, list ) {
		memcpy ( &gid, &mgid->gid, sizeof ( union ib_gid ) );
		hermon_mcast_detach ( ibdev, eth_qp, &gid );
		list_del(&mgid->list);
	}
}

/* Detach multicast groups used by NCSI */
void hermon_eth_ncsi_release_steer ( struct hermon *hermon )
{
	struct ib_queue_pair *tmp_qp;
	struct ib_device *tmp_ibdev;
	struct ib_multicast_gid *mgid;
	struct ib_multicast_gid *tmp;
	union ib_gid gid;

	tmp_ibdev = zalloc ( sizeof ( *tmp_ibdev ) );
	if ( ! tmp_ibdev ) {
		return;
	}
	tmp_qp = zalloc ( sizeof ( *tmp_qp ) );
	if ( ! tmp_qp ) {
		return;
	}
	tmp_ibdev->protocol = HERMON_PROT_ETH;
	ib_set_drvdata ( tmp_ibdev, hermon );

	list_for_each_entry_safe ( mgid, tmp, &hermon->ncsi_mgids, list ) {
		memcpy ( &gid, &mgid->gid, sizeof ( union ib_gid ) );
		tmp_qp->qpn = mgid->qpn;
		hermon_mcast_detach ( tmp_ibdev, tmp_qp, &gid );
	}

	free ( tmp_qp );
	free ( tmp_ibdev);
}

/**
 * Transmit packet via ConnectX3 Ethernet device
 *
 * @v netdev		Network device
 * @v iobuf		I/O buffer
 * @ret rc		Return status code
 */
static int hermon_eth_transmit ( struct hermon_port *port,
				 struct io_buffer *iobuf )
{
	struct ib_device	*ibdev	= port->ibdev;
	int rc;

	/* Transmit packet */
	if ( ( rc = ib_post_send ( ibdev, port->eth_qp, NULL,
				   iobuf ) ) != 0 ) {
		ERROR ( "ConnectX3 %p port %d could not transmit: %s\n",
		    ib_get_drvdata ( ibdev ), ibdev->port, strerror ( rc ) );
		return rc;
	}

	return 0;
}

/**
 * Handle ConnectX3 Ethernet device send completion
 *
 * @v ibdev		Infiniband device
 * @v qp		Queue pair
 * @v iobuf		I/O buffer
 * @v rc		Completion status code
 */
static void hermon_eth_complete_send ( struct ib_device *ibdev __unused,
				       struct ib_queue_pair *qp,
				       struct io_buffer *iobuf, int rc ) {
	TAG();
	free_iob(iobuf);
}

/**
 * Handle ConnectX3 Ethernet device receive completion
 *
 * @v ibdev		Infiniband device
 * @v qp		Queue pair
 * @v av		Address vector, or NULL
 * @v iobuf		I/O buffer
 * @v rc		Completion status code
 */
static void hermon_eth_complete_recv ( struct ib_device *ibdev __unused,
				       struct ib_queue_pair *qp,
				       struct ib_address_vector *av,
				       struct io_buffer *iobuf, int rc ) {
	//struct net_device *netdev = ib_qp_get_ownerdata ( qp );
  //struct hermon *hermon = ib_get_drvdata ( ibdev );
	/* Hand off to network layer */
	TAG("len = %x[%d]", iob_len(iobuf), rc);
	if (rc == 0)
	  Mellanox_Callback_GetReceiveData(ib_qp_get_ownerdata ( qp ), iobuf->data, iob_len(iobuf));
	free_iob(iobuf);
	TAG("Out of NetReceive");
}

/** ConnectX3 Ethernet device completion operations */
static struct ib_completion_queue_operations hermon_eth_cq_op = {
	.complete_send = hermon_eth_complete_send,
	.complete_recv = hermon_eth_complete_recv,
};

/**
 * Poll ConnectX3 Ethernet device
 *
 * @v netdev		Network device
 */
static int hermon_eth_poll ( struct hermon_port *port )
{
	struct ib_device *ibdev = port->ibdev;
	struct hermon *hermon = ib_get_drvdata ( ibdev );

	/* NetLoop will call eth_halt before its been opened */
	if (!hermon->open_count) {
		DBGC( hermon, "ConnectX3 %p hermon NIC is closed. Cowardly refuse to execute \n",
		      hermon, hermon_eth_poll);
		return 0;
	}


	ib_poll_eq ( ibdev );
	if (poll_verbosity)
		TAG("Out");
	poll_verbosity = 0;
	/* No one cares what's returned... */
	return 1;
}

/**
 * Open ConnectX3 Ethernet device
 *
 * @v netdev		Network device
 * @ret rc		Return status code
 */
static int hermon_eth_open ( struct hermon_port *port, void *priv_data)
{
	struct ib_device *ibdev		= port->ibdev;
	struct hermon *hermon		= ib_get_drvdata ( ibdev );
	union hermonprm_set_port set_port;
	int rc;

	TAG();
	/* Open hardware */
	if ( ( rc = hermon_open ( hermon ) ) != 0 )
		goto err_open;

	/* Allocate completion queue */
	port->eth_cq = ib_create_cq ( ibdev, HERMON_ETH_NUM_CQES,
				      &hermon_eth_cq_op );
	if ( ! port->eth_cq ) {
		ERROR ( "ConnectX3 %p port %d could not create completion "
		       "queue\n", hermon, ibdev->port );
		rc = -ENOMEM;
		goto err_create_cq;
	}

	TAG();
	/* Allocate queue pair */
	port->eth_qp = ib_create_qp ( ibdev, IB_QPT_ETH,
				      HERMON_ETH_NUM_SEND_WQES, port->eth_cq,
				      HERMON_ETH_NUM_RECV_WQES, port->eth_cq );
	if ( ! port->eth_qp ) {
		ERROR ( "ConnectX3 %p port %d could not create queue "
		       "pair\n", hermon, ibdev->port );
		rc = -ENOMEM;
		goto err_create_qp;
	}
	TAG();
	ib_qp_set_ownerdata ( port->eth_qp, priv_data );

	/* Activate queue pair */
	if ( ( rc = ib_modify_qp ( ibdev, port->eth_qp ) ) != 0 ) {
		ERROR ( "ConnectX3 %p port %d could not modify queue "
		       "pair: %s\n", hermon, ibdev->port, strerror ( rc ) );
		goto err_modify_qp;
	}
	TAG();

	/* Add steering */
	if ( ( rc = hermon_eth_add_steer ( ibdev, port->eth_qp ) ) != 0 ) {
		ERROR ( "ConnectX3 %p port %d failed to add steering:"
		       " %s\n", hermon, ibdev->port, strerror ( rc ) );
		goto err_add_steer;
	}

	/* Fill receive rings */
	ib_refill_recv ( ibdev, port->eth_qp );

	/* Set port general parameters */
	memset ( &set_port, 0, sizeof ( set_port ) );
	MLX_FILL_3 ( &set_port.general, 0,
		     v_mtu, 1,
		     v_pprx, 1,
		     v_pptx, 1 );
	MLX_FILL_1 ( &set_port.general, 1,
		     mtu, ( ETH_FRAME_LEN + 40 /* Used by card */ ) );
	MLX_FILL_1 ( &set_port.general, 2,
		     pptx,  port->port_nv_conf.flow_control.pptx );
	MLX_FILL_1 ( &set_port.general, 3,
		     pprx, port->port_nv_conf.flow_control.pprx );
	if ( ( rc = hermon_cmd_set_port ( hermon, 1,
					  ( HERMON_SET_PORT_GENERAL_PARAM |
					    ibdev->port ),
					  &set_port ) ) != 0 ) {
		ERROR ( "ConnectX3 %p port %d could not set port general "
		       "parameters: %s\n",
		       hermon, ibdev->port, strerror ( rc ) );
		goto err_set_port_general_params;
	}
	TAG();

	/* Set port mac table */
	memset ( &set_port, 0, sizeof ( set_port ) );
	MLX_FILL_3 ( set_port.mac_table, 0,
		     mac_vep, ibdev->vep_number,
		     v, 1,
		     mac_h, ibdev->eth_mac_h );
	MLX_FILL_1 ( set_port.mac_table, 1,
		     mac_l, ibdev->eth_mac_l );
	if ( ( rc = hermon_cmd_set_port ( hermon, 1,
					  ( HERMON_SET_PORT_MAC_TABLE |
					    ibdev->port ),
					  &set_port ) ) != 0 ) {
		ERROR ( "ConnectX3 %p port %d could not set port mac "
		       "table: %s\n",
		       hermon, ibdev->port, strerror ( rc ) );
		goto err_set_port_mac_table;
	}
	TAG();

	/* Initialise port */
	if ( ( rc = hermon_cmd_init_port ( hermon, ibdev->port ) ) != 0 ) {
		ERROR ( "ConnectX3 %p port %d could not initialise port: "
		       "%s\n", hermon, ibdev->port, strerror ( rc ) );
		goto err_init_port;
	}

	if (hermon->cap.ncsi_lag_mode) {
		sleep(65);
	}

	return 0;

 err_init_port:
 err_set_port_general_params:
 err_set_port_mac_table:
 err_add_steer:
	hermon_eth_release_steer ( ibdev, port->eth_qp );
 err_modify_qp:
	ib_destroy_qp ( ibdev, port->eth_qp );
 err_create_qp:
	ib_destroy_cq ( ibdev, port->eth_cq );
 err_create_cq:
	hermon_close ( hermon );
 err_open:
	TAG("rc %d\n", rc);
	return rc;
}

/**
 * Close ConnectX3 Ethernet device
 *
 * @v netdev		Network device
 */
static void hermon_eth_close ( struct hermon_port *port ) {
	struct ib_device *ibdev = port->ibdev;
	struct hermon *hermon = ib_get_drvdata ( ibdev );
	int rc;
	
	TAG();
	/* NetLoop will call eth_halt before its been opened */
	if (!hermon->open_count) {
		return;
	}

	/* NULL pointers here can crash U-Boot */
	assert( port->eth_qp );
	assert( port->eth_cq );

	/* Close port */
	if ( ( rc = hermon_cmd_close_port ( hermon, ibdev->port ) ) != 0 ) {
		ERROR ( "ConnectX3 %p port %d could not close port: %s\n",
		       hermon, ibdev->port, strerror ( rc ) );
		/* Nothing we can do about this */
	}

	/* Release steering */
	hermon_eth_release_steer ( ibdev, port->eth_qp );

	/* Tear down the queues */
	ib_destroy_qp ( ibdev, port->eth_qp );
	ib_destroy_cq ( ibdev, port->eth_cq );

	port->eth_qp = NULL;
	port->eth_cq = NULL;

	/* Close hardware */
	hermon_close ( hermon );
}


#ifndef  CONNECTX_IB_ONLY
/**
 * Register ConnectX3 Ethernet device
 *
 * @v hermon		ConnectX3 device
 * @v port		ConnectX3 port
 * @ret rc		Return status code
 */
static int hermon_register_netdev ( struct hermon *hermon,
				    struct hermon_port *port ) {
	struct ib_device *ibdev = port->ibdev;
	struct hermonprm_query_port_cap query_port;
	int rc;

	/* Set protocol */
	ibdev->protocol = HERMON_PROT_ETH;

	/* Retrieve MAC address */
	if ( ( rc = hermon_cmd_query_port ( hermon, ibdev->port,
					    &query_port ) ) != 0 ) {
		ERROR ( "ConnectX3 %p port %d could not query port: %s\n",
		       hermon, ibdev->port, strerror ( rc ) );
		return rc;
	}

	ibdev->eth_mac_l = MLX_GET ( &query_port, mac_31_0 );
	ibdev->eth_mac_h = MLX_GET ( &query_port, mac_47_32 );

	return 0;
}

/**
 * Handle ConnectX3 Ethernet device port state change
 *
 * @v hermon		ConnectX3 device
 * @v port		ConnectX3 port
 * @v link_up		Link is up
 */
static void hermon_state_change_netdev ( struct hermon *hermon __unused,
					 struct hermon_port *port,
					 int link_up ) {

}

/**
 * Unregister ConnectX3 Ethernet device
 *
 * @v hermon		ConnectX3 device
 * @v port		ConnectX3 port
 */
static void hermon_unregister_netdev ( struct hermon *hermon __unused,
				       struct hermon_port *port ) {
}

/** ConnectX3 Ethernet port type */
static struct hermon_port_type hermon_port_type_eth = {
	.register_dev = hermon_register_netdev,
	.state_change = hermon_state_change_netdev,
	.unregister_dev = hermon_unregister_netdev,
};
#endif
/***************************************************************************
 *
 * Port type detection
 *
 ***************************************************************************
 */

/**
 * Name port type
 *
 * @v port_type		Port type
 * @v port_type_name	Port type name
 */
static inline const char * hermon_name_port_type ( unsigned int port_type ) {
	switch ( port_type ) {
	case HERMON_PORT_TYPE_UNKNOWN:	return "unknown";
	case HERMON_PORT_TYPE_IB:	return "Infiniband";
	case HERMON_PORT_TYPE_ETH:	return "Ethernet";
	default:			return "INVALID";
	}
}

/**
 * Set port type
 *
 * @v hermon		ConnectX3 device
 * @v port		ConnectX3 port
 * @ret rc		Return status code
 */
static int hermon_set_port_type ( struct hermon *hermon __unused,
				  struct hermon_port *port )
{
		port->type = &hermon_port_type_eth;
		return 0;
}


/**
 * Get Virtual Ethernet Port number
 *
 * @v hermon		ConnectX3 device
 * @ret rc		Return status code
 */
int vep_get_function ( struct hermon *hermon, u8 vep_index,
		       int port, u8 *vep_function ) {
	struct hermonprm_mod_stat_cfg stat_cfg;
	int rc = 0;

	/* Query static configuration */
	if ( ( rc = hermon_mod_stat_cfg ( hermon, port,
				  HERMON_MOD_STAT_CFG_QUERY,
				  HERMON_MOD_STAT_CFG_OFFSET ( pf_net_boot_m ),
				  vep_index, HERMON_SETUP_MODE_VEP,
				  &stat_cfg ) ) != 0 ) {
		ERROR ( "ConnectX3 %p port %d could not query "
		       "configuration: %s\n", hermon, port, strerror ( rc ) );
		return rc;
	}

	*vep_function = MLX_GET ( &stat_cfg, funix );

	return 0;
}

/**
 * Check CLP boot enable
 *
 * @v hermon		ConnectX3 device
 * @ret rc		Return status code
 */
int hermon_check_clp_boot_enable ( struct hermon *hermon, u8 vep_index,
				   int port, u8 *boot_enable ) {
	u8 vep_function;
	struct hermonprm_mod_stat_cfg stat_cfg;
	int rc = 0;

	*boot_enable = 0;

	if ( ( rc = vep_get_function
	                  ( hermon, vep_index, port, &vep_function ) ) != 0 ) {
		ERROR ( "ConnectX3 %p could not get vep function %s\n",
		       hermon, strerror ( rc ) );
		return rc;
	}

	if ( vep_function != hermon->physical_function )
		return 0;

	/* Query static configuration */
	if ( ( rc = hermon_mod_stat_cfg ( hermon, port,
				   HERMON_MOD_STAT_CFG_QUERY,
				   HERMON_MOD_STAT_CFG_OFFSET ( pf_net_boot_m ),
				   vep_index, HERMON_SETUP_MODE_VEP,
				   &stat_cfg ) ) != 0 ) {
		 ERROR ( "ConnectX3 %p port %d could not query "
			"configuration: %s\n", hermon, port, strerror ( rc ) );
		 return rc;
	}

	if ( MLX_GET ( &stat_cfg, pf_net_boot ) == 0 ) {
		DBGC ( hermon, "ConnectX3 %p port:%d disabled"
		       " booting by CLP\n",hermon, port );
	} else {
		DBGC ( hermon, "ConnectX3 %p port:%d enabled"
		       " booting by CLP\n",hermon, port );
		*boot_enable = 1;
	}

	return 0;
}


/**
 * Get number of supported physical functions
 *
 * @v hermon		ConnectX3 device
 * @ret rc		Return status code
 */
int hermon_get_num_supported_veps ( struct hermon *hermon,
				    u8 supported_veps[] ) {
	unsigned int port;
	struct hermonprm_mod_stat_cfg stat_cfg;
	int rc = 0;

	for ( port = 1 ; port <= hermon->num_ports ; port++ ) {
		/* Query static configuration */
		if ( ( rc = hermon_mod_stat_cfg ( hermon, port,
				  HERMON_MOD_STAT_CFG_QUERY,
				  HERMON_MOD_STAT_CFG_OFFSET ( num_veps ),
				  0, HERMON_SETUP_MODE_PORT_SETUP,
				  &stat_cfg ) ) != 0 ) {
			ERROR ( "ConnectX3 %p port %d could not query "
			       "configuration: %s\n", hermon, port, strerror ( rc ) );
			return rc;
		}


		supported_veps[port - 1] = MLX_GET ( &stat_cfg, num_veps );
		DBGC ( hermon, "ConnectX3 %p port %d number supported VEPs %d\n",
		       hermon, port, hermon->num_veps[port - 1] );
	}

	return 0;
}


/**
 * Get supported number of ports
 *
 * @v hermon		ConnectX3 device
 * @ret rc		Return status code
 */
int hermon_get_num_ports ( struct hermon *hermon ) {
	struct hermonprm_mod_stat_cfg stat_cfg;
	int rc = 0;

	/* Query static configuration */
	if ( ( rc = hermon_mod_stat_cfg ( hermon, 0,
					  HERMON_MOD_STAT_CFG_QUERY,
				HERMON_MOD_STAT_CFG_OFFSET ( num_port ),
					  hermon->physical_function,
					  HERMON_SETUP_MODE_LANE_SETUP,
				  &stat_cfg ) ) != 0 ) {
		ERROR ( "ConnectX3 %p could not query "
		       "configuration: %s\n", hermon, strerror ( rc ) );
		return rc;
	}

	hermon->num_ports = MLX_GET ( &stat_cfg, num_port );

	/* Sanity check */
	if ( hermon->num_ports > HERMON_MAX_PORTS ) {
		DBGC ( hermon, "ConnectX3 %p has %d ports (only %d supported)\n",
		       hermon, hermon->num_ports, HERMON_MAX_PORTS );
		hermon->num_ports = HERMON_MAX_PORTS;
	}

	DBGC ( hermon, "ConnectX3 %p supported number of ports %d\n",
	       hermon, hermon->num_ports );

	return 0;
}


/**
 * Set port masking
 *
 * @v hermon		ConnectX3 device
 * @ret rc		Return status code
 */
int set_port_masking ( struct hermon *hermon ) {
	int rc = 0;
	u8 vep = 0;
	unsigned int i;
	u8 boot_enable = 0;
	u8 supported_veps[HERMON_MAX_PORTS];

	/* Get number of supported ports */
	if ( ( rc = hermon_get_num_ports ( hermon ) ) != 0 )
		return rc;

	/* Get number of physical functions */
	if ( ( rc = hermon_get_num_supported_veps
				( hermon, supported_veps ) ) != 0 )
		return rc;

	/* Check CLP configuration */
	hermon->port_mask = 0;
	for ( i = 0; i < hermon->num_ports ; i++ ) {
		hermon->num_veps[i] = 0;
		for ( vep = 0; vep < supported_veps[i]; vep ++ )
		{
			if ( ( rc = hermon_check_clp_boot_enable
				  ( hermon, vep, i + 1, &boot_enable ) ) != 0 )
				return rc;
			if ( boot_enable ) {
			       hermon->port_mask |= (i + 1);
			       hermon->vep_table[i][hermon->num_veps[i]] = vep;
			       hermon->num_veps[i] ++;
			}
		}
	}

	if ( ! hermon->port_mask ) {
		/* No port was enabled */
		DBGC ( hermon, "ConnectX3 %p No port was enabled for "
		       "booting\n", hermon );
		return -ENETUNREACH;
	}

	return 0;
}


/***************************************************************************
 *
 * PCI interface
 *
 ***************************************************************************
 */

/**
 * Allocate ConnectX3 device
 *
 * @v pci		PCI device
 * @v id		PCI ID
 * @ret rc		Return status code
 */
static struct hermon * hermon_alloc ( void ) {
	struct hermon *hermon;

	/* Allocate ConnectX3 device */
	hermon = zalloc ( sizeof ( *hermon ) );
	if ( ! hermon )
		goto err_hermon;

	/* Allocate space for mailboxes */
	hermon->mailbox_in = malloc_dma ( HERMON_MBOX_SIZE,
					  HERMON_MBOX_ALIGN );
	if ( ! hermon->mailbox_in )
		goto err_mailbox_in;
	hermon->mailbox_out = malloc_dma ( HERMON_MBOX_SIZE,
					   HERMON_MBOX_ALIGN );
	if ( ! hermon->mailbox_out )
		goto err_mailbox_out;

	return hermon;

	free_dma ( hermon->mailbox_out, HERMON_MBOX_SIZE );
 err_mailbox_out:
	free_dma ( hermon->mailbox_in, HERMON_MBOX_SIZE );
 err_mailbox_in:
	free ( hermon );
 err_hermon:
	return NULL;
}

/**
 * Free ConnectX3 device
 *
 * @v hermon		ConnectX3 device
 */
void hermon_free ( void *hermon ) {
	if (!hermon)
	  return;

  ufree ( ((struct hermon *)hermon)->icm );
	ufree ( ((struct hermon *)hermon)->firmware_area );
	free_dma (((struct hermon *) hermon)->mailbox_out, HERMON_MBOX_SIZE );
	free_dma ( ((struct hermon *)hermon)->mailbox_in, HERMON_MBOX_SIZE );
	free ( hermon );
}

/**
 * Initialise ConnectX3 PCI parameters
 *
 * @v hermon		ConnectX3 device
 */
static void hermon_pci_init ( struct hermon *hermon ) {
  EFI_PCI_IO_PROTOCOL *pci = hermon->pci;
  EFI_ACPI_ADDRESS_SPACE_DESCRIPTOR *MmioDesc;
  EFI_STATUS Status;

	/* Get PCI BARs */
  Status = pci->GetBarAttributes (
                          pci,
                          HERMON_PCI_CONFIG_BAR,
                          NULL,
                          (VOID**) &MmioDesc
                          );
  if (EFI_ERROR (Status) ||
      MmioDesc->ResType != ACPI_ADDRESS_SPACE_TYPE_MEM) {
      ERROR("Mellanox: No mmio bar\n");
      assert(0);
  }
	hermon->config	= (void *)MmioDesc->AddrRangeMin;
	DBGC2 ( hermon, "BAR0 = %p\n",hermon->config);
	Status = pci->GetBarAttributes (
                          pci,
                          HERMON_PCI_UAR_BAR,
                          NULL,
                          (VOID**) &MmioDesc
                          );
  if (EFI_ERROR (Status) ||
      MmioDesc->ResType != ACPI_ADDRESS_SPACE_TYPE_MEM) {
      ERROR("Mellanox: No mmio bar\n");
      assert(0);
  }
  hermon->uar = (void *)MmioDesc->AddrRangeMin;
  DBGC2 ( hermon, "BAR1 = %p\n",hermon->uar);

	hermon->physical_function = 0;
}

/**
 * Probe PCI device
 *
 * @v pci		PCI device
 * @v id		PCI ID
 * @ret Return hermon pointer. Null if error
 */
void *hermon_probe (EFI_PCI_IO_PROTOCOL *pci, UINT32 *dev_cnt)
{
	struct hermon *hermon;
	struct ib_device *ibdev;
	struct hermon_port *port;
	//struct hermon_tlv_header tlv;
	unsigned int vep;
	unsigned int i;
	int rc;

	*dev_cnt = 0;
	/* Allocate ConnectX3 device */
	hermon = hermon_alloc();
	if ( ! hermon )
		goto err_alloc;

	hermon->pci = pci;

	/* Initialise PCI parameters */
	hermon_pci_init ( hermon );

	/* Reset device */
	hermon_reset ( hermon, HERMON_RESET_START );

	TAG();
	/* Set port mask */
	if ( ( rc = set_port_masking ( hermon ) ) != 0 ) {
		goto err_alloc;
	}

	TAG();
	/* Allocate Infiniband devices */
	for ( i = 0 ; i < hermon->num_ports ; i++ ) {
		for ( vep = 0; vep < hermon->num_veps[i]; vep++ ) {
			if ( ! ( hermon->port_mask &
						   ( i + HERMON_PORT_BASE ) ) )
				continue;
			ibdev = alloc_ibdev ( 0 );
			if ( ! ibdev )
				goto err_alloc_ibdev;
			hermon->port[i].ibdev = ibdev;
			ibdev->op = &hermon_ib_operations;
			ibdev->port = ( HERMON_PORT_BASE + i );
			ib_set_drvdata ( ibdev, hermon );
			ibdev->vep_number = hermon->vep_table[i][vep];
		}
	}

	TAG();

	/* Start firmware */
	if ( ( rc = hermon_start_firmware ( hermon ) ) != 0 )
		goto err_start_firmware;

	TAG();
	/* Get device limits */
	if ( ( rc = hermon_get_cap ( hermon ) ) != 0 )
		goto err_get_cap;

	TAG();
	/* Start device */
	if ( ( rc = hermon_start ( hermon, 1 ) ) != 0 )
		goto err_start;

	TAG();
	/* Determine port types */
	for ( i = 0 ; i < hermon->num_ports ; i++ ) {
		if ( ! ( hermon->port_mask & ( i + HERMON_PORT_BASE ) ) )
			continue;
		port = &hermon->port[i];
		if ( ( rc = hermon_set_port_type ( hermon, port ) ) != 0 )
			goto err_set_port_type;
	}

	TAG();
	/* Register devices */
	for ( i = 0 ; i < hermon->num_ports ; i++ ) {
		if ( ! ( hermon->port_mask & ( i + HERMON_PORT_BASE ) ) )
			continue;
		port = &hermon->port[i];
		if ( ( rc = port->type->register_dev ( hermon, port ) ) != 0 )
			goto err_register;
		*dev_cnt = *dev_cnt + 1;
	}

	/* Leave device quiescent until opened */
	if ( hermon->open_count == 0 )
		hermon_stop ( hermon );

	TAG();
	return hermon;

 err_register:
  i = hermon->num_ports;
	for ( i-- ; ( signed int ) i >= 0 ; i-- ) {
		if ( ! ( hermon->port_mask & ( i + HERMON_PORT_BASE ) ) )
			continue;
		port = &hermon->port[i];
		port->type->unregister_dev ( hermon, port );
	}
 err_set_port_type:
	hermon_stop ( hermon );
 err_start:
	i = hermon->num_ports;
 err_alloc_ibdev:
 i = hermon->num_ports;
	for ( i-- ; ( signed int ) i >= 0 ; i-- ) {
		if ( ! ( hermon->port_mask & ( i + HERMON_PORT_BASE ) ) )
			continue;
		ibdev_put ( hermon->port[i].ibdev );
	}
 err_get_cap:
	hermon_stop_firmware ( hermon );
 err_start_firmware:
	hermon_free ( hermon );
 err_alloc:
	TAG("Error");
	return NULL;
}

int hermon_set_mac( void *hermon, unsigned int mport,
				const uint8_t *mac ) {

	struct hermonprm_mod_stat_cfg stat_cfg;
	union {
		uint8_t bytes[8];
		uint32_t dwords[2];
	} buf;
	int rc = 0;

	/* Prepare MAC address */
	memset ( &buf, 0, sizeof ( buf ) );
	memcpy ( &buf.bytes[ sizeof ( buf.bytes ) - ETH_ALEN ], mac,
		ETH_ALEN );

	/* Modify static configuration */
	memset ( &stat_cfg, 0, sizeof ( stat_cfg ) );
	MLX_FILL_2 ( &stat_cfg, 36,
			mac_m, 1,
			mac_high, ntohl ( buf.dwords[0] ) );
	MLX_FILL_1 ( &stat_cfg, 37, mac_low, ntohl ( buf.dwords[1] ) );

	if ( ( rc = hermon_mod_stat_cfg ( (struct hermon *)hermon, mport,
						HERMON_MOD_STAT_CFG_SET,
						HERMON_MOD_STAT_CFG_OFFSET ( mac_m ),
						0, HERMON_SETUP_MODE_LANE_SETUP,
						&stat_cfg ) ) != 0 ) {
	ERROR ( "ConnectX3 %p port %d could not modify "
		"configuration: %s\n", hermon, mport, strerror ( rc ) );
	} else {
		DBGC ( hermon, "ConnectX3 %p port %d updated MAC address to %pM\n",
			hermon, mport, mac );
		/* modify our copy of mac address */
		((struct hermon *)hermon)->port[mport-1].ibdev->eth_mac_l = ntohl(buf.dwords[1]);
		((struct hermon *)hermon)->port[mport-1].ibdev->eth_mac_h = ntohl(buf.dwords[0]);
	}
	TAG();
	return rc;
}

int hermon_get_mac_info(void *hermon, unsigned int mport, uint8_t *mac)
{
  struct hermon_port *port = &(((struct hermon *)hermon)->port[mport]);
  union {
    uint8_t bytes[8];
    uint32_t dwords[2];
  } buf;
  uint32_t tmp;
  tmp = htonl(port->ibdev->eth_mac_l);
  memcpy ( &buf.dwords[1], &tmp,
      sizeof(buf.dwords[1]) );
  tmp = htonl(port->ibdev->eth_mac_h);
  memcpy ( &buf.dwords[0], &tmp,
          sizeof(buf.dwords[0]) );
  memcpy((void *)mac, &buf.bytes[ sizeof ( buf.bytes ) - ETH_ALEN ], ETH_ALEN);

  return 0;
}

int hermon_transmit(void *hermon, unsigned int mport,
				void *packet, unsigned int length )
{
  struct hermon_port *port = &(((struct hermon *)hermon)->port[mport]);
  struct io_buffer *iobuf = alloc_iob(packet, length);
  iob_put ( iobuf, length );
	return	hermon_eth_transmit(port, iobuf);
}

int hermon_poll(void *hermon, unsigned int mport)
{
  return hermon_eth_poll(&(((struct hermon *)hermon)->port[mport]));
}

int hermon_close_port(void *hermon, unsigned int mport)
{
  struct hermon_port *port = &(((struct hermon *)hermon)->port[mport]);
  hermon_eth_close(port);
  return 0;
}

int hermon_open_port(void *hermon, unsigned int mport, void *priv_data)
{
  struct hermon_port *port = &(((struct hermon *)hermon)->port[mport]);
  hermon_eth_open(port, priv_data);
  return 0;
}

