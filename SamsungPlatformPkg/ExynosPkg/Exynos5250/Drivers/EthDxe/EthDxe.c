/** @file
  Template for Timer Architecture Protocol driver of the ARM flavor

  Copyright (c) 2012, Samsung Electronics Co. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/


#include <PiDxe.h>

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/NetLib.h>
#include <Library/TimerLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/SimpleNetwork.h>
#include <Protocol/DevicePath.h>
#include <Protocol/ExynosGpio.h>
#include <Platform/ArmPlatform.h>
#include "EthDxe.h"


ETH_DXE_PRIVATE_DATA gEthDxePrivateTemplate = {
	ETH_DXE_PRIVATE_DATA_SIGNATURE,
	{
		EFI_SIMPLE_NETWORK_PROTOCOL_REVISION,
		EthStart,
		EthStop,
		EthInitialize,
		EthReset,
		EthShutdown,
		EthReceiveFilters,
		EthStationAddress,
		EthStatistics,
		EthMCastIpToMac,
		EthNvData,
		EthGetStatus,
		EthTransmit,
		EthReceive,
		NULL,
		NULL
	},
	{
		EfiSimpleNetworkStopped,	//  State
		NET_ETHER_ADDR_LEN,		//  HwAddressSize
    		NET_ETHER_HEADER_SIZE,	//  MediaHeaderSize
    		1500,					//  MaxPacketSize
    		0,						//  NvRamSize
    		0,						//  NvRamAccessSize
    		0,						//  ReceiveFilterMask
    		0,						//  ReceiveFilterSetting
    		MAX_MCAST_FILTER_CNT,	//  MaxMCastFilterCount
    		0,						//  MCastFilterCount
    		{
    			0
		},                    			//  MCastFilter
		{
			0
		},			                    	//  CurrentAddress
		{
			0
		},						//  BroadcastAddress
		{
			0
		},						//  PermanentAddress
		NET_IFTYPE_ETHERNET,		//  IfType
		FALSE,                  			//  MacAddressChangeable
		FALSE,					//  MultipleTxSupported
		FALSE,					//  MediaPresentSupported
		TRUE                  			//  MediaPresent
	},
	{
		{
			HARDWARE_DEVICE_PATH,
			HW_VENDOR_DP,
			(UINT8)(sizeof(VENDOR_DEVICE_PATH)),
			(UINT8)((sizeof(VENDOR_DEVICE_PATH)) >> 8),
			EFI_SIMPLE_NETWORK_PROTOCOL_GUID
		},
		{
			END_DEVICE_PATH_TYPE,
			END_ENTIRE_DEVICE_PATH_SUBTYPE,
			sizeof (EFI_DEVICE_PATH_PROTOCOL),
			0
		}
	}
};


UINT32 smc911x_reg_read(UINT32 offset)
{
	UINT32 regBase = PcdGet32(PcdSMC911XBase);
	UINT32 val;

	val = (MmioRead16(regBase + offset) & 0xFFFF) | ((MmioRead16(regBase + offset + 2) & 0xFFFF) << 16);

	return val;
}

VOID smc911x_reg_write(UINT32 offset, UINT32 val)
{
	UINT32 regBase = PcdGet32(PcdSMC911XBase);

	MmioWrite16(regBase + offset, ((UINT16)(val & 0xFFFF)));
	MmioWrite16(regBase + offset + 2, ((UINT16)((val & 0xFFFF0000)>>16)));
}

UINT32 smc911x_get_mac_csr(UINT8 reg)
{
	while (smc911x_reg_read(MAC_CSR_CMD) & MAC_CSR_CMD_CSR_BUSY)
		;	
	smc911x_reg_write(MAC_CSR_CMD, (MAC_CSR_CMD_CSR_BUSY | MAC_CSR_CMD_R_NOT_W | reg));
	while (smc911x_reg_read(MAC_CSR_CMD) & MAC_CSR_CMD_CSR_BUSY)
		;
	return smc911x_reg_read(MAC_CSR_DATA);
}

VOID smc911x_set_mac_csr(UINT8 reg, UINT32 data)
{
	while (smc911x_reg_read(MAC_CSR_CMD) & MAC_CSR_CMD_CSR_BUSY)
		;
	smc911x_reg_write(MAC_CSR_DATA, data);
	smc911x_reg_write(MAC_CSR_CMD, (MAC_CSR_CMD_CSR_BUSY | reg));
	while (smc911x_reg_read(MAC_CSR_CMD) & MAC_CSR_CMD_CSR_BUSY)
		;
}

VOID smc911x_reset(VOID)
{
	INT32 timeout;

	/* Take out of PM setting first */
	if (smc911x_reg_read(PMT_CTRL) & PMT_CTRL_READY) {
		/* Write to the bytetest will take out of powerdown */
		smc911x_reg_write(BYTE_TEST, 0x0);

		timeout = 10;

		while (timeout-- && !(smc911x_reg_read(PMT_CTRL) & PMT_CTRL_READY))
			MicroSecondDelay(10);
		if (!timeout) {
			DEBUG((EFI_D_ERROR, "smc911x_reset: timeout waiting for PM restore\n"));
			return;
		}
	}

	/* Disable interrupts */
	smc911x_reg_write(INT_EN, 0);

	smc911x_reg_write(HW_CFG, HW_CFG_SRST);

	timeout = 1000;
	while (timeout-- && (smc911x_reg_read(E2P_CMD) & E2P_CMD_EPC_BUSY))
		MicroSecondDelay(10);

	if (!timeout) {
		DEBUG((EFI_D_ERROR, "smc911x_reset: reset timeout\n"));
		return;
	}

	/* Reset the FIFO level and flow control settings */
	smc911x_set_mac_csr(FLOW, FLOW_FCPT | FLOW_FCEN);
	smc911x_reg_write(AFC_CFG, 0x0050287F);

	/* Set to LED outputs */
	smc911x_reg_write(GPIO_CFG, 0x70070000);
}

