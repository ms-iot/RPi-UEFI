/**
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
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

#include "ddr_mcu.h"
#include "ddr_lib.h"
#include "kc_phy_util_reg_flds.h"

#define MIN_RDLVL_DLY	0x30
#define MAX_RDLVL_DLY	0xE0	/* 0x100: 1 clock cycle */
#define RDLVL_STEP	0x2
#define NUM_STEPS	((MAX_RDLVL_DLY - MIN_RDLVL_DLY) / RDLVL_STEP)
#define GOOD_RDLVL_WINDOW 0x30

typedef struct sw_phy_train_ctx {
	struct apm_mcu *mcu;
	unsigned int rank;
	unsigned int min_dly;
	unsigned int max_dly;
	unsigned int step;
	void *shmoo_data;
	unsigned int hw_lvl[18]; 
	unsigned int mid_lvl[18]; 
} sw_lvl_ctx_t;

typedef struct window_lvl {
	unsigned int start;
	unsigned int end;
	unsigned int width;
} window_t;

static void lfsr(unsigned long long *_lfsr_p) 
{
	/* taps: 32 31 29 1; feedback polynomial: x^32 + x^31 + x^29 + x + 1 */
	*_lfsr_p = (*_lfsr_p >> 1) ^ (-(*_lfsr_p & 1U) & 0xD0000001U);
}

static unsigned long long rand_val(unsigned long long *_lfsr_p) 
{
	unsigned long long ret = 0;

	lfsr(_lfsr_p);
	ret = *_lfsr_p;
	ret <<= 32ULL;
	lfsr(_lfsr_p);
	ret |= (unsigned long long)*_lfsr_p & 0xFFFFFFFFULL;

	return ret;
}

static void sw_rdlvl_display_result(sw_lvl_ctx_t *ctx) 
{
	struct apm_mcu *mcu = ctx->mcu;
	unsigned int i, j, y1, y2, z1, z2;
	//char *p = ctx->shmoo_data;

	debug(".: h/w lvl - *: sw mid-point lvl\n");
	for (i = 0; i < PHY_SUPPORTED_LANES - 1; i++) {
		debug("Byte[%d]   : ", i);
		y1 = (ctx->hw_lvl[i * 2] - ctx->min_dly) / ctx->step;
		z1 = (ctx->mid_lvl[i * 2] - ctx->min_dly) / ctx->step;
		for (j = 0; j < NUM_STEPS; j++){
			if ((y1 == j) && (y1 != z1))
				debug(".");
			else if (z1 == j)
				debug("*");
	//		else
	//			debug("%d", *(p + (i * 2) * NUM_STEPS + j));
		}
		debug("\n");
		if (!mcu->mcu_params.by4_mode) 
			goto skip_x4_display;
		debug("Byte[%d] x4: ", i);
		y2 = (ctx->hw_lvl[i * 2 + 1] - ctx->min_dly) / ctx->step;
		z2 = (ctx->mid_lvl[i * 2 + 1] - ctx->min_dly) / ctx->step;
		for (j = 0; j < NUM_STEPS; j++){
			if ((y2 == j) && (y2 != z2))
				debug(".");
			else if (z2 == j)
				debug("*");
	//		else
	//			debug("%d", *(p + (i * 2 + 1) * NUM_STEPS + j));
		}
		debug("\n");
skip_x4_display:
		;
	}
}

static int compare_data(unsigned long long *p1, unsigned long long *p2, 
					unsigned long long data_mask)
{
	return ((*p1 & data_mask) != (*p2 & data_mask)) ? 1 : 0;
}

static void ecc_err_ctl_enable(struct apm_mcu *p_mcu)
{
	struct apm_memc *memc = (struct apm_memc *)p_mcu->parent;
	struct apm_mcu *mcu;
	unsigned int iia, val;

	/* In case of cache on, need to disable ECC err control on all MCUs */
	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&memc->mcu[iia];
		if (!mcu->enabled)
			continue;
		val = mcu->mcu_rd(mcu, MCU_REG_MCUGECR);
		val |= 0x8F;
		mcu->mcu_wr(mcu, MCU_REG_MCUGECR, val);
		/* Clear unexpected errors */
		mcu->mcu_wr(mcu, MCU_REG_MCUGESR, 0xFFFU);
	}
}

