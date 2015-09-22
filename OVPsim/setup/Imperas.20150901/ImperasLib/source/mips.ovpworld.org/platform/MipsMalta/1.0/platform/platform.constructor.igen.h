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


// This file constructs the platform according to TCL script.
// This file should NOT need to be edited.

////////////////////////////////////////////////////////////////////////////////

void platformConstructor(void) {

    icmInitAttrs MipsMalta_attrs = ICM_STOP_ON_CTRLC;

    icmInitPlatform(ICM_VERSION, MipsMalta_attrs, 0, 0, "MipsMalta");


    icmDocNodeP Root1_node = icmDocSectionAdd(0, "Root");
    {
        icmDocNodeP doc2_node = icmDocSectionAdd(Root1_node, "Licensing");
        icmDocTextAdd(doc2_node, "Open Source Apache 2.0");
        icmDocNodeP doc_12_node = icmDocSectionAdd(Root1_node, "Description");
        icmDocTextAdd(doc_12_node, "This is a platform representing a MIPS Malta development board.\n    It provides the peripherals required to boot and run a Linux Operating System.\n    A single MIPS32 architecture processor is instantiated in this platform.\n    This instance could be duplicated to instantiate further processors to easily create an SMP platform.\n    Attributes are provided for configuration of the generic ISA model for a specific processor.\n    The processor model is configured to operate as a MIPS32 4KEc.\n\n    The main SDRAM and Flash memory is modeled using RAM models. Both are initialised in places by the\n    'SmartLoaderLinux'. The SmartLoaderLinux allows ease of use of changing kernel command lines,\n    loading an initial ram disk and creating the boot flash(s). The operation of the SmartloaderLinux is configured\n    using a number of attributes.  \n       The kernel attribute of the SmartLoaderLinux and the imagefile of the processor must be consistent.\n\n    NOTE: a non Mips Malta peripheral 'AlphaDisplay16x2' has been defined in this platform definition\n          to be used for demo purposes. It should be removed if there is a memory error in the address space 0x18000100-0x18000103\n\n    If this platform is not part of your installation, then it is available for download from www.OVPworld.org/MIPSuser.");
        icmDocNodeP doc_22_node = icmDocSectionAdd(Root1_node, "Limitations");
        icmDocTextAdd(doc_22_node, "Verification has only been carried out using Little Endian memory ordering.");
        icmDocNodeP doc_32_node = icmDocSectionAdd(Root1_node, "Reference");
        icmDocTextAdd(doc_32_node, "MIPS Malta User's Manual MD00048-2B-MALTA-USM-1.07.pdf\n           MIPS Malta-R Development Platform User's Manual MD00627-2B-MALTA_R-USM-01.01.pdf    \n           CoreFPGA User's Manual MD00116-2B-COREFPGA-USM-01.00.pdf\n           Linux for the MIPS Malta Development Platform Useer's Guide MD00646-2B-LINUXMALTA-USM-01.03.pdf");
    }
    icmSetPlatformStatus(ICM_OVP,ICM_EPK,ICM_VISIBLE);

////////////////////////////////////////////////////////////////////////////////
//                                  Bus bus1
////////////////////////////////////////////////////////////////////////////////


    handles.bus1_b = icmNewBus( "bus1", 32);

////////////////////////////////////////////////////////////////////////////////
//                                 Bus busPCI
////////////////////////////////////////////////////////////////////////////////


    handles.busPCI_b = icmNewBus( "busPCI", 32);

////////////////////////////////////////////////////////////////////////////////
//                               Bus busPCIReMap
////////////////////////////////////////////////////////////////////////////////


    handles.busPCIReMap_b = icmNewBus( "busPCIReMap", 32);

////////////////////////////////////////////////////////////////////////////////
//                              Bus PCIconfigBus
////////////////////////////////////////////////////////////////////////////////


    handles.PCIconfigBus_b = icmNewBus( "PCIconfigBus", 16);

////////////////////////////////////////////////////////////////////////////////
//                                Bus PCIackBus
////////////////////////////////////////////////////////////////////////////////


    handles.PCIackBus_b = icmNewBus( "PCIackBus", 1);

////////////////////////////////////////////////////////////////////////////////
//                               Bus cascadeBus
////////////////////////////////////////////////////////////////////////////////


    handles.cascadeBus_b = icmNewBus( "cascadeBus", 3);

////////////////////////////////////////////////////////////////////////////////
//                                Bus flashBus
////////////////////////////////////////////////////////////////////////////////


    handles.flashBus_b = icmNewBus( "flashBus", 32);

////////////////////////////////////////////////////////////////////////////////
//                              Processor mipsle1
////////////////////////////////////////////////////////////////////////////////


    const char *mipsle1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "mips.ovpworld.org" ,    // vendor
        "processor"         ,    // library
        "mips32"            ,    // name
        0                   ,    // version
        "model"                  // model
    );

    icmAttrListP mipsle1_attrList = icmNewAttrList();
    icmAddStringAttr(mipsle1_attrList, "variant", "24KEf");
    icmAddUns32Attr(mipsle1_attrList, "vectoredinterrupt", 0);
    icmAddUns32Attr(mipsle1_attrList, "config1MMUSizeM1", 63);
    icmAddDoubleAttr(mipsle1_attrList, "mips", 100.000000);
    icmAddStringAttr(mipsle1_attrList, "endian", "little");
    icmNewProcAttrs mipsle1_attrs = ICM_ATTR_SIMEX;


    handles.mipsle1_c = icmNewProcessor(
        "mipsle1"           ,   // name
        0,
        0                   ,   // cpuId
        0x0000              ,  // flags
        32                  ,   // address bits
        mipsle1_path        ,   // model
        0, 
        mipsle1_attrs       ,   // procAttrs
        mipsle1_attrList    ,   // attrlist
        0                   ,   // semihost file
        0
    );


