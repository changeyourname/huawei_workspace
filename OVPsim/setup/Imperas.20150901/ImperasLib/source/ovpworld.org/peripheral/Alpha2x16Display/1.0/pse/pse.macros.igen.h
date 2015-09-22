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
// Set the macro 'BUSPORT' to the base of port 'busPort'
#ifndef BUSPORT
    #error BUSPORT is undefined.It needs to be set to the port base address
#endif
#define BUSPORT_A_CONTROL    (BUSPORT + 0x0)

#define BUSPORT_A_CONTROL_INVERT   (0x1 << 3)
#define BUSPORT_A_CONTROL_SET   (0x1 << 2)
#define BUSPORT_A_CONTROL_CLEAR   (0x1 << 1)
#define BUSPORT_A_CONTROL_ENABLE   0x1
#define BUSPORT_A_ADDRESS    (BUSPORT + 0x1)

#define BUSPORT_A_STATUS    (BUSPORT + 0x2)

#define BUSPORT_A_STATUS_ENABLE   (0x1 << 1)
#define BUSPORT_A_STATUS_BUSY   0x1
#define BUSPORT_A_DATA    (BUSPORT + 0x3)



#endif