static void ecc_err_ctl_disable(struct apm_mcu *p_mcu)
{
	struct apm_memc *memc = (struct apm_memc *)p_mcu->parent;
	struct apm_mcu *mcu;
	unsigned int iia, val;

	/* In case of cache on, need to disable ECC err control on all MCUs */
	for (iia = 0; iia < CONFIG_SYS_NUM_DDR_CTLRS; iia++) {
		mcu = (struct apm_mcu *)&memc->mcu[iia];
		if (!mcu->enabled)
			continue;
		val = mcu->mcu_rd(mcu, MCU_REG_MCUGECR);
		val &= ~0x8F;
		mcu->mcu_wr(mcu, MCU_REG_MCUGECR, val);
	}
}

static unsigned int get_rnk_intlv_bit(struct apm_mcu *mcu, unsigned int rank)
{
	struct apm_memc *memc = (struct apm_memc *)mcu->parent;
	mcu_param_t *p_parm = &mcu->mcu_params;
	unsigned int rnk_intlv_bit = 0;

	switch (p_parm->rank_size[rank]) {
	case 0:
	case 1:
	case 2:
	case 3:
		rnk_intlv_bit = p_parm->by4_mode? 14 : 13;
		break;
	case 4:
		rnk_intlv_bit = 14; 
		break;
	case 5:
		rnk_intlv_bit = 15; 
		break;
	}
	if (memc->mcb_intrlv)
		rnk_intlv_bit ++;
	if (memc->mcb[0].mcu_intrlv || memc->mcb[1].mcu_intrlv)
		rnk_intlv_bit ++;

	return rnk_intlv_bit;
}

/*
 * is_addr_mcu_matching: check if the addr match desired MCU
 * 	0: not match
 *	1: match
 */
static int is_addr_mcu_matching(struct apm_mcu *mcu, unsigned long long *addr)
{
	struct apm_memc *memc = (struct apm_memc *)mcu->parent;
	unsigned long long tmp = (unsigned long long)addr;
	unsigned char mcumcb_intlv = 0;

	if (memc->mcb_intrlv)
		mcumcb_intlv |= 0x1;	
	if (memc->mcb[0].mcu_intrlv || memc->mcb[1].mcu_intrlv)
		mcumcb_intlv |= (0x1 << 1);

	switch (mcumcb_intlv) {
	case 1:
		return (((tmp >> 6) & 0x1ULL) == mcu->mcb_id)? 1: 0; 
	case 2:
		return (((tmp >> 6) & 0x1ULL) == mcu->id)? 1: 0; 
	case 3:
		return ((((tmp >> 6) & 0x1ULL) == mcu->mcb_id) && 
			(((tmp >> 7) & 0x1ULL) == (mcu->id % 2)))? 1: 0; 
	}

	/* TODO: support MCU/MCB non-interleaving mode */
	switch (memc->mcu_mask) {
	case 1:	
	case 4:	
		return 1;
	default:
		break;
	}

	return 0;
}

