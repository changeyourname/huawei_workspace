/*
 * Copyright (c) 2011-2014 Posedge Software Inc., www.posedgesoft.com
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

#include <stdio.h>
#include <string.h>

#include "pse.igen.h"

//////////////////////////////// Callback stubs ////////////////////////////////
#define muxRegisters bport1_ab_dataT
#define THREAD_STACK (8*1024)

muxRegisters *muxReg;
static char periphName[] = "KinetisDMAMUX";

typedef struct chConfigS
{
    void * regAddr;         
} chConfigT, *chConfigP;

typedef struct srcConfigS
{
    Uns32 dmaChannel;
    Uns32 lastRequestValue;
} srcConfigT, *srcConfigP;

typedef struct {
    bhmThreadHandle thread;
    char            stack[THREAD_STACK];
} muxStateT, *muxStateP;

static muxStateT muxState;
Uns32 startDMAChannel = 0;

chConfigT chConfig[16];
srcConfigT srcConfig[64];

/////////////////////////////////////////////////////////////
// Functions to access the CHCFG bit fields.
/////////////////////////////////////////////////////////////
static int isChannelEnabled(Uns32 chNum)
{
    return ((*(Uns32 *) chConfig[chNum].regAddr) & 0x80);
}

// If we start using the trigger, uncomment this function to access the TRIG
// bitfield in the Channel configuration.
static int isTriggerEnabled(Uns32 chNum)
{
    // Only have triggers on first 4 channels. Ignore if not one of these.
    if (chNum > 4)
        return 0;

    return ((*(Uns32 *) chConfig[chNum].regAddr) & 0x40);
}

static Uns32 sourceNum(Uns32 chNum)
{
    return ((*(Uns32 *) chConfig[chNum].regAddr) & 0x3f);
}


static int sendDMARequest(Uns32 chNum)
{
    if ((chNum < 0) || (chNum > 16))
        return 1;

    if (isChannelEnabled(chNum))
    {
        if (diagnosticLevel >= 2)
            bhmMessage("I", periphName, "Sending DMA request on dmaChannel: %d", chNum + startDMAChannel);
        ppmWriteNet(handles.eDMARequest, (ppmNetValue) (chNum + startDMAChannel));
    }
    else
        bhmMessage("W", periphName, "Attempting to sendDMA request on disabled channel: %d", chNum);

    return 0;
}

static void updateSrcConfig(Uns32 chNum, Uns32 data)
{
    Uns32 lastSrc = sourceNum(chNum);
    Uns32 newSrc = (data & 0x3f);

    // Clear the previous user of this channel, and set the new user.
    srcConfig[lastSrc].dmaChannel = (Uns32) -1;
    srcConfig[newSrc].dmaChannel = chNum;
}

PPM_REG_WRITE_CB(dmamuxWrite) {
    Uns32 chNum = (Uns32) addr - (Uns32) handles.bport1;

    if (diagnosticLevel >= 2)
        bhmMessage("I", periphName, "Channel %d Config size = %d val = 0x%x", chNum, bytes, data);

    if ((chNum < 0) || (chNum > 16))
        bhmMessage("W", periphName, "Channel %d out of range", chNum);

    updateSrcConfig(chNum, data);

    *(Uns8*)user = (*(Uns8*)user & 0x0) | (data & 0xff);

    if (diagnosticLevel >= 3)
        bhmMessage("I", periphName, "val = 0x%x", *(int *) chConfig[chNum].regAddr);
}

PPM_NET_CB(dmaSrcRequest) {
    Uns32 srcRequest = (Uns32) userData;

    if (diagnosticLevel >= 2)
        bhmMessage("I", periphName, "Recieved dma request on Source Channel: %d, value = %d", srcRequest, value);

    if ((srcRequest < 0) || (srcRequest > 64))
        bhmMessage("F", periphName, "Source request channel out of range: %d", srcRequest);

    if (value == 0)
    {
        srcConfig[srcRequest].lastRequestValue = 0;
    } else if ((value == 1) && (srcConfig[srcRequest].lastRequestValue == 0))
    {
        srcConfig[srcRequest].lastRequestValue = 1;
        if (sendDMARequest(srcConfig[srcRequest].dmaChannel))
            bhmMessage("W", periphName, "Error sending DMARequest: Source: %d  dmaChannel: %d", value, srcConfig[srcRequest].dmaChannel);
    }
}

PPM_NET_CB(dmaTrgRequest) {
    Uns32 trgRequest = (Uns32) userData - 1;

    if (diagnosticLevel >= 3)
        bhmMessage("I", periphName, "Recieved triggered dma request on Source Channel: %d", trgRequest);

    if ((trgRequest < 0) || (trgRequest > 4))
        bhmMessage("W", periphName, "Trigger request out of range: %d", trgRequest);

    if (isTriggerEnabled(trgRequest))
    {
        bhmMessage("I", periphName, "send triggered dma request on Source Channel: %d", trgRequest);
        if (sendDMARequest(trgRequest))
            bhmMessage("W", periphName, "Error sending Triggered DMARequest: Trigger: %d", trgRequest);
    }
}

static void DMAMUX_Thread(void *user)
{
    // All of the functionality is handled in the callbacks. Thread just
    // waits for the end of the simulation before exiting.
    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
}

void userInit(void)
{
    if (diagnosticLevel >= 2)
        bhmMessage("I", periphName, "User Initialization: Starting DMAChannel = %d", startDMAChannel);

    muxReg = (muxRegisters *) &bport1_ab_data;

    // clear out chConfig and srcConfig.
    memset(chConfig, 0, sizeof(chConfigT) * 16);
    memset(srcConfig, 0, sizeof(srcConfigT) * 64);
    
    // Provide an array index into the CHCFG registers.
    chConfig[0].regAddr = &(bport1_ab_data.CHCFG0.value);
    chConfig[1].regAddr = &(bport1_ab_data.CHCFG1.value);
    chConfig[2].regAddr = &(bport1_ab_data.CHCFG2.value);
    chConfig[3].regAddr = &(bport1_ab_data.CHCFG3.value);
    chConfig[4].regAddr = &(bport1_ab_data.CHCFG4.value);
    chConfig[5].regAddr = &(bport1_ab_data.CHCFG5.value);
    chConfig[6].regAddr = &(bport1_ab_data.CHCFG6.value);
    chConfig[7].regAddr = &(bport1_ab_data.CHCFG7.value);
    chConfig[8].regAddr = &(bport1_ab_data.CHCFG8.value);
    chConfig[9].regAddr = &(bport1_ab_data.CHCFG9.value);
    chConfig[10].regAddr = &(bport1_ab_data.CHCFG10.value);
    chConfig[11].regAddr = &(bport1_ab_data.CHCFG11.value);
    chConfig[12].regAddr = &(bport1_ab_data.CHCFG12.value);
    chConfig[13].regAddr = &(bport1_ab_data.CHCFG13.value);
    chConfig[14].regAddr = &(bport1_ab_data.CHCFG14.value);
    chConfig[15].regAddr = &(bport1_ab_data.CHCFG15.value);

    // Set our internal array to unconnected.
    int ii;
    for (ii = 0; ii < 64; ii ++)
    {
        srcConfig[ii].dmaChannel = (Uns32) -1;
        srcConfig[ii].lastRequestValue = 0;
    }

    // Create our thread.
    char threadName[32];
    sprintf(threadName, "dmaMux");
    muxState.thread = bhmCreateThread(
            DMAMUX_Thread,
            (void *) 0,
            threadName,
            &muxState.stack[THREAD_STACK]
        );
    
}

PPM_CONSTRUCTOR_CB(constructor) {
    // YOUR CODE HERE (pre constructor)
    bhmIntegerAttribute("startDMAChannel", &startDMAChannel);

    periphConstructor();

    // YOUR CODE HERE (post constructor)
    userInit();
}



// Save / restore callbacks

PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}

