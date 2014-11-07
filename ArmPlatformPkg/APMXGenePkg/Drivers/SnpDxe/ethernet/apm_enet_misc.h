/**
 * AppliedMicro APM88xxxx Ethernet Driver
 *
 * Copyright (c) 2013 Applied Micro Circuits Corporation.
 * All rights reserved. Mahesh Pujara <mpujara@apm.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * @file apm_enet_misc.c
 *
 * This file implements APM88xxxx SoC Ethernet subsystem driver
 *
 */

#ifndef __APM_ENET_MISC_H_
#define __APM_ENET_MISC_H_

#include "apm_enet_common.h"
#ifdef INT_SUPPORT
#include <linux/irqreturn.h>
#endif

int apm_enet_parse_error(u8 LErr, u8 HC, int qid);
void apm_enet_unmask_int(struct apm_enet_priv *priv);
int apm_enet_enable_link_intr(struct apm_enet_priv *priv, int enable);
void apm_enet_qmi_pop_pb_msg(struct apm_enet_priv *priv, u32 pbn,
				u32 addroffset, u32 last, u32 *msg);
void apm_enet_qmi_read_pb_msg(struct apm_enet_priv *priv, u32 pbn,
				u32 addroffset, u32 last, u32 *msg);
int apm_enet_get_pb_cnt(struct apm_enet_priv *priv, int pbn);
#ifdef CONFIG_SHADOWCAT
extern int apm_ahb_gpio_rd_bit(int pin);
#endif
#ifdef INT_SUPPORT
irqreturn_t apm_enet_qmi_err_irq(int irq, void *dev_instance);
irqreturn_t apm_enet_mac_err_irq(int irq, void *dev_instance);
irqreturn_t apm_enet_err_irq(int irq, void *dev_instance);
#endif

#endif /* __APM_ENET_MISC_H_ */