/* Return the addr offset matching desired rank */
static unsigned long long rank_addr_offset(struct apm_mcu *mcu, 
						unsigned int rank)
{
	struct apm_memc *memc = (struct apm_memc *)mcu->parent;
	mcu_param_t *p_parm = &mcu->mcu_params;
	unsigned long long mcb_intlv_adj = 0, mcu_intlv_adj = 0, 
				rnk_intlv_adj = 0;
	unsigned int rnk_intlv_bit = 0;

	/* FIXME: add support for non rank interleave mode */
	if (mcu->mcu_ud.ud_rank_intrlv) {
		rnk_intlv_bit = get_rnk_intlv_bit(mcu, rank); 
		rnk_intlv_adj = (unsigned long long)
			((p_parm->rank_base_low[rank] & 0x7U) << rnk_intlv_bit);
	}

	switch (memc->mcu_mask) {
	case 0x1:
	case 0x4:
		mcb_intlv_adj = mcu_intlv_adj = 0;
		break;
	case 0x3:
		mcb_intlv_adj = 0;
		mcu_intlv_adj = (unsigned long long)(mcu->id << 6);
		break;
	case 0x5:
		mcb_intlv_adj = (unsigned long long)((mcu->id / 2) << 6);
		mcu_intlv_adj = 0x0; 
		break;
	case 0xF:
		mcb_intlv_adj = (unsigned long long)((mcu->id / 2) << 6);
		mcu_intlv_adj = (unsigned long long)((mcu->id % 2) << 7);
		break;
	}	

	return (rnk_intlv_adj + mcb_intlv_adj + mcu_intlv_adj);
}

/* 
 * Return rank address base of desired rank of MCU 
 * To use for non-cache sw PHY training
 */
static char *rank_addr(struct apm_mcu *mcu, unsigned int rank)
{
	struct apm_memc *memc = (struct apm_memc *)mcu->parent;
	unsigned long long rnk_offset;

	if (memc->mc_ud.ud_is_cache_on) {
		if (mcu->mcu_ud.ud_rank_intrlv) 
			return (char*)memc->memspace.str_addr[0]; 
		else
			return (char*)memc->memspace.str_addr[0] +
				rank * mcu->mcu_params.minranksize;
	}

	rnk_offset = rank_addr_offset(mcu, rank); 
	return (char*)(memc->memspace.str_addr[0]) + rnk_offset; 
}

/* Find the first proper rdlvl window and the mid point */
static int find_center_rdlvl(sw_lvl_ctx_t *ctx)
{
	struct apm_mcu *mcu = ctx->mcu;
	unsigned int slice, i, err = 0;
	char *p;
	window_t w;
	int found_w;

	w.start = w.end = w.width = 0;
	for (slice = 0; slice < PHY_SUPPORTED_LANES - 1; slice++){
		p = (char *)ctx->shmoo_data + (slice * 2) * NUM_STEPS;
		found_w = 0;
		for (i = 0; i < NUM_STEPS; i++, p++) {
			if (!found_w) { 
				if (*p == 0) {		
					continue;
				} else {
					w.start = w.end = i;
					found_w = 1;
				}
			} else {
				if ((*p == 0) || (i == NUM_STEPS - 1)) {
					w.width = w.end - w.start;
					debug("Byte[%d]: window "
						"[step 0x%x - step 0x%x]\n",
						slice, w.start, w.end);
					if (w.width * ctx->step < 
							GOOD_RDLVL_WINDOW)
						/* Not a good window */
						found_w = 0;
					else
						break;
				} else if (*p == 1) {
					w.end++;	
					continue;
				}	
			}
		}

		if (found_w) {
			ctx->mid_lvl[slice * 2] = ctx->min_dly +  
				(w.start + w.width / 2) * ctx->step;
			debug("\tCenter @ 0x%x\n", ctx->mid_lvl[2 * slice]);
		} else {
			/* Fall back to hw lvl values */
			ctx->mid_lvl[slice * 2] = ctx->hw_lvl[2 * slice]; 
			err |= 1U << (4 * slice);
			debug("Byte[%d]: Can't find a proper window\n", slice);
		}
		
		if (!mcu->mcu_params.by4_mode)
			goto skip_x4_centering;	
		p = (char *)ctx->shmoo_data + (slice * 2 + 1) * NUM_STEPS;
		found_w = 0;
		for (i = 0; i < NUM_STEPS; i++, p++) {
			if (!found_w) { 
				if (*p == 0) {		
					continue;
				} else {
					w.start = w.end = i;
					found_w = 1;
				}
			} else {
				if ((*p == 0) || (i == NUM_STEPS - 1)) {
					w.width = w.end - w.start;
					debug("Byte[%d] x4: window "
						"[step 0x%x - step 0x%x]\n",
						slice, w.start, w.end);
					if (w.width * ctx->step < 
							GOOD_RDLVL_WINDOW)
						/* Not a good window */
						found_w = 0;
					else
						break;
				} else if (*p == 1) {
					w.end++;	
					continue;
				}	
			}
		}
		if (found_w) {
			ctx->mid_lvl[slice * 2 + 1] = ctx->min_dly +  
				(w.start + w.width / 2) * ctx->step;
			debug("\tCenter @ 0x%x\n", ctx->mid_lvl[slice * 2 + 1]);
		} else {
			/* Fall back to hw lvl values */
			ctx->mid_lvl[slice * 2 + 1] = ctx->hw_lvl[slice * 2 + 1];
			err |= 1U << (4 * slice);
			debug("Byte[%d] x4: Can't find a proper window\n", slice);
		}
skip_x4_centering:
		;
	}

	return err;
}

