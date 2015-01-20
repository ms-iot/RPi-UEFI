/** 
 * Copyright (c) 2013, AppliedMicro Corp. All rights reserved.
 *  
 *  This program and the accompanying materials
 *  are licensed and made available under the terms and conditions of the BSD License
 *  which accompanies this distribution.  The full text of the license may be found at
 *  http://opensource.org/licenses/bsd-license.php
 *  
 *  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 *  
 **/
 
 #ifndef _DWSPICsr_H_
 #define _DWSPICsr_H_
 
#define DWSPI_CSR_SIZE  0x1000

#define DWSPI_CTRLR0(base)		((base) + 0x00)
#define DWSPI_CTRLR1(base)		((base) + 0x04)
#define DWSPI_SSIENR(base)		((base) + 0x08)
#define DWSPI_MWCR(base)		((base) + 0x0C)
#define DWSPI_SER(base)			((base) + 0x10)
#define DWSPI_BAUDR(base)		((base) + 0x14)
#define DWSPI_TXFTLR(base)		((base) + 0x18)
#define DWSPI_RXFTLR(base)		((base) + 0x1C)
#define DWSPI_TXFLR(base)		((base) + 0x20)
#define DWSPI_RXFLR(base)		((base) + 0x24)
#define DWSPI_SR(base)			((base) + 0x28)
#define DWSPI_IMR(base)			((base) + 0x2C)
#define DWSPI_ISR(base)			((base) + 0x30)
#define DWSPI_RISR(base)		((base) + 0x34)
#define DWSPI_TXOICR(base)		((base) + 0x38)
#define DWSPI_RXOICR(base)		((base) + 0x3C)
#define DWSPI_RXUICR(base)		((base) + 0x40)
#define DWSPI_ICR(base)			((base) + 0x44)
#define DWSPI_DMACR(base)		((base) + 0x4C)
#define DWSPI_DMATDLR(base)		((base) + 0x50)
#define DWSPI_DMARDLR(base)		((base) + 0x54)
#define DWSPI_IDR(base)			((base) + 0x58)
#define DWSPI_SSI_VER(base)		((base) + 0x5C)
#define DWSPI_DR(base)			((base) + 0x60)
    
#define DWSPI_SSIENR_SSI_EN_MASK	0x1
    
#define DWSPI_CTRLR0_DFS_MASK		0x000f
#define DWSPI_CTRLR0_DFS_VAL		0x7
#define DWSPI_CTRLR0_SCPOL_MASK		0x0080
#define DWSPI_CTRLR0_SCPH_MASK		0x0040
#define DWSPI_CTRLR0_TMOD_MASK		0x0300
#define DWSPI_CTRLR0_TMOD_SHIFT		8
#define DWSPI_CTRLR0_TMOD_TXRX		0x0
#define DWSPI_CTRLR0_TMOD_RX		0x1
#define DWSPI_CTRLR0_TMOD_TX		0x2
#define DWSPI_CTRLR0_TMOD_EEPROM	0x3
    
#define DWSPI_CTRLR1_MASK		0xFFFF
    
#define DWSPI_SR_BUSY_MASK		0x01
#define DWSPI_SR_TFNF_MASK		0x02
#define DWSPI_SR_TFE_MASK		0x04
#define DWSPI_SR_RFNE_MASK		0x08
#define DWSPI_SR_RFF_MASK		0x10
    
#define DWSPI_ISR_TXEIS_MASK		0x01
#define DWSPI_ISR_RXFIS_MASK		0x10
#define DWSPI_IMR_TXEIM_MASK		0x01
#define DWSPI_IMR_RXFIM_MASK		0x10
#define DWSPI_IMR_VAL			0x0
    
#define DWSPI_TXFTLR_VAL		(DWSPI_TX_FIFO_DEPTH-1)
#define DWSPI_RXFTLR_VAL		0x0
    
#define DWSPI_TUNNING_DELAY		0x100000
 
 #endif /* _DWSPICsr_H_ */
