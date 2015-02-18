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

#ifndef _DDR_LRDIMM_UTIL_H_
#define _DDR_LRDIMM_UTIL_H_

#if defined(APM_VBIOS) || defined(APM_TIANOCORE)
#define imb_write(a,r,d,b)   /* imb_write not supported */
#define imb_read(a,r,b)    0 /* imb_read not supported */
#endif

unsigned int lrdimm_mb_init_from_spd_preinit(void *p, unsigned int slot);
unsigned int lrdimm_mb_init_from_spd_mck(void *p, unsigned int slot);
unsigned int lrdimm_mb_init_from_spd_ck(void *p, unsigned int slot);
unsigned int lrdimm_mb_mrs(void *p, unsigned int slot);
unsigned int lrdimm_mb_mck_training(void *p, unsigned int slot);
unsigned int lrdimm_mb_ck_training(void *p, unsigned int slot);
unsigned int lrdimm_mb_normal_op(void *p, unsigned int slot);
unsigned int lrdimm_mb_WRleveling(void *p, unsigned int slot);

/* LRDIMM  Currently sypport only INPHI LRDIMM */
#define LRDIMM_INPHI_MR_CONFIG 1

#endif /* _DDR_LRDIMM_UTIL_H_ */