static int memtest_allbits_per_rank(sw_lvl_ctx_t *ctx, unsigned int step) 
{
	struct apm_mcu *mcu = ctx->mcu;
	unsigned long long v, q, seed;	
	int iter, i, j, slice;
	unsigned long long *ptr1, *ptr2;
	unsigned long long data_mask;
	char *p;
	char pass[PHY_SUPPORTED_LANES * 2] = 
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

	iter = 1;
	seed = 10010 + 0x10000000*iter;

memtest_loop1:
	/* random write */
	ptr1 = (unsigned long long *)rank_addr(mcu, ctx->rank) + iter*0x80000ULL;
	ptr2 = ptr1 + 0x40000ULL; 
	for (i = 0; i < 16*1024; i++) {
		for (j = 0; j < 8; j++) {
			v = rand_val(&seed);
			*ptr1++ = *ptr2++ = v;
		}
	}
	flush_dcache_all();
	/* Make sure all the bits get flipped */
	ptr1 = (unsigned long long *)rank_addr(mcu, ctx->rank) + iter*0x80000ULL;
	ptr2 = ptr1 + 0x40000ULL; 
	for (i = 0; i < 16*1024; i++) {
		for (j = 0; j < 8; j++) {
			q = rand_val(&seed);	
			*ptr1 ^= q; 
			*ptr2 ^= q;
			*ptr1++ ^= ~q; 
			*ptr2++ ^= ~q;
		}
	}
	flush_dcache_all();
	/* compare */
	ptr1 = (unsigned long long *)rank_addr(mcu, ctx->rank) + iter*0x80000ULL;
	ptr2 = ptr1 + 0x40000ULL; 
	for (i = 0; i < 16*1024; i++) {
		for (j = 0; j < 8; j++) {
			/* Only compare addresses belong to the trained MCU */
			if (!is_addr_mcu_matching(mcu, ptr1)){
				ptr1++;
				ptr2++;
				continue;
			}
			for (slice = 0; slice < PHY_SUPPORTED_LANES-1; slice++){
				if (mcu->mcu_params.by4_mode) {
					if (!pass[slice*2] && !pass[slice*2+1])
						continue;
					data_mask = 0xFFULL << (slice * 8);
					if (compare_data(ptr1, ptr2, data_mask)){
						data_mask = 0x0FULL << (slice*8);
						if (compare_data(ptr1, ptr2, 
								data_mask))
							pass[slice * 2] = 0;
						else
							pass[slice * 2 + 1] = 0;
					}
				} else {
					if (!pass[slice * 2])
						continue;
					data_mask = 0xFFULL << (slice * 8);
					if (compare_data(ptr1, ptr2, data_mask))
						pass[slice * 2] = 0;
				}
			}
			ptr1++;
			ptr2++;
		}
	}

	if (--iter > 0) 
		goto memtest_loop1;
	
	/* update result */
	for (slice = 0; slice < PHY_SUPPORTED_LANES - 1; slice++) {
		p = (char *)ctx->shmoo_data + (slice * 2) * NUM_STEPS + step;	
		*p = pass[slice * 2]; 
		if (mcu->mcu_params.by4_mode) {
			p = (char *)ctx->shmoo_data + 
					(slice * 2 + 1) * NUM_STEPS + step;	
			*p = pass[slice * 2 + 1]; 
		}
	}

	return 0;
}

