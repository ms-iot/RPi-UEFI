/**
 * @file
 *
 * PCI configuration space backup and restoration
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
#ifndef _IPXE_PCIBACKUP_H
#define _IPXE_PCIBACKUP_H

#include "common.h"

/** A PCI configuration space backup */
struct pci_config_backup {
	uint32_t dwords[64];
};

/** PCI configuration space backup exclusion list end marker */
#define PCI_CONFIG_BACKUP_EXCLUDE_END 0xff

/** Define a PCI configuration space backup exclusion list */
#define PCI_CONFIG_BACKUP_EXCLUDE(...) \
	{ __VA_ARGS__, PCI_CONFIG_BACKUP_EXCLUDE_END }

extern void pci_backup ( EFI_PCI_IO_PROTOCOL *pci,
			 struct pci_config_backup *backup,
			 const uint8_t *exclude );
extern void pci_restore ( EFI_PCI_IO_PROTOCOL *pci,
			  struct pci_config_backup *backup,
			  const uint8_t *exclude );

#endif /* _IPXE_PCIBACKUP_H */
