/*
 * APM X-Gene PHY Initalization
 *
 * Copyright (c) 2014, Applied Micro Circuits Corporation
 * Author: Loc Ho <lho@apm.com>
 *
 * This program and the accompanying materials
 *are licensed and made available under the terms and conditions of the BSD License
 * which accompanies this distribution.  The full text of the license may be found at
 * http://opensource.org/licenses/bsd-license.php
 *
 * THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 * WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 */
#ifndef __XGENEPHY_H__
#define __XGENEPHY_H__

INTN xgene_ahci_init(UINT64 serdes_base, UINT64 ahci_base, UINT64 pcie_clk_base,
    UINTN cid, UINTN irq);

INTN xgene_pcie_init(UINT64 csr_base, UINTN lane, UINTN port);

#endif