/* Use this memtest if cache is turned off */
static int memtest_allbits_per_rank_nocache(sw_lvl_ctx_t *ctx, unsigned int step)
{
	struct apm_mcu *mcu = ctx->mcu;
	unsigned long long v, q, seed;	
	int iter, j, slice;
	unsigned long long *ptr1, *ptr2;
	unsigned long long data_mask;
	char *p;
	char pass[PHY_SUPPORTED_LANES * 2] = 
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

	iter = 50;
	seed = 10010 + 0x10000000*iter;

memtest_loop:
	/* random write */
	ptr1 = (unsigned long long *)rank_addr(mcu, ctx->rank) + iter*0x8000U;
	ptr2 = ptr1 + 0x20;

	for (j = 0; j < 8; j++) {
		v = rand_val(&seed);
		*ptr1++ = *ptr2++ = v;
	}

	/* Make sure all the bits get flipped */
	ptr1 = (unsigned long long *)rank_addr(mcu, ctx->rank) + iter*0x8000U;
	ptr2 = ptr1 + 0x20;
	for (j = 0; j < 8; j++) {
		q = rand_val(&seed);	
		*ptr1 ^= q; 
		*ptr2 ^= q;
		*ptr1++ ^= ~q; 
		*ptr2++ ^= ~q;
	}

	/* compare */
	ptr1 = (unsigned long long *)rank_addr(mcu, ctx->rank) + iter*0x8000U;
	ptr2 = ptr1 + 0x20; 
	for (j = 0; j < 8; j++) {
		for (slice = 0; slice < PHY_SUPPORTED_LANES - 1; slice++){
			if (mcu->mcu_params.by4_mode) {
				if (!pass[slice * 2] && !pass[slice * 2 + 1])
					continue;
				data_mask = 0xFFULL << (slice * 8);
				if (compare_data(ptr1, ptr2, data_mask)) {
					data_mask = 0x0FULL << (slice * 8);
					if (compare_data(ptr1, ptr2, data_mask))
						pass[slice * 2] = 0;
					else
						pass[slice * 2 + 1] = 0;
				}
			} else {
				if (!pass[slice * 2])
					continue;
				data_mask = 0xFFULL << (slice * 8);
				if (compare_data(ptr1, ptr2, data_mask))
					pass[slice * 2] = 0;
			}
		}
		ptr1++;
		ptr2++;
	}

	if (iter > 0) {
		iter--;
		goto memtest_loop;
	}

	/* update result */
	for (slice = 0; slice < PHY_SUPPORTED_LANES - 1; slice++) {
		p = (char *)ctx->shmoo_data + (slice * 2) * NUM_STEPS + step;	
		*p = pass[slice * 2]; 
		if (mcu->mcu_params.by4_mode) {
			p = (char *)ctx->shmoo_data + 
					(slice * 2 + 1) * NUM_STEPS + step;	
			*p = pass[slice * 2 + 1]; 
		}
	}

	return 0;
}

