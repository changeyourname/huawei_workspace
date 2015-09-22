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


#include "pse.igen.h"
/////////////////////////////// Port Declarations //////////////////////////////

bport1_ab_dataT bport1_ab_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "VirtioBlkMMIO", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 512);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    ppmCreateRegister("ab_MagicValue",
        "Magic value ('virt' string)",
        handles.bport1,
        0,
        4,
        rdMagic,
        0,
        view32,
        &(bport1_ab_data.MagicValue.value),
        True
    );
    ppmCreateRegister("ab_Version",
        "Device Version number",
        handles.bport1,
        4,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.Version.value),
        True
    );
    ppmCreateRegister("ab_DeviceID",
        "Block Subsystem Device ID",
        handles.bport1,
        8,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.DeviceID.value),
        True
    );
    ppmCreateRegister("ab_VendorID",
        "Subsystem Vendor ID ('OVP' string)",
        handles.bport1,
        12,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.VendorID.value),
        True
    );
    ppmCreateRegister("ab_HostFeatures",
        "Host features flags",
        handles.bport1,
        16,
        4,
        rdHostF,
        0,
        view32,
        &(bport1_ab_data.HostFeatures.value),
        True
    );
    ppmCreateRegister("ab_HostFSel",
        "Host features select",
        handles.bport1,
        20,
        4,
        0,
        wrSel,
        view32,
        &(bport1_ab_data.HostFSel.value),
        True
    );
    ppmCreateRegister("ab_GuestFeatures",
        "Guest features flags",
        handles.bport1,
        32,
        4,
        0,
        wrGuestF,
        view32,
        &(bport1_ab_data.GuestFeatures.value),
        True
    );
    ppmCreateRegister("ab_GuestFSel",
        "Guest features select",
        handles.bport1,
        36,
        4,
        0,
        wrSel,
        view32,
        &(bport1_ab_data.GuestFSel.value),
        True
    );
    ppmCreateRegister("ab_GuestPageSz",
        "Guest page size",
        handles.bport1,
        40,
        4,
        0,
        wrGPgSz,
        view32,
        &(bport1_ab_data.GuestPageSz.value),
        True
    );
    ppmCreateRegister("ab_QueueSel",
        "Virtual queue index",
        handles.bport1,
        48,
        4,
        0,
        wrSel,
        view32,
        &(bport1_ab_data.QueueSel.value),
        True
    );
    ppmCreateRegister("ab_QueueNumMax",
        "Maximum virtual queue size",
        handles.bport1,
        52,
        4,
        read_32,
        0,
        view32,
        &(bport1_ab_data.QueueNumMax.value),
        True
    );
    ppmCreateRegister("ab_QueueNum",
        "Virtual queue size",
        handles.bport1,
        56,
        4,
        0,
        wrQNum,
        view32,
        &(bport1_ab_data.QueueNum.value),
        True
    );
    ppmCreateRegister("ab_QueueAlign",
        "Virtual queue align",
        handles.bport1,
        60,
        4,
        0,
        wrQAlign,
        view32,
        &(bport1_ab_data.QueueAlign.value),
        True
    );
    ppmCreateRegister("ab_QueuePFN",
        "Virtual queue PFN",
        handles.bport1,
        64,
        4,
        rdQPFN,
        wrQPFN,
        view32,
        &(bport1_ab_data.QueuePFN.value),
        True
    );
    ppmCreateRegister("ab_QueueNotify",
        "Virtual queue notify",
        handles.bport1,
        80,
        4,
        0,
        wrQNotify,
        view32,
        &(bport1_ab_data.QueueNotify.value),
        True
    );
    ppmCreateRegister("ab_IntStatus",
        "Interrupt status",
        handles.bport1,
        96,
        4,
        rdIntStat,
        0,
        view32,
        &(bport1_ab_data.IntStatus.value),
        True
    );
    ppmCreateRegister("ab_IntAck",
        "Interrupt acknowlege",
        handles.bport1,
        100,
        4,
        0,
        wrIntAck,
        view32,
        &(bport1_ab_data.IntAck.value),
        True
    );
    ppmCreateRegister("ab_Status",
        "Device status",
        handles.bport1,
        112,
        4,
        rdStatus,
        wrStatus,
        view32,
        &(bport1_ab_data.Status.value),
        True
    );

}

/////////////////////////////// Bus Master Ports ///////////////////////////////

static void installMasterPorts(void) {
    handles.dma = ppmOpenAddressSpace("dma");
    if (!handles.dma) {
        bhmMessage("E", "PPM_MPNC", "Could not connect port 'dma'");
    }
}

/////////////////////////////////// Net Ports //////////////////////////////////

static void installNetPorts(void) {
// To write to this net, use ppmWriteNet(handles.Interrupt, value);

    handles.Interrupt = ppmOpenNetPort("Interrupt");

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.Status.value = 0x0;
        bport1_ab_data.IntAck.value = 0x0;
        bport1_ab_data.IntStatus.value = 0x0;
        bport1_ab_data.QueueNotify.value = 0x0;
        bport1_ab_data.QueuePFN.value = 0x0;
        bport1_ab_data.QueueAlign.value = 0x0;
        bport1_ab_data.QueueNum.value = 0x0;
        bport1_ab_data.QueueNumMax.value = 0x100;
        bport1_ab_data.QueueSel.value = 0x0;
        bport1_ab_data.GuestPageSz.value = 0x0;
        bport1_ab_data.GuestFSel.value = 0x0;
        bport1_ab_data.GuestFeatures.value = 0x0;
        bport1_ab_data.HostFSel.value = 0x0;
        bport1_ab_data.HostFeatures.value = 0x8000000;
        bport1_ab_data.VendorID.value = 0x50564f;
        bport1_ab_data.DeviceID.value = 0x2;
        bport1_ab_data.Version.value = 0x1;
        bport1_ab_data.MagicValue.value = 0x74726976;
    }
}

////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installMasterPorts();
    installNetPorts();
    reset_Reset(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "\n VIRTIO version 1 mmio block device\n This model implements a VIRTIO  MMIO block device as described in:\n      http://docs.oasis-open.org/virtio/virtio/v1.0/virtio-v1.0.pdf.\n Use the VB_DRIVE parameter to specify the disk image file to use.\n Set the VB_DRIVE_DELTA parameter to 1 to prevent writes to disk during \n simulation from changing the image file.\n");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "\nOnly supports the Legacy (Device Version 1) interface.\nOnly little endian guests are supported.\n");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_22_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "\nhttp://docs.oasis-open.org/virtio/virtio/v1.0/virtio-v1.0.pdf\n");
    }

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

