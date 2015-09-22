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
#include "peripheral/ppm.h"
#include "pci.h"

#define PREFIX              "PCI_USB"


/////////////////// PCI main IO bus window ///////////////////

#define PCI_IO_WINDOW_SIZE 14

Uns8 pciBusWindow[PCI_IO_WINDOW_SIZE];

static PPM_WRITE_CB(ioRegWrite) {
    bhmMessage("I", PREFIX, "ioRegWrite");
}

static PPM_READ_CB(ioRegRead) {
    bhmMessage("I", PREFIX, "ioRegRead");
    return 0;
}

static void pciInit(void)
{
    /* setup PCI configuration registers */
    pciConfig.vendorID       = 0x8086;
    pciConfig.deviceID       = 0x7112;
    pciConfig.revisionID     = 0x01;
    pciConfig.classCode[0]   = 0x00;
    pciConfig.classCode[1]   = 0x03;
    pciConfig.classCode[2]   = 0x0C;
    pciConfig.interruptPin   = 0x04;
    pciConfig.user.bytes[20] = 0x10;
    pciConfig.baseAddress[4] = 0x00000001;

    pciInstallRegion(0x20, 0xffffffe1, pciBusWindow, NULL, PCI_IO_WINDOW_SIZE);
    ppmInstallWriteCallback(ioRegWrite, 0, pciBusWindow, PCI_IO_WINDOW_SIZE);
    ppmInstallReadCallback (ioRegRead,  0, pciBusWindow, PCI_IO_WINDOW_SIZE);
}



int main(int argc, char **argv) {
	// Model Documentation
    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "PCI USB Interface");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model has sufficient functionality to allow a Linux Kernel to Boot on the MIPS:MALTA platform");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Intel 82371EB South Bridge Chipset Datasheet");
    }
    pciInit();
    pciConnectConfigSlavePort(PREFIX, NULL);
    if (BHM_DIAG_LOW) {
        bhmMessage("I", PREFIX, "Starting.");
    }
    return 0;
}