////////////////////////////////////////////////////////////////////////////////
//                                 PSE pciBrD
////////////////////////////////////////////////////////////////////////////////


    const char *pciBrD_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "DynamicBridge"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP pciBrD_attrList = icmNewAttrList();
    icmAddUns64Attr(pciBrD_attrList, "spLoAddress", 0x18000000LL);
    icmAddUns64Attr(pciBrD_attrList, "mpLoAddress", 0LL);
    icmAddUns64Attr(pciBrD_attrList, "portSize", 0x4ffLL);
    icmAddUns32Attr(pciBrD_attrList, "enableBridge", 1);

    handles.pciBrD_p = icmNewPSE(
        "pciBrD"            ,   // name
        pciBrD_path         ,   // model
        pciBrD_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.pciBrD_p, handles.busPCIReMap_b, "mp", 1, 0x0, 0xffffffff);

    icmConnectPSEBus( handles.pciBrD_p, handles.busPCI_b, "sp", 0, 0x0, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                        PSE Core_Board_SDRAM_promInit
////////////////////////////////////////////////////////////////////////////////


    const char *Core_Board_SDRAM_promInit_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "mips.ovpworld.org" ,    // vendor
        "peripheral"        ,    // library
        "SmartLoaderLinux"  ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP Core_Board_SDRAM_promInit_attrList = icmNewAttrList();

    handles.Core_Board_SDRAM_promInit_p = icmNewPSE(
        "Core_Board_SDRAM_promInit",   // name
        Core_Board_SDRAM_promInit_path,   // model
        Core_Board_SDRAM_promInit_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.Core_Board_SDRAM_promInit_p, handles.bus1_b, "mport", 1, 0x0, 0xffffffff);

    icmConnectPSEBus( handles.Core_Board_SDRAM_promInit_p, handles.bus1_b, "idport", 0, 0x1fc00010, 0x1fc00013);

////////////////////////////////////////////////////////////////////////////////
//                               PSE sysControl
////////////////////////////////////////////////////////////////////////////////


    const char *sysControl_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "marvell.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "GT6412x"           ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP sysControl_attrList = icmNewAttrList();

    handles.sysControl_p = icmNewPSE(
        "sysControl"        ,   // name
        sysControl_path     ,   // model
        sysControl_attrList ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.sysControl_p, handles.PCIconfigBus_b, "PCIconfigM", 1, 0x0, 0xffff);

    icmConnectPSEBus( handles.sysControl_p, handles.PCIackBus_b, "PCIackM", 1, 0x0, 0x1);

    icmConnectPSEBus( handles.sysControl_p, handles.bus1_b, "busPort", 0, 0x0, 0x0);

    icmConnectPSEBus( handles.sysControl_p, handles.PCIconfigBus_b, "PCIconfig", 0, 0x0, 0x0);

    icmConnectPSEBus( handles.sysControl_p, handles.PCIconfigBus_b, "PCIconfigS", 0, 0x0, 0xffff);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE PIIX4
////////////////////////////////////////////////////////////////////////////////


    const char *PIIX4_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "intel.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "82371EB"           ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP PIIX4_attrList = icmNewAttrList();
    icmAddUns32Attr(PIIX4_attrList, "PCIslot", 10);

    handles.PIIX4_p = icmNewPSE(
        "PIIX4"             ,   // name
        PIIX4_path          ,   // model
        PIIX4_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.PIIX4_p, handles.PCIconfigBus_b, "PCIconfig", 0, 0x0, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                PSE PIIX4-IDE
////////////////////////////////////////////////////////////////////////////////


    const char *PIIX4_IDE_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "intel.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "PciIDE"            ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP PIIX4_IDE_attrList = icmNewAttrList();
    icmAddUns32Attr(PIIX4_IDE_attrList, "PCIslot", 10);
    icmAddUns32Attr(PIIX4_IDE_attrList, "PCIfunction", 1);

    handles.PIIX4_IDE_p = icmNewPSE(
        "PIIX4-IDE"         ,   // name
        PIIX4_IDE_path      ,   // model
        PIIX4_IDE_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.PIIX4_IDE_p, handles.busPCI_b, "dmaPort", 1, 0x0, 0xffffffff);

    icmConnectPSEBus( handles.PIIX4_IDE_p, handles.PCIconfigBus_b, "PCIconfig", 0, 0x0, 0x0);

    icmConnectPSEBus( handles.PIIX4_IDE_p, handles.busPCI_b, "busPort", 0, 0x0, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE PCI_PM
////////////////////////////////////////////////////////////////////////////////


    const char *PCI_PM_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "intel.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "PciPM"             ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP PCI_PM_attrList = icmNewAttrList();
    icmAddUns32Attr(PCI_PM_attrList, "PCIslot", 10);
    icmAddUns32Attr(PCI_PM_attrList, "PCIfunction", 3);

    handles.PCI_PM_p = icmNewPSE(
        "PCI_PM"            ,   // name
        PCI_PM_path         ,   // model
        PCI_PM_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.PCI_PM_p, handles.PCIconfigBus_b, "PCIconfig", 0, 0x0, 0x0);

    icmConnectPSEBus( handles.PCI_PM_p, handles.busPCI_b, "busPort", 0, 0x0, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE PCI_NET
////////////////////////////////////////////////////////////////////////////////


    const char *PCI_NET_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "amd.ovpworld.org"  ,    // vendor
        "peripheral"        ,    // library
        "79C970"            ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP PCI_NET_attrList = icmNewAttrList();
    icmAddUns32Attr(PCI_NET_attrList, "PCIslot", 11);
    icmAddUns32Attr(PCI_NET_attrList, "PCIfunction", 0);
    icmAddUns32Attr(PCI_NET_attrList, "pollDelay", 1000);

    handles.PCI_NET_p = icmNewPSE(
        "PCI_NET"           ,   // name
        PCI_NET_path        ,   // model
        PCI_NET_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.PCI_NET_p, handles.busPCI_b, "dmaPort", 1, 0x0, 0xffffffff);

    icmConnectPSEBus( handles.PCI_NET_p, handles.PCIconfigBus_b, "PCIconfig", 0, 0x0, 0x0);

    icmConnectPSEBus( handles.PCI_NET_p, handles.busPCI_b, "busPort", 0, 0x0, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                              PSE intCtrlMaster
////////////////////////////////////////////////////////////////////////////////


    const char *intCtrlMaster_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "intel.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "8259A"             ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP intCtrlMaster_attrList = icmNewAttrList();
    icmAddStringAttr(intCtrlMaster_attrList, "spen", "master");

    handles.intCtrlMaster_p = icmNewPSE(
        "intCtrlMaster"     ,   // name
        intCtrlMaster_path  ,   // model
        intCtrlMaster_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.intCtrlMaster_p, handles.cascadeBus_b, "cascade", 1, 0x0, 0x7);

    icmConnectPSEBus( handles.intCtrlMaster_p, handles.busPCIReMap_b, "io", 0, 0x20, 0x21);

    icmConnectPSEBus( handles.intCtrlMaster_p, handles.busPCIReMap_b, "elcr", 0, 0x4d0, 0x4d0);

    icmConnectPSEBus( handles.intCtrlMaster_p, handles.PCIackBus_b, "PCIackS", 0, 0x0, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                              PSE intCtrlSlave
////////////////////////////////////////////////////////////////////////////////


    const char *intCtrlSlave_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "intel.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "8259A"             ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP intCtrlSlave_attrList = icmNewAttrList();
    icmAddStringAttr(intCtrlSlave_attrList, "spen", "slave");

    handles.intCtrlSlave_p = icmNewPSE(
        "intCtrlSlave"      ,   // name
        intCtrlSlave_path   ,   // model
        intCtrlSlave_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.intCtrlSlave_p, handles.busPCIReMap_b, "io", 0, 0xa0, 0xa1);

    icmConnectPSEBus( handles.intCtrlSlave_p, handles.busPCIReMap_b, "elcr", 0, 0x4d1, 0x4d1);

    icmConnectPSEBus( handles.intCtrlSlave_p, handles.cascadeBus_b, "PCIackS", 0, 0x2, 0x2);

////////////////////////////////////////////////////////////////////////////////
//                              PSE _SUPERIO_REG_
////////////////////////////////////////////////////////////////////////////////


    const char *_SUPERIO_REG__path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "SerInt"            ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP _SUPERIO_REG__attrList = icmNewAttrList();

    handles._SUPERIO_REG__p = icmNewPSE(
        "_SUPERIO_REG_"     ,   // name
        _SUPERIO_REG__path  ,   // model
        _SUPERIO_REG__attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles._SUPERIO_REG__p, handles.busPCIReMap_b, "bport1", 0, 0xb0, 0xb3);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE vga
////////////////////////////////////////////////////////////////////////////////


    const char *vga_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "cirrus.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "GD5446"            ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP vga_attrList = icmNewAttrList();
    icmAddUns32Attr(vga_attrList, "scanDelay", 50000);
    icmAddUns32Attr(vga_attrList, "PCIslot", 18);
    icmAddStringAttr(vga_attrList, "title", "Imperas MIPS32 Malta");

    handles.vga_p = icmNewPSE(
        "vga"               ,   // name
        vga_path            ,   // model
        vga_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.vga_p, handles.PCIconfigBus_b, "PCIconfig", 0, 0x0, 0x0);

    icmConnectPSEBus( handles.vga_p, handles.busPCIReMap_b, "config", 0, 0x3b0, 0x3df);

    icmConnectPSEBus( handles.vga_p, handles.busPCI_b, "memory", 0, 0x0, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                               PSE Ps2Control
////////////////////////////////////////////////////////////////////////////////


    const char *Ps2Control_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "intel.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "Ps2Control"        ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP Ps2Control_attrList = icmNewAttrList();
    icmAddUns32Attr(Ps2Control_attrList, "pollPeriod", 50000);
    icmAddUns32Attr(Ps2Control_attrList, "grabDisable", 1);

    handles.Ps2Control_p = icmNewPSE(
        "Ps2Control"        ,   // name
        Ps2Control_path     ,   // model
        Ps2Control_attrList ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.Ps2Control_p, handles.busPCIReMap_b, "config", 0, 0x60, 0x67);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE pit
////////////////////////////////////////////////////////////////////////////////


    const char *pit_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "intel.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "8253"              ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP pit_attrList = icmNewAttrList();

    handles.pit_p = icmNewPSE(
        "pit"               ,   // name
        pit_path            ,   // model
        pit_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.pit_p, handles.busPCIReMap_b, "bport1", 0, 0x40, 0x43);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE rtc
////////////////////////////////////////////////////////////////////////////////


    const char *rtc_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "motorola.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "MC146818"          ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP rtc_attrList = icmNewAttrList();

    handles.rtc_p = icmNewPSE(
        "rtc"               ,   // name
        rtc_path            ,   // model
        rtc_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.rtc_p, handles.busPCIReMap_b, "busPort", 0, 0x70, 0x71);

////////////////////////////////////////////////////////////////////////////////
//                                PSE uartTTY0
////////////////////////////////////////////////////////////////////////////////


    const char *uartTTY0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "national.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "16550"             ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP uartTTY0_attrList = icmNewAttrList();
    icmAddStringAttr(uartTTY0_attrList, "outfile", "uartTTY0.log");
    icmAddUns32Attr(uartTTY0_attrList, "finishOnDisconnect", 1);

    handles.uartTTY0_p = icmNewPSE(
        "uartTTY0"          ,   // name
        uartTTY0_path       ,   // model
        uartTTY0_attrList   ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uartTTY0_p, handles.busPCIReMap_b, "bport1", 0, 0x3f8, 0x3ff);

////////////////////////////////////////////////////////////////////////////////
//                                PSE uartTTY1
////////////////////////////////////////////////////////////////////////////////


    const char *uartTTY1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "national.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "16550"             ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP uartTTY1_attrList = icmNewAttrList();
    icmAddStringAttr(uartTTY1_attrList, "outfile", "uartTTY1.log");
    icmAddUns32Attr(uartTTY1_attrList, "finishOnDisconnect", 1);

    handles.uartTTY1_p = icmNewPSE(
        "uartTTY1"          ,   // name
        uartTTY1_path       ,   // model
        uartTTY1_attrList   ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uartTTY1_p, handles.busPCIReMap_b, "bport1", 0, 0x2f8, 0x2ff);

////////////////////////////////////////////////////////////////////////////////
//                                   PSE fd0
////////////////////////////////////////////////////////////////////////////////


    const char *fd0_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "intel.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "82077AA"           ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP fd0_attrList = icmNewAttrList();

    handles.fd0_p = icmNewPSE(
        "fd0"               ,   // name
        fd0_path            ,   // model
        fd0_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.fd0_p, handles.busPCIReMap_b, "bport1", 0, 0x3f0, 0x3f7);

////////////////////////////////////////////////////////////////////////////////
//                                PSE uartCBUS
////////////////////////////////////////////////////////////////////////////////


    const char *uartCBUS_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "mips.ovpworld.org" ,    // vendor
        "peripheral"        ,    // library
        "16450C"            ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP uartCBUS_attrList = icmNewAttrList();
    icmAddStringAttr(uartCBUS_attrList, "outfile", "uartCBUS.log");

    handles.uartCBUS_p = icmNewPSE(
        "uartCBUS"          ,   // name
        uartCBUS_path       ,   // model
        uartCBUS_attrList   ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uartCBUS_p, handles.bus1_b, "bport1", 0, 0x1f000900, 0x1f00093f);

////////////////////////////////////////////////////////////////////////////////
//                                PSE maltaFpga
////////////////////////////////////////////////////////////////////////////////


    const char *maltaFpga_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "mips.ovpworld.org" ,    // vendor
        "peripheral"        ,    // library
        "MaltaFPGA"         ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP maltaFpga_attrList = icmNewAttrList();
    icmAddUns32Attr(maltaFpga_attrList, "stoponsoftreset", 1);

    handles.maltaFpga_p = icmNewPSE(
        "maltaFpga"         ,   // name
        maltaFpga_path      ,   // model
        maltaFpga_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.maltaFpga_p, handles.bus1_b, "busPort1", 0, 0x1f000000, 0x1f0008ff);

    icmConnectPSEBus( handles.maltaFpga_p, handles.bus1_b, "busPort2", 0, 0x1f000a00, 0x1f000fff);

////////////////////////////////////////////////////////////////////////////////
//                              PSE alphaDisplay
////////////////////////////////////////////////////////////////////////////////


    const char *alphaDisplay_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "ovpworld.org"      ,    // vendor
        0                   ,    // library
        "Alpha2x16Display"  ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP alphaDisplay_attrList = icmNewAttrList();

    handles.alphaDisplay_p = icmNewPSE(
        "alphaDisplay"      ,   // name
        alphaDisplay_path   ,   // model
        alphaDisplay_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.alphaDisplay_p, handles.busPCIReMap_b, "busPort", 0, 0x100, 0x103);

    icmConnectProcessorBusByName( handles.mipsle1_c, "INSTRUCTION", handles.bus1_b );

    icmConnectProcessorBusByName( handles.mipsle1_c, "DATA", handles.bus1_b );

////////////////////////////////////////////////////////////////////////////////
//                           Memory Core_Board_SDRAM
////////////////////////////////////////////////////////////////////////////////

    handles.Core_Board_SDRAM_m = icmNewMemory("Core_Board_SDRAM", 0x7, 0xfffffff);


    icmConnectMemoryToBus( handles.bus1_b, "sp1", handles.Core_Board_SDRAM_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                          Memory Core_Board_SDRAM2
////////////////////////////////////////////////////////////////////////////////

    handles.Core_Board_SDRAM2_m = icmNewMemory("Core_Board_SDRAM2", 0x7, 0x3fffffff);


    icmConnectMemoryToBus( handles.bus1_b, "sp1", handles.Core_Board_SDRAM2_m, 0x20000000);

////////////////////////////////////////////////////////////////////////////////
//                            Memory Monitor_Flash
////////////////////////////////////////////////////////////////////////////////

    handles.Monitor_Flash_m = icmNewMemory("Monitor_Flash", 0x7, 0x3fffff);


    icmConnectMemoryToBus( handles.flashBus_b, "sp1", handles.Monitor_Flash_m, 0x1e000000);

////////////////////////////////////////////////////////////////////////////////
//                             Memory vgaMemRegion
////////////////////////////////////////////////////////////////////////////////

    handles.vgaMemRegion_m = icmNewMemory("vgaMemRegion", 0x5, 0x1ffff);


    icmConnectMemoryToBus( handles.busPCI_b, "sp1", handles.vgaMemRegion_m, 0x100a0000);

////////////////////////////////////////////////////////////////////////////////
//                                Bridge pciBr
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.bus1_b, handles.busPCI_b, "pciBr", "sp1", "mp1", 0x10000000, 0x1bdfffff, 0x10000000);

////////////////////////////////////////////////////////////////////////////////
//                                Bridge pciMBr
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.busPCI_b, handles.bus1_b, "pciMBr", "sp1", "mp1", 0x0, 0xfffffff, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                 Bridge map
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.bus1_b, handles.flashBus_b, "map", "sp1", "mp1", 0x1e000000, 0x1e3fffff, 0x1e000000);

////////////////////////////////////////////////////////////////////////////////
//                                Bridge remap1
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.bus1_b, handles.flashBus_b, "remap1", "sp1", "mp1", 0x1e000000, 0x1e00000f, 0x1fc00000);

////////////////////////////////////////////////////////////////////////////////
//                                Bridge remap2
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.bus1_b, handles.flashBus_b, "remap2", "sp1", "mp1", 0x1e000014, 0x1e3fffff, 0x1fc00014);

////////////////////////////////////////////////////////////////////////////////
//                               Bridge high2low
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.bus1_b, handles.bus1_b, "high2low", "sp1", "mp1", 0x0, 0x7fffffff, 0x80000000);


////////////////////////////////////////////////////////////////////////////////
//                                 CONNECTIONS
////////////////////////////////////////////////////////////////////////////////

    handles.i8259Int_n = icmNewNet("i8259Int" );

    icmConnectProcessorNet( handles.mipsle1_c, handles.i8259Int_n, "hwint0", 0);

    icmConnectPSENet( handles.intCtrlMaster_p, handles.i8259Int_n, "intp", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.intCtl_ir14_n = icmNewNet("intCtl_ir14" );

    icmConnectPSENet( handles.PIIX4_IDE_p, handles.intCtl_ir14_n, "intOut0", 0);

    icmConnectPSENet( handles.intCtrlSlave_p, handles.intCtl_ir14_n, "ir6", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.intCtl_ir15_n = icmNewNet("intCtl_ir15" );

    icmConnectPSENet( handles.PIIX4_IDE_p, handles.intCtl_ir15_n, "intOut1", 0);

    icmConnectPSENet( handles.intCtrlSlave_p, handles.intCtl_ir15_n, "ir7", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.intCtl_ir10_n = icmNewNet("intCtl_ir10" );

    icmConnectPSENet( handles.PCI_NET_p, handles.intCtl_ir10_n, "intOut0", 0);

    icmConnectPSENet( handles.intCtrlSlave_p, handles.intCtl_ir10_n, "ir2", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.intCtl_ir1_n = icmNewNet("intCtl_ir1" );

    icmConnectPSENet( handles.intCtrlMaster_p, handles.intCtl_ir1_n, "ir1", 0);

    icmConnectPSENet( handles.Ps2Control_p, handles.intCtl_ir1_n, "kbdInterrupt", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.intCtl_ir3_n = icmNewNet("intCtl_ir3" );

    icmConnectPSENet( handles.intCtrlMaster_p, handles.intCtl_ir3_n, "ir3", 0);

    icmConnectPSENet( handles.uartTTY1_p, handles.intCtl_ir3_n, "intOut", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.intCtl_ir4_n = icmNewNet("intCtl_ir4" );

    icmConnectPSENet( handles.intCtrlMaster_p, handles.intCtl_ir4_n, "ir4", 0);

    icmConnectPSENet( handles.uartTTY0_p, handles.intCtl_ir4_n, "intOut", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.i8259Cascade_n = icmNewNet("i8259Cascade" );

    icmConnectPSENet( handles.intCtrlMaster_p, handles.i8259Cascade_n, "ir2", 0);

    icmConnectPSENet( handles.intCtrlSlave_p, handles.i8259Cascade_n, "intp", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.intCtl_ir8_n = icmNewNet("intCtl_ir8" );

    icmConnectPSENet( handles.intCtrlSlave_p, handles.intCtl_ir8_n, "ir0", 0);

    icmConnectPSENet( handles.rtc_p, handles.intCtl_ir8_n, "timerInt", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.intCtl_ir12_n = icmNewNet("intCtl_ir12" );

    icmConnectPSENet( handles.intCtrlSlave_p, handles.intCtl_ir12_n, "ir4", 0);

    icmConnectPSENet( handles.Ps2Control_p, handles.intCtl_ir12_n, "mouseInterrupt", 0);
}