VOID smc911x_phy_reset(VOID)
{
	UINT32 reg;

	reg = smc911x_reg_read(PMT_CTRL);
	reg &= ~0xfffff030;
	reg |= PMT_CTRL_PHY_RST;
	smc911x_reg_write(PMT_CTRL, reg);

	MicroSecondDelay(100000);
}

VOID smc911x_miiphy_read(UINT8 phy, UINT8 reg, UINT16 *val)
{
	while (smc911x_get_mac_csr(MII_ACC) & MII_ACC_MII_BUSY)
		;

	smc911x_set_mac_csr(MII_ACC, (phy << 11 | reg << 6 | MII_ACC_MII_BUSY));

	while (smc911x_get_mac_csr(MII_ACC) & MII_ACC_MII_BUSY)
		;

	*val = smc911x_get_mac_csr(MII_DATA);
}

VOID smc911x_miiphy_write(UINT8 phy, UINT8 reg, UINT16 val)
{
	while (smc911x_get_mac_csr(MII_ACC) & MII_ACC_MII_BUSY)
		;

	smc911x_set_mac_csr(MII_DATA, val);
	smc911x_set_mac_csr(MII_ACC, (phy << 11 | reg << 6 | MII_ACC_MII_BUSY | MII_ACC_MII_WRITE));

	while (smc911x_get_mac_csr(MII_ACC) & MII_ACC_MII_BUSY)
		;
}

VOID smc911x_phy_configure(VOID)
{
	INT32 timeout;
	UINT16 status;

	smc911x_phy_reset();

	smc911x_miiphy_write(1, PHY_BMCR, PHY_BMCR_RESET);
	MicroSecondDelay(1000);
	smc911x_miiphy_write(1, PHY_ANAR, 0x01e1);
	smc911x_miiphy_write(1, PHY_BMCR, (PHY_BMCR_AUTON | PHY_BMCR_RST_NEG));

	timeout = 5000;
	do {
		MicroSecondDelay(1000);
		if ((timeout--) == 0)
			goto err_out;

		smc911x_miiphy_read(1, PHY_BMSR, &status);
	} while (!(status & PHY_BMSR_LS));

	DEBUG((EFI_D_ERROR, "smc911x_phy_configure: PHY initialized\n"));

	return;

err_out:
	DEBUG((EFI_D_ERROR, "smc911x_phy_configure: autonegotiation timed out\n"));
}

VOID smc911x_handle_mac_address(ETH_DXE_PRIVATE_DATA	*Private)
{
	UINT32 addrh, addrl;

	addrl = Private->Mode.CurrentAddress.Addr[0] | \
			(Private->Mode.CurrentAddress.Addr[1] << 8) | \
			(Private->Mode.CurrentAddress.Addr[2] << 16) | \
			(Private->Mode.CurrentAddress.Addr[3] << 24);
	addrh = Private->Mode.CurrentAddress.Addr[4] | \
			(Private->Mode.CurrentAddress.Addr[5] << 8);
	
	smc911x_set_mac_csr(ADDRL, addrl);
	smc911x_set_mac_csr(ADDRH, addrh);
}

