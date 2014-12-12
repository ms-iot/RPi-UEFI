/** @file
 *
 * Infiniband Subnet Management Client
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
#ifndef _IPXE_IB_SMC_H
#define _IPXE_IB_SMC_H

#include "infiniband.h"

typedef int ( * ib_local_mad_t ) ( struct ib_device *ibdev,
				   union ib_mad *mad );

extern int ib_smc_init ( struct ib_device *ibdev, ib_local_mad_t local_mad );
extern int ib_smc_update ( struct ib_device *ibdev, ib_local_mad_t local_mad );

#endif /* _IPXE_IB_SMC_H */