static int sw_phy_train_rdlvl_per_rank(struct apm_mcu *mcu, unsigned int rank)
{
	struct apm_memc *memc = (struct apm_memc *)mcu->parent;
	sw_lvl_ctx_t ctx;
	unsigned int i, slice, err = 0;
	rnk_tr_dly_val_t *rnk_tr_dly = &mcu->phy_tr_dly.rank_dly[rank];
	char result[PHY_SUPPORTED_LANES * 2][NUM_STEPS];

	debug("sw rdlvl mcu %d - rank %d\n", mcu->id, rank);
	memset(&ctx, 0, sizeof(ctx));
	ctx.mcu = mcu;
	ctx.rank = rank;
	ctx.min_dly = MIN_RDLVL_DLY;
	ctx.max_dly = min(mcu->phy_tr_dly.rdlvl_max_delay_limit, MAX_RDLVL_DLY);
	ctx.step = max(mcu->phy_tr_dly.rdlvl_dly_stsize, RDLVL_STEP);
	ctx.shmoo_data = (void *)&result;
	memset(&result, 0, sizeof(result));
	debug("leveling...[0x%x - 0x%x] - step %d\n",
			ctx.min_dly, ctx.max_dly, ctx.step);

	/* Saving h/w rdlvl values */
	for (slice = 0; slice < PHY_SUPPORTED_LANES; slice++){ 
		ctx.hw_lvl[slice * 2] = rnk_tr_dly->rd_lvl[slice * 2];
		if (mcu->mcu_params.by4_mode)
			ctx.hw_lvl[slice * 2 + 1] = 
					rnk_tr_dly->rd_lvl[slice * 2 + 1];
	}

	/* Start finding rdlvl windows of all bytes except ECC byte */
	for (i = 0; i < NUM_STEPS; i++) {
		for (slice = 0; slice < PHY_SUPPORTED_LANES - 1; slice++) { 
			rnk_tr_dly->rd_lvl[slice * 2] = ctx.min_dly + 
							i * ctx.step;
			if (mcu->mcu_params.by4_mode)
				rnk_tr_dly->rd_lvl[slice * 2 + 1] = ctx.min_dly 
							+ i * ctx.step;
		}
		phy_restore_train_dly_csrs(mcu, (0x1U << ctx.rank), 0, 0, 1);	
		mcu_phy_rdfifo_reset(mcu);

		/* depend on cache on/off use proper routine */
		if (memc->mc_ud.ud_is_cache_on)
			err = memtest_allbits_per_rank(&ctx, i);
		else
			err = memtest_allbits_per_rank_nocache(&ctx, i);
	}

	/* Centering the rdlvl within the found windows */
	err += find_center_rdlvl(&ctx);
	if (err) 
		debug("Can't find proper windows on some slices: %08x\n", err);
	for (slice = 0; slice < PHY_SUPPORTED_LANES - 1; slice++) {
		rnk_tr_dly->rd_lvl[slice * 2] = ctx.mid_lvl[slice * 2];
		if (mcu->mcu_params.by4_mode)
			rnk_tr_dly->rd_lvl[slice * 2 + 1] = 
						ctx.mid_lvl[slice * 2 + 1];
	}
	phy_restore_train_dly_csrs(mcu, (0x1U << ctx.rank), 0, 0, 1);	
	mcu_phy_rdfifo_reset(mcu);

	/* Display result windows */
	sw_rdlvl_display_result(&ctx);

	return err;	
}

static int sw_phy_retrain_rdlvl(struct apm_mcu *mcu)
{
	unsigned long rankmask =  mcu->phy_tr_dly.rank_mask;
	unsigned int iia, err = 0;

	for (iia = 0; iia < MCU_SUPPORTED_RANKS; iia++) {
                if (!((rankmask >> iia) & 0x1))
			continue;
		err += sw_phy_train_rdlvl_per_rank(mcu, iia); 
        }

	return err;
}

int sw_phy_retrain(void *p)
{
	struct apm_mcu *mcu = (struct apm_mcu *)p;
	unsigned int err = 0;

	/* Disable ECC err control to avoid exception */
	if (mcu->mcu_params.ECCenable)	
		ecc_err_ctl_disable(mcu);

	debug0("PHY calibrating ...");
	debug("\n");	
	if (mcu->mcu_ud.ud_sw_rdlvl)
		err = sw_phy_retrain_rdlvl(mcu);
	debug("\n");	
	debug0("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");	

	/* Enable ECC err control again */
	if (mcu->mcu_params.ECCenable)	
		ecc_err_ctl_enable(mcu);

	/* Display sw rde lvl values */
	phy_display_post_train_csrs(mcu, mcu->phy_tr_dly.rank_mask);

	return err;	
}
