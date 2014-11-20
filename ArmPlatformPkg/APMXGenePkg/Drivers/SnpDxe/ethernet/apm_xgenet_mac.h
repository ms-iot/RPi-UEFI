#ifndef __APM_XGENET_MAC_H__
#define __APM_XGENET_MAC_H__

#include "apm_enet_common.h"
#if 0
#ifdef BOOTLOADER
#include <asm/arch-storm/apm88xxxx_scu.h>
#else
#include <misc/xgene/slimpro/apm88xxxx_slimpro.h>
#endif
#endif
#undef APM_XG_AXGMAC_TX2RX_LOOPBACK
#undef APM_XGENET_XGMII_TX2RX_LOOPBACK	
void apm_xgenet_init_priv(struct apm_enet_priv *priv, void *port_vaddr,
			  void *gbl_vaddr, void *mii_vaddr);
//void apm_xg_clk_rst_cfg(struct apm_enet_priv *priv);
//void apm_xgport_shutdown(struct apm_enet_priv *priv);
#endif  // __APM_XGENET_MAC_H__