VOID smc911x_enable(VOID)
{
	/* Enable TX */
	smc911x_reg_write(HW_CFG, (8 << 16 | HW_CFG_SF));

	smc911x_reg_write(GPT_CFG, (GPT_CFG_TIMER_EN | 10000));

	smc911x_reg_write(TX_CFG, TX_CFG_TX_ON);

	/* no padding to start of packets */
	smc911x_reg_write(RX_CFG, 0);

	smc911x_set_mac_csr(MAC_CR, (MAC_CR_TXEN | MAC_CR_RXEN | MAC_CR_HBDIS /*| MAC_CR_PADSTR*/));
}

EFI_STATUS
EFIAPI
EthStart(
	EFI_SIMPLE_NETWORK_PROTOCOL	*This
)
{
	ETH_DXE_PRIVATE_DATA	*Private;

	Private = ETH_DXE_PRIVATE_DATA_FROM_SNP_THIS(This);

	switch ( Private->Snp.Mode->State )
	{
		case EfiSimpleNetworkStopped:
			break;

		case EfiSimpleNetworkStarted:
		case EfiSimpleNetworkInitialized:
			return( EFI_ALREADY_STARTED );
      			break;

    		default:
      			return( EFI_DEVICE_ERROR );
      			break;
	}
	
	/* gpio configuration */
	MmioAndThenOr32(0x11000000 + 0x120, ~((0xFF<<16)|(0xFF<<4)), ((0x22<<16)|(0x52<<4)));

	/* 16 Bit bus width */
	MmioWrite32(0x11000000 + 0x1C0, 0x22222222);
	MmioWrite32(0x11000000 + 0x1E0, 0x22222222);
	
	/* SROM BANK1 */
	MmioAndThenOr32(0x12570000, ~(0xF<<4), (((1<<0)|(0<<2)|(1<<3))<<4));

	/* set timing for nCS1 suitable for ethernet chip */
	MmioWrite32(0x12570008, ((0x1 << 0) | (0x9 << 4) | (0xC << 8) | (0x1 << 12) | \
								(0x6 << 16) | (0x1 << 24) | (0x1 << 28)));

	Private->Snp.Mode->State = EfiSimpleNetworkStarted;

	return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EthStop(
	EFI_SIMPLE_NETWORK_PROTOCOL	*This
)
{
	ETH_DXE_PRIVATE_DATA	*Private;

	Private = ETH_DXE_PRIVATE_DATA_FROM_SNP_THIS(This);

	switch ( Private->Snp.Mode->State )
	{
		case EfiSimpleNetworkStarted:
			break;

		case EfiSimpleNetworkStopped:
			return( EFI_NOT_STARTED );
			break;

		default:
			return( EFI_DEVICE_ERROR );
			break;
	}

	Private->Snp.Mode->State = EfiSimpleNetworkStopped;

	return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EthInitialize(
	EFI_SIMPLE_NETWORK_PROTOCOL	*This,
	UINTN							ExtraRxBufferSize,
	UINTN							ExtraTxBufferSize
)
{
	UINT32 val, i, addrh, addrl;
	ETH_DXE_PRIVATE_DATA *Private;

	Private = ETH_DXE_PRIVATE_DATA_FROM_SNP_THIS(This);

	switch ( Private->Snp.Mode->State )
	{
		case EfiSimpleNetworkStarted:
			break;

		case EfiSimpleNetworkStopped:
			return( EFI_NOT_STARTED );
			break;

		default:
			return( EFI_DEVICE_ERROR );
			break;
	}

	val = smc911x_reg_read(BYTE_TEST);

	if(val == 0xFFFFFFFF) {
		return EFI_NO_MEDIA;
	}
	else if(val != 0x87654321) {
		DEBUG((EFI_D_ERROR,"EthInitialize: Invalid chip endian 0x%x\n", val));
		return EFI_NO_MEDIA;
	}

	val = smc911x_reg_read(ID_REV) >> 16;
	for(i=0;chip_ids[i].id != 0;i++) {
		if(chip_ids[i].id == val)
			break;
	}

	if(!chip_ids[i].id) {
		DEBUG((EFI_D_ERROR,"EthInitialize: Unknown chip id 0x%x\n", val));
		return EFI_NO_MEDIA;
	}
	else {
		DEBUG((EFI_D_ERROR,"EthInitialize: Chip id 0x%x\n", val));
	}

	addrh = smc911x_get_mac_csr(ADDRH);
	addrl = smc911x_get_mac_csr(ADDRL);

	if (addrl == 0xffffffff && addrh == 0x0000ffff) {
		addrh = 0x00000040;
		addrl = 0x5c260a5b;
	}
	
	Private->Mode.CurrentAddress.Addr[0] = (addrl & 0xFF);
	Private->Mode.CurrentAddress.Addr[1] = (addrl & 0xFF00)>>8;
	Private->Mode.CurrentAddress.Addr[2] = (addrl & 0xFF0000)>>16;
	Private->Mode.CurrentAddress.Addr[3] = (addrl & 0xFF000000)>>24;
	Private->Mode.CurrentAddress.Addr[4] = (addrh & 0xFF);
	Private->Mode.CurrentAddress.Addr[5] = (addrh & 0xFF00)>>8;
	gBS->CopyMem((VOID *)&Private->Mode.PermanentAddress, \
					(VOID *)&Private->Mode.CurrentAddress, \
					sizeof(EFI_MAC_ADDRESS));

	DEBUG((EFI_D_ERROR,"EthInitialize: MAC address is "));

	for(i=6;i>0;i--) {
		DEBUG((EFI_D_ERROR,"%02x", Private->Mode.CurrentAddress.Addr[i - 1]));
		if(i > 1)
			DEBUG((EFI_D_ERROR,":"));
		else
			DEBUG((EFI_D_ERROR,"\n"));
	}

	smc911x_reset();

	/* Configure the PHY, initialize the link state */
	smc911x_phy_configure();

	smc911x_handle_mac_address(Private);

	/* Turn on Tx + Rx */
	smc911x_enable();

	Private->Snp.Mode->State = EfiSimpleNetworkInitialized;

	return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EthReset(
	EFI_SIMPLE_NETWORK_PROTOCOL	*This,
	BOOLEAN							ExtendedVerification
)
{
	ETH_DXE_PRIVATE_DATA	*Private;

	Private = ETH_DXE_PRIVATE_DATA_FROM_SNP_THIS(This);

	switch ( Private->Snp.Mode->State )
	{
		case EfiSimpleNetworkInitialized:
			break;

		case EfiSimpleNetworkStopped:
			return( EFI_NOT_STARTED );
			break;

		default:
			return( EFI_DEVICE_ERROR );
			break;
	}

	return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EthShutdown(
	EFI_SIMPLE_NETWORK_PROTOCOL	*This
)
{
	ETH_DXE_PRIVATE_DATA	*Private;

	Private = ETH_DXE_PRIVATE_DATA_FROM_SNP_THIS(This);

	switch ( Private->Snp.Mode->State )
	{
		case EfiSimpleNetworkInitialized:
			break;

		case EfiSimpleNetworkStopped:
			return( EFI_NOT_STARTED );
			break;

		default:
			return( EFI_DEVICE_ERROR );
			break;
	}

	Private->Snp.Mode->State = EfiSimpleNetworkStarted;

	return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EthReceiveFilters(
	EFI_SIMPLE_NETWORK_PROTOCOL	*This,
	UINT32							Enable,
	UINT32							Disable,
	BOOLEAN							ResetMCastFilter,
	UINTN							MCastFilterCnt,
	EFI_MAC_ADDRESS				*MCastFilter
)
{
	return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EthStationAddress(
	EFI_SIMPLE_NETWORK_PROTOCOL	*This,
	BOOLEAN							Reset,
	EFI_MAC_ADDRESS				*New
)
{
	return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
EthStatistics(
	EFI_SIMPLE_NETWORK_PROTOCOL	*This,
	BOOLEAN							Reset,
	UINTN							*StatisticsSize,
	EFI_NETWORK_STATISTICS              *StatisticsTable
)
{
	return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
EthMCastIpToMac(
	EFI_SIMPLE_NETWORK_PROTOCOL	*This,
	BOOLEAN							IPv6,
	EFI_IP_ADDRESS					*IP,
	EFI_MAC_ADDRESS				*MAC
)
{
	return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
EthNvData(
	EFI_SIMPLE_NETWORK_PROTOCOL	*This,
	BOOLEAN							ReadWrite,
	UINTN							Offset,
	UINTN							BufferSize,
	VOID							*Buffer
)
{
	return EFI_UNSUPPORTED;
}

EFI_STATUS
EFIAPI
EthGetStatus(
	EFI_SIMPLE_NETWORK_PROTOCOL	*This,
	UINT32							*InterruptStatus,
	VOID							**TxBuf
)
{
	if ( TxBuf != NULL ) {
		*( ( UINT8 ** ) TxBuf ) = ( UINT8 * ) 1;
	}

	if ( InterruptStatus != NULL ) {
		*InterruptStatus = EFI_SIMPLE_NETWORK_TRANSMIT_INTERRUPT;
	}

	return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EthTransmit(
	EFI_SIMPLE_NETWORK_PROTOCOL	*This,
	UINTN							HeaderSize,
	UINTN							BufferSize,
	VOID							*Buffer,
	EFI_MAC_ADDRESS				*SrcAddr,
	EFI_MAC_ADDRESS				*DestAddr,
	UINT16							*Protocol
)
{
	UINT32 *data = (UINT32 *)Buffer;
	UINT32 tmpSize;
	UINT32 status;
	EthernetHeader *EnetHeader;

	if ( This->Mode->State < EfiSimpleNetworkStarted ) {
		return( EFI_NOT_STARTED );
	}

	if ( HeaderSize != 0 ) {
		if ( ( DestAddr == NULL ) || ( Protocol == NULL ) || \
			( HeaderSize != This->Mode->MediaHeaderSize ) ) {
				return( EFI_INVALID_PARAMETER );
		}

		if ( SrcAddr == NULL ) {
			SrcAddr = &This->Mode->CurrentAddress;
		}

		EnetHeader = (EthernetHeader *)Buffer;

		CopyMem( EnetHeader->DstAddr, DestAddr, NET_ETHER_ADDR_LEN );
		CopyMem( EnetHeader->SrcAddr, SrcAddr, NET_ETHER_ADDR_LEN );

		EnetHeader->Type = HTONS( *Protocol );
	}

	smc911x_reg_write(TX_DATA_FIFO, TX_CMD_A_INT_FIRST_SEG | TX_CMD_A_INT_LAST_SEG | BufferSize);
	smc911x_reg_write(TX_DATA_FIFO, BufferSize);

	tmpSize = (BufferSize + 3) / 4;

	while (tmpSize--)
		smc911x_reg_write(TX_DATA_FIFO, *data++);

	/* wait for transmission */
	while (!((smc911x_reg_read(TX_FIFO_INF) & TX_FIFO_INF_TSUSED) >> 16))
		;

	/* get status. Ignore 'no carrier' error, it has no meaning for
	 * full duplex operation
	 */
	status = smc911x_reg_read(TX_STATUS_FIFO) & \
								(TX_STS_LOC | TX_STS_LATE_COLL | \
								TX_STS_MANY_COLL | TX_STS_MANY_DEFER | \
								TX_STS_UNDERRUN);

	if (!status)
		return EFI_SUCCESS;

	DEBUG((EFI_D_ERROR, "EthTransmit: Failed to send packet: %s%s%s%s%s\n",
			status & TX_STS_LOC ? "TX_STS_LOC " : "",
			status & TX_STS_LATE_COLL ? "TX_STS_LATE_COLL " : "",
			status & TX_STS_MANY_COLL ? "TX_STS_MANY_COLL " : "",
			status & TX_STS_MANY_DEFER ? "TX_STS_MANY_DEFER " : "",
			status & TX_STS_UNDERRUN ? "TX_STS_UNDERRUN" : ""));

	return EFI_DEVICE_ERROR;
}

EFI_STATUS
EFIAPI
EthReceive(
	EFI_SIMPLE_NETWORK_PROTOCOL	*This,
	UINTN							*HeaderSize,
	UINTN							*BufferSize,
	VOID							*Buffer,
	EFI_MAC_ADDRESS				*SrcAddr,
	EFI_MAC_ADDRESS				*DestAddr,
	UINT16							*Protocol  
)
{
	UINT32 *data = (UINT32 *)Buffer;
	UINT32 pktSize, tmpSize;
	UINT32 status, i;
	EthernetHeader *EnetHeader;
	
	/* workaround: delay for rx packet should be added here.
	 * because NetLoop does not guarantee the RX packet delay.
	 */
	for (i=0; i<0x100000; i++) {
		if ((smc911x_reg_read(RX_FIFO_INF) & RX_FIFO_INF_RXSUSED) >> 16)
			break;
	}
	
	if (i == 0x100000) {
		DEBUG((EFI_D_ERROR, "EthReceive: timeout in RX\n"));
		return EFI_TIMEOUT;
	}

	if ((smc911x_reg_read(RX_FIFO_INF) & RX_FIFO_INF_RXSUSED) >> 16) {
		status = smc911x_reg_read(RX_STATUS_FIFO);
		pktSize = (status & RX_STS_PKT_LEN) >> 16;

		smc911x_reg_write(RX_CFG, 0);

		tmpSize = (pktSize + 3) / 4;
		i = 0;
		while (tmpSize--)
			*data++ = smc911x_reg_read(RX_DATA_FIFO);
		
		if (status & RX_STS_ES) {
			DEBUG((EFI_D_ERROR, "EthReceive: dropped bad packet. Status: 0x%x\n", status));
		}

		*BufferSize = pktSize -4; //discard 4 bytes of FCS

	}

#if 0
	{
		UINT8 *tmpBuffer = (UINT8 *)Buffer;

		for(i=0;i<*BufferSize;i++) {
			DEBUG((EFI_D_ERROR, "%02x", *tmpBuffer++));
			if((i%16) < 15)
				DEBUG((EFI_D_ERROR, " "));
			else 
				DEBUG((EFI_D_ERROR, "\n"));
		}

		DEBUG((EFI_D_ERROR, "\n"));
	}
#endif

	if(HeaderSize != NULL) {
		*HeaderSize = sizeof(EthernetHeader);
	}

	EnetHeader = (EthernetHeader *)Buffer;

	if(SrcAddr != NULL) {
		ZeroMem(SrcAddr, sizeof(EFI_MAC_ADDRESS));
		CopyMem(SrcAddr, EnetHeader->SrcAddr, NET_ETHER_ADDR_LEN);
	}

	if(DestAddr != NULL) {
		ZeroMem(DestAddr, sizeof(EFI_MAC_ADDRESS));
		CopyMem(DestAddr, EnetHeader->DstAddr, NET_ETHER_ADDR_LEN);
	}

	if (Protocol != NULL) {
		*Protocol = NTOHS(EnetHeader->Type);
	}

	return EFI_SUCCESS;
}


/**
  Initialize the state information for the Display Dxe

  @param  ImageHandle   of the loaded driver
  @param  SystemTable   Pointer to the System Table

  @retval EFI_SUCCESS           Protocol registered
  @retval EFI_OUT_OF_RESOURCES  Cannot allocate protocol data structure
  @retval EFI_DEVICE_ERROR      Hardware problems

**/
EFI_STATUS
EFIAPI
EthDxeInitialize (
	EFI_HANDLE			ImageHandle,
	EFI_SYSTEM_TABLE   	*SystemTable
)
{
	EFI_STATUS Status = EFI_SUCCESS;
	EFI_GUID SimpleNetworkProtocolGuid = EFI_SIMPLE_NETWORK_PROTOCOL_GUID;
	EFI_GUID DevicePathProtocolGuid = EFI_DEVICE_PATH_PROTOCOL_GUID;
	ETH_DXE_PRIVATE_DATA *Private;

	/* Allocate the private data */
	Private = (ETH_DXE_PRIVATE_DATA *)AllocateCopyPool(sizeof(ETH_DXE_PRIVATE_DATA), &gEthDxePrivateTemplate );
	if ( Private == NULL ) {
		Status = EFI_OUT_OF_RESOURCES;
		ASSERT_EFI_ERROR(Status);
	}

	Private->Snp.Mode = &Private->Mode;

	/* Set the broadcast address */
	SetMem( &Private->Mode.BroadcastAddress, sizeof( EFI_MAC_ADDRESS ), 0xFF );

	Status = gBS->InstallMultipleProtocolInterfaces (
											&ImageHandle,
											&DevicePathProtocolGuid,
											&Private->DevicePath,
											&SimpleNetworkProtocolGuid,
											&Private->Snp,
											NULL);

	return Status;
}
