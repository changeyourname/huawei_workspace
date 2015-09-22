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
#define BPORT1_AB_SRS0    (BPORT1 + 0x0)

#define BPORT1_AB_SRS0_LOC   (0x1 << 2)
#define BPORT1_AB_SRS0_LVD   (0x1 << 1)
#define BPORT1_AB_SRS0_PIN   (0x1 << 6)
#define BPORT1_AB_SRS0_POR   (0x1 << 7)
#define BPORT1_AB_SRS0_WAKEUP   0x1
#define BPORT1_AB_SRS0_WDOG   (0x1 << 5)
#define BPORT1_AB_SRS1    (BPORT1 + 0x1)

#define BPORT1_AB_SRS1_EZPT   (0x1 << 4)
#define BPORT1_AB_SRS1_JTAG   0x1
#define BPORT1_AB_SRS1_LOCKUP   (0x1 << 1)
#define BPORT1_AB_SRS1_MDM_AP   (0x1 << 3)
#define BPORT1_AB_SRS1_SACKERR   (0x1 << 5)
#define BPORT1_AB_SRS1_SW   (0x1 << 2)
#define BPORT1_AB_SRS1_TAMPER   (0x1 << 7)
#define BPORT1_AB_RPFC    (BPORT1 + 0x4)

#define BPORT1_AB_RPFC_RSTFLTSRW   0x3
#define BPORT1_AB_RPFC_RSTFLTSS   (0x1 << 2)
#define BPORT1_AB_RPFW    (BPORT1 + 0x5)

#define BPORT1_AB_RPFW_RSTFLTSEL   0x1f
#define BPORT1_AB_MR    (BPORT1 + 0x7)

#define BPORT1_AB_MR_EZP_MS   (0x1 << 1)


#endif
