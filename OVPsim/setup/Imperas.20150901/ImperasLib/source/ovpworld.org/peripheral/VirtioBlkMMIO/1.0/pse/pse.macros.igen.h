/*
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                             Version 20150901.0
//
////////////////////////////////////////////////////////////////////////////////

#ifndef PSE_MACROS_IGEN_H
#define PSE_MACROS_IGEN_H
// Before including this file in the application, define the indicated macros
// to fix the base address of each slave port.
// Set the macro 'BPORT1' to the base of port 'bport1'
#ifndef BPORT1
    #error BPORT1 is undefined.It needs to be set to the port base address
#endif
#define BPORT1_AB_MAGICVALUE    (BPORT1 + 0x0)

#define BPORT1_AB_VERSION    (BPORT1 + 0x4)

#define BPORT1_AB_DEVICEID    (BPORT1 + 0x8)

#define BPORT1_AB_VENDORID    (BPORT1 + 0xc)

#define BPORT1_AB_HOSTFEATURES    (BPORT1 + 0x10)

#define BPORT1_AB_HOSTFSEL    (BPORT1 + 0x14)

#define BPORT1_AB_GUESTFEATURES    (BPORT1 + 0x20)

#define BPORT1_AB_GUESTFSEL    (BPORT1 + 0x24)

#define BPORT1_AB_GUESTPAGESZ    (BPORT1 + 0x28)

#define BPORT1_AB_QUEUESEL    (BPORT1 + 0x30)

#define BPORT1_AB_QUEUENUMMAX    (BPORT1 + 0x34)

#define BPORT1_AB_QUEUENUM    (BPORT1 + 0x38)

#define BPORT1_AB_QUEUEALIGN    (BPORT1 + 0x3c)

#define BPORT1_AB_QUEUEPFN    (BPORT1 + 0x40)

#define BPORT1_AB_QUEUENOTIFY    (BPORT1 + 0x50)

#define BPORT1_AB_INTSTATUS    (BPORT1 + 0x60)

#define BPORT1_AB_INTSTATUS_USEDRINGUPDATE   0x1
#define BPORT1_AB_INTSTATUS_CONFIGCHANGE   (0x1 << 1)
#define BPORT1_AB_INTACK    (BPORT1 + 0x64)

#define BPORT1_AB_INTACK_USEDRINGUPDATE   0x1
#define BPORT1_AB_INTACK_CONFIGCHANGE   (0x1 << 1)
#define BPORT1_AB_STATUS    (BPORT1 + 0x70)

#define BPORT1_AB_STATUS_ACK   0x1
#define BPORT1_AB_STATUS_DRIVER   (0x1 << 1)
#define BPORT1_AB_STATUS_DRIVEROK   (0x1 << 2)
#define BPORT1_AB_STATUS_FAILED   (0x1 << 7)
#define BPORT1_AB_BLKCONFIG          (BPORT1 + 0x100)
#define BPORT1_AB_BLKCONFIG_BYTES    0x100



#endif
