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

#include "string.h"

#include "peripheral/impTypes.h"
#include "peripheral/bhm.h"
#include "peripheral/ppm.h"

#define PREFIX              "FlashDevice"

//
// Changing these requires changes to model.xml
//
#define FLASH_PORT_NAME         "flash"

static Uns32             diagLevel = 0;

void flashInit(const char *portName, const char *fileName, const char *endian)
{
    bhmMessage("F", PREFIX, "Failed to intercept : %s", __FUNCTION__);
}

void flashSetDiag(Uns32 diag)
{
    bhmMessage("F", PREFIX, "Failed to intercept : %s", __FUNCTION__);
}

//
// Set the local diag level
//
static void setDiagLevel(Uns32 d)
{
    diagLevel = d & 0x0f;
    flashSetDiag((d & 0xf0)>>4);

}

int main(int argc, char **argv)
{
	// Model Documentation
    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of AMD Am29 Flash memory device");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Only basic erase and programming commands are supported");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "AMD Am29 datasheet");
    }
    const char initFile[BHM_MAX_PATH];
    const char *initFileP= NULL;
    const char endian[16] = "little";

    bhmInstallDiagCB(setDiagLevel);

    if (bhmStringAttribute("init", (char *)initFile, sizeof(initFile))) {
        initFileP = initFile;
    }

    bhmStringAttribute("endian", (char *)endian, sizeof(endian));

    flashInit(FLASH_PORT_NAME, initFileP, endian);

    // now sit and wait for things to happen
    if(BHM_DIAG_LOW) bhmMessage("I", PREFIX, "main done\n");
    bhmEventHandle never = bhmCreateEvent();

    bhmWaitEvent(never);
    return 0;
}
