/*
 * Copyright (C) 2009 Michael Brown <mbrown@fensystems.co.uk>.
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
#include "pcibackup.h"

/**
 * Check PCI configuration space offset against exclusion list
 *
 * @v pci		PCI device
 * @v offset		Offset within PCI configuration space
 * @v exclude		PCI configuration space backup exclusion list, or NULL
 */
static int
pci_backup_excluded ( EFI_PCI_IO_PROTOCOL *pci, unsigned int offset,
		      const uint8_t *exclude ) {

	if ( ! exclude )
		return 0;
	for ( ; *exclude != PCI_CONFIG_BACKUP_EXCLUDE_END ; exclude++ ) {
		if ( offset == *exclude ) {
			DBGC ( pci, "PCI %p skipping configuration offset "
			       "%02x\n", pci, offset );
			return 1;
		}
	}
	return 0;
}

/**
 * Back up PCI configuration space
 *
 * @v pci		PCI device
 * @v backup		PCI configuration space backup
 * @v exclude		PCI configuration space backup exclusion list, or NULL
 */
void pci_backup ( EFI_PCI_IO_PROTOCOL *pci, struct pci_config_backup *backup,
		  const uint8_t *exclude ) {
	unsigned int offset;
	uint32_t *dword;

	for ( offset = 0, dword = backup->dwords ; offset < 0x100 ;
	      offset += sizeof ( *dword ) , dword++ ) {
		if ( ! pci_backup_excluded ( pci, offset, exclude ) )
		  pci->Pci.Read (pci,
                     EfiPciIoWidthUint8,
                     offset,
                     sizeof ( *dword ),
                     dword
                     );
	}
}

/**
 * Restore PCI configuration space
 *
 * @v pci		PCI device
 * @v backup		PCI configuration space backup
 * @v exclude		PCI configuration space backup exclusion list, or NULL
 */
void pci_restore ( EFI_PCI_IO_PROTOCOL *pci, struct pci_config_backup *backup,
		   const uint8_t *exclude ) {
	unsigned int offset;
	uint32_t *dword;

	for ( offset = 0, dword = backup->dwords ; offset < 0x100 ;
	      offset += sizeof ( *dword ) , dword++ ) {
		if ( ! pci_backup_excluded ( pci, offset, exclude ) )
		  pci->Pci.Write (pci,
		                  EfiPciIoWidthUint8,
		                  offset,
		                  sizeof ( *dword ),
		                  dword
		                  );
	}
}
