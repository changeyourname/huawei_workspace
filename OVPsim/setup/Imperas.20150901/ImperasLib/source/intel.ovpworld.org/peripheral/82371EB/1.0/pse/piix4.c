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

#include <string.h>

#include "peripheral/impTypes.h"
#include "peripheral/bhm.h"
#include "pci.h"

#define PREFIX              "PIIX4"

static void pciInit(void)
{
    /* setup PCI configuration registers */
    pciConfig.vendorID         = 0x8086;
    pciConfig.deviceID         = 0x7110;

    pciConfig.command          = 0x0007;
    pciConfig.status           = 0x0200;

    pciConfig.revisionID       = 0x00;
    pciConfig.classCode[0]     = 0x00;
    pciConfig.classCode[1]     = 0x01;
    pciConfig.classCode[2]     = 0x06;

    pciConfig.headerType       = 0x80;

    pciConfig.user.bytes[0x20] = 0x0a;
    pciConfig.user.bytes[0x21] = 0x0a;
    pciConfig.user.bytes[0x22] = 0x0b;
    pciConfig.user.bytes[0x23] = 0x0b;

    pciConfig.user.bytes[0x28] = 0x00;
    pciConfig.user.bytes[0x29] = 0x02;
    pciConfig.user.bytes[0x2a] = 0x00;
    pciConfig.user.bytes[0x2b] = 0x00;

    pciConfig.user.bytes[0x32] = 0x02; /* SMRAM */
    pciInstallUserWritable(0x40, 4, NULL, NULL);
}


int main(int argc, char **argv) {
	// Model Documentation
    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "PIIX4 PCI configuration controller");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model has sufficient functionality to allow a Linux Kernel to Boot on the MIPS:MALTA platform.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Intel 82371EB South Bridge Chipset Datasheet");
    }

    pciInit();
    pciConnectConfigSlavePort(PREFIX, NULL);
    pciInstallUserWritable(0x68, 4, NULL, NULL);
    if (BHM_DIAG_LOW) {
        bhmMessage("I", PREFIX, "Starting.");
    }
    return 0;
}

