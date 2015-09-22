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

    icmInitAttrs HeteroArmNucleusMIPSLinux_attrs = ICM_INIT_DEFAULT;

    icmInitPlatform(ICM_VERSION, HeteroArmNucleusMIPSLinux_attrs, 0, 0, "HeteroArmNucleusMIPSLinux");


    icmDocNodeP Root1_node = icmDocSectionAdd(0, "Root");
    {
        icmDocNodeP doc2_node = icmDocSectionAdd(Root1_node, "Licensing");
        icmDocTextAdd(doc2_node, "Open Source Apache 2.0");
        icmDocNodeP doc_12_node = icmDocSectionAdd(Root1_node, "Description");
        icmDocTextAdd(doc_12_node, "This is a platform representing a MIPS Malta development board.\n    It provides the peripherals required to boot and run a Linux Operating System.\n    A single MIPS32 architecture processor is instantiated in this platform.\n    This instance could be duplicated to instantiate further processors to easily create an SMP platform.\n    Attributes are provided for configuration of the generic ISA model for a specific processor.\n    The processor model is configured to operate as a MIPS32 4KEc.\n\n    The extension library 'mips32-kernel' has been included in the platform.\n    This library provides interception features for the Linux Kernel. This gives visability of the operation\n    of the kernel without having to rebuild the kernel itself. Attributes are passed to control some of the features.\n    The main SDRAM and Flash memory is modeled using RAM models. Both are initialised in places by the\n    'SmartLoaderLinux'. The SmartLoaderLinux allows ease of use of changing kernel command lines,\n    loading an initial ram disk and creating the boot flash(s). The operation of the SmartloaderLinux is configured\n    using a number of attributes.\n");
    }
    icmSetPlatformStatus(ICM_OVP,ICM_FIX,ICM_VISIBLE);

////////////////////////////////////////////////////////////////////////////////
//                               Bus busmipsMain
////////////////////////////////////////////////////////////////////////////////


    handles.busmipsMain_b = icmNewBus( "busmipsMain", 32);

////////////////////////////////////////////////////////////////////////////////
//                          Bus PCIconfigBusmipsMain
////////////////////////////////////////////////////////////////////////////////


    handles.PCIconfigBusmipsMain_b = icmNewBus( "PCIconfigBusmipsMain", 16);

////////////////////////////////////////////////////////////////////////////////
//                            Bus PCIackBusmipsMain
////////////////////////////////////////////////////////////////////////////////


    handles.PCIackBusmipsMain_b = icmNewBus( "PCIackBusmipsMain", 1);

////////////////////////////////////////////////////////////////////////////////
//                           Bus cascadeBusmipsMain
////////////////////////////////////////////////////////////////////////////////


    handles.cascadeBusmipsMain_b = icmNewBus( "cascadeBusmipsMain", 3);

////////////////////////////////////////////////////////////////////////////////
//                                Bus flashBus
////////////////////////////////////////////////////////////////////////////////


    handles.flashBus_b = icmNewBus( "flashBus", 32);

////////////////////////////////////////////////////////////////////////////////
//                               Bus busarmSub1
////////////////////////////////////////////////////////////////////////////////


    handles.busarmSub1_b = icmNewBus( "busarmSub1", 32);

////////////////////////////////////////////////////////////////////////////////
//                                Bus busShared
////////////////////////////////////////////////////////////////////////////////


    handles.busShared_b = icmNewBus( "busShared", 32);

////////////////////////////////////////////////////////////////////////////////
//                              Processor mipsle1
////////////////////////////////////////////////////////////////////////////////


    const char *mipsle1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "mips.ovpworld.org" ,    // vendor
        0                   ,    // library
        "mips32"            ,    // name
        0                   ,    // version
        "model"                  // model
    );

    icmAttrListP mipsle1_attrList = icmNewAttrList();
    icmAddStringAttr(mipsle1_attrList, "variant", "34Kf");
    icmAddStringAttr(mipsle1_attrList, "vectoredinterrupt", "disable");
    icmAddUns64Attr(mipsle1_attrList, "config1MMUSizeM1", 63LL);
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
//                            Processor armSub1arm1
////////////////////////////////////////////////////////////////////////////////


    const char *armSub1arm1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "arm"               ,    // name
        0                   ,    // version
        "model"                  // model
    );

    icmAttrListP armSub1arm1_attrList = icmNewAttrList();
    icmAddStringAttr(armSub1arm1_attrList, "variant", "ARM920T");
    icmAddStringAttr(armSub1arm1_attrList, "compatibility", "ISA");
    icmAddUns64Attr(armSub1arm1_attrList, "showHiddenRegs", 0LL);
    icmAddDoubleAttr(armSub1arm1_attrList, "mips", 200.000000);
    icmAddStringAttr(armSub1arm1_attrList, "endian", "little");
    icmNewProcAttrs armSub1arm1_attrs = ICM_ATTR_SIMEX;


    handles.armSub1arm1_c = icmNewProcessor(
        "armSub1arm1"       ,   // name
        0,
        1                   ,   // cpuId
        0x0000              ,  // flags
        32                  ,   // address bits
        armSub1arm1_path    ,   // model
        0, 
        armSub1arm1_attrs   ,   // procAttrs
        armSub1arm1_attrList,   // attrlist
        0                   ,   // semihost file
        0
    );


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
    icmAddStringAttr(Core_Board_SDRAM_promInit_attrList, "kernel", "mips.vmlinux");
    icmAddUns64Attr(Core_Board_SDRAM_promInit_attrList, "boardid", 0x00000420LL);
    icmAddStringAttr(Core_Board_SDRAM_promInit_attrList, "initrd", "mips.initrd.gz");
    icmAddStringAttr(Core_Board_SDRAM_promInit_attrList, "command", "console=tty0");

    handles.Core_Board_SDRAM_promInit_p = icmNewPSE(
        "Core_Board_SDRAM_promInit",   // name
        Core_Board_SDRAM_promInit_path,   // model
        Core_Board_SDRAM_promInit_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.Core_Board_SDRAM_promInit_p, handles.busmipsMain_b, "mport", 1, 0x0, 0x7fffffff);

    icmConnectPSEBus( handles.Core_Board_SDRAM_promInit_p, handles.busmipsMain_b, "idport", 0, 0x1fc00010, 0x1fc00013);

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

    icmConnectPSEBus( handles.sysControl_p, handles.PCIconfigBusmipsMain_b, "PCIconfigM", 1, 0x0, 0xffff);

    icmConnectPSEBus( handles.sysControl_p, handles.PCIackBusmipsMain_b, "PCIackM", 1, 0x0, 0x1);

    icmConnectPSEBus( handles.sysControl_p, handles.busmipsMain_b, "busPort", 0, 0x0, 0x0);

    icmConnectPSEBus( handles.sysControl_p, handles.PCIconfigBusmipsMain_b, "PCIconfig", 0, 0x0, 0x0);

    icmConnectPSEBus( handles.sysControl_p, handles.PCIconfigBusmipsMain_b, "PCIconfigS", 0, 0x0, 0xffff);

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
    icmAddUns64Attr(PIIX4_attrList, "PCIslot", 10LL);

    handles.PIIX4_p = icmNewPSE(
        "PIIX4"             ,   // name
        PIIX4_path          ,   // model
        PIIX4_attrList      ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.PIIX4_p, handles.PCIconfigBusmipsMain_b, "PCIconfig", 0, 0x0, 0x0);

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
    icmAddUns64Attr(PIIX4_IDE_attrList, "PCIslot", 10LL);
    icmAddUns64Attr(PIIX4_IDE_attrList, "PCIfunction", 1LL);
    icmAddStringAttr(PIIX4_IDE_attrList, "Drive0Name", "mipsel_hda");
    icmAddStringAttr(PIIX4_IDE_attrList, "Drive1Name", "mipsel_hdb");
    icmAddStringAttr(PIIX4_IDE_attrList, "Drive2Name", "mipsel_cd");

    handles.PIIX4_IDE_p = icmNewPSE(
        "PIIX4-IDE"         ,   // name
        PIIX4_IDE_path      ,   // model
        PIIX4_IDE_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.PIIX4_IDE_p, handles.busmipsMain_b, "dmaPort", 1, 0x0, 0xffffffff);

    icmConnectPSEBus( handles.PIIX4_IDE_p, handles.PCIconfigBusmipsMain_b, "PCIconfig", 0, 0x0, 0x0);

    icmConnectPSEBus( handles.PIIX4_IDE_p, handles.busmipsMain_b, "busPort", 0, 0x0, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                 PSE PCI_USB
////////////////////////////////////////////////////////////////////////////////


    const char *PCI_USB_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "intel.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "PciUSB"            ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP PCI_USB_attrList = icmNewAttrList();
    icmAddUns64Attr(PCI_USB_attrList, "PCIslot", 10LL);
    icmAddUns64Attr(PCI_USB_attrList, "PCIfunction", 2LL);

    handles.PCI_USB_p = icmNewPSE(
        "PCI_USB"           ,   // name
        PCI_USB_path        ,   // model
        PCI_USB_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.PCI_USB_p, handles.PCIconfigBusmipsMain_b, "PCIconfig", 0, 0x0, 0x0);

    icmConnectPSEBus( handles.PCI_USB_p, handles.busmipsMain_b, "busPort", 0, 0x0, 0x0);

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
    icmAddUns64Attr(PCI_PM_attrList, "PCIslot", 10LL);
    icmAddUns64Attr(PCI_PM_attrList, "PCIfunction", 3LL);

    handles.PCI_PM_p = icmNewPSE(
        "PCI_PM"            ,   // name
        PCI_PM_path         ,   // model
        PCI_PM_attrList     ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.PCI_PM_p, handles.PCIconfigBusmipsMain_b, "PCIconfig", 0, 0x0, 0x0);

    icmConnectPSEBus( handles.PCI_PM_p, handles.busmipsMain_b, "busPort", 0, 0x0, 0x0);

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
    icmAddUns64Attr(PCI_NET_attrList, "PCIslot", 11LL);
    icmAddUns64Attr(PCI_NET_attrList, "PCIfunction", 0LL);
    icmAddUns64Attr(PCI_NET_attrList, "pollDelay", 1000LL);

    handles.PCI_NET_p = icmNewPSE(
        "PCI_NET"           ,   // name
        PCI_NET_path        ,   // model
        PCI_NET_attrList    ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.PCI_NET_p, handles.busmipsMain_b, "dmaPort", 1, 0x0, 0xffffffff);

    icmConnectPSEBus( handles.PCI_NET_p, handles.PCIconfigBusmipsMain_b, "PCIconfig", 0, 0x0, 0x0);

    icmConnectPSEBus( handles.PCI_NET_p, handles.busmipsMain_b, "busPort", 0, 0x0, 0x0);

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

    icmConnectPSEBus( handles.intCtrlMaster_p, handles.cascadeBusmipsMain_b, "cascade", 1, 0x0, 0x7);

    icmConnectPSEBus( handles.intCtrlMaster_p, handles.busmipsMain_b, "io", 0, 0x18000020, 0x18000021);

    icmConnectPSEBus( handles.intCtrlMaster_p, handles.busmipsMain_b, "elcr", 0, 0x180004d0, 0x180004d0);

    icmConnectPSEBus( handles.intCtrlMaster_p, handles.PCIackBusmipsMain_b, "PCIackS", 0, 0x0, 0x0);

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

    icmConnectPSEBus( handles.intCtrlSlave_p, handles.busmipsMain_b, "io", 0, 0x180000a0, 0x180000a1);

    icmConnectPSEBus( handles.intCtrlSlave_p, handles.busmipsMain_b, "elcr", 0, 0x180004d1, 0x180004d1);

    icmConnectPSEBus( handles.intCtrlSlave_p, handles.cascadeBusmipsMain_b, "PCIackS", 0, 0x2, 0x2);

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
    icmAddUns64Attr(vga_attrList, "scanDelay", 50000LL);
    icmAddUns64Attr(vga_attrList, "PCIslot", 18LL);
    icmAddStringAttr(vga_attrList, "title", "Imperas MIPS32 Malta");

    handles.vga_p = icmNewPSE(
        "vga"               ,   // name
        vga_path            ,   // model
        vga_attrList        ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.vga_p, handles.PCIconfigBusmipsMain_b, "PCIconfig", 0, 0x0, 0x0);

    icmConnectPSEBus( handles.vga_p, handles.busmipsMain_b, "config", 0, 0x180003b0, 0x180003df);

    icmConnectPSEBus( handles.vga_p, handles.busmipsMain_b, "memory", 0, 0x0, 0x0);

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
    icmAddUns64Attr(Ps2Control_attrList, "pollPeriod", 5000LL);
    icmAddUns64Attr(Ps2Control_attrList, "grabDisable", 1LL);

    handles.Ps2Control_p = icmNewPSE(
        "Ps2Control"        ,   // name
        Ps2Control_path     ,   // model
        Ps2Control_attrList ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.Ps2Control_p, handles.busmipsMain_b, "config", 0, 0x18000060, 0x18000067);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE mpit
////////////////////////////////////////////////////////////////////////////////


    const char *mpit_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "intel.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "8253"              ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP mpit_attrList = icmNewAttrList();

    handles.mpit_p = icmNewPSE(
        "mpit"              ,   // name
        mpit_path           ,   // model
        mpit_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.mpit_p, handles.busmipsMain_b, "bport1", 0, 0x18000040, 0x18000043);

////////////////////////////////////////////////////////////////////////////////
//                                  PSE mrtc
////////////////////////////////////////////////////////////////////////////////


    const char *mrtc_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "motorola.ovpworld.org",    // vendor
        "peripheral"        ,    // library
        "MC146818"          ,    // name
        "1.0"               ,    // version
        "pse"                    // model
    );

    icmAttrListP mrtc_attrList = icmNewAttrList();

    handles.mrtc_p = icmNewPSE(
        "mrtc"              ,   // name
        mrtc_path           ,   // model
        mrtc_attrList       ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.mrtc_p, handles.busmipsMain_b, "busPort", 0, 0x18000070, 0x18000071);

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

    handles.uartTTY0_p = icmNewPSE(
        "uartTTY0"          ,   // name
        uartTTY0_path       ,   // model
        uartTTY0_attrList   ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uartTTY0_p, handles.busmipsMain_b, "bport1", 0, 0x180003f8, 0x180003ff);

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

    handles.uartTTY1_p = icmNewPSE(
        "uartTTY1"          ,   // name
        uartTTY1_path       ,   // model
        uartTTY1_attrList   ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uartTTY1_p, handles.busmipsMain_b, "bport1", 0, 0x180002f8, 0x180002ff);

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

    handles.uartCBUS_p = icmNewPSE(
        "uartCBUS"          ,   // name
        uartCBUS_path       ,   // model
        uartCBUS_attrList   ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.uartCBUS_p, handles.busmipsMain_b, "bport1", 0, 0x1f000900, 0x1f00093f);

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

    icmConnectPSEBus( handles.fd0_p, handles.busmipsMain_b, "bport1", 0, 0x180003f0, 0x180003f7);

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
    icmAddUns64Attr(maltaFpga_attrList, "stoponsoftreset", 1LL);

    handles.maltaFpga_p = icmNewPSE(
        "maltaFpga"         ,   // name
        maltaFpga_path      ,   // model
        maltaFpga_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.maltaFpga_p, handles.busmipsMain_b, "busPort1", 0, 0x1f000000, 0x1f0008ff);

    icmConnectPSEBus( handles.maltaFpga_p, handles.busmipsMain_b, "busPort2", 0, 0x1f000a00, 0x1f000fff);

////////////////////////////////////////////////////////////////////////////////
//                                PSE armSub1cm
////////////////////////////////////////////////////////////////////////////////


    const char *armSub1cm_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "CoreModule9x6"     ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP armSub1cm_attrList = icmNewAttrList();

    handles.armSub1cm_p = icmNewPSE(
        "armSub1cm"         ,   // name
        armSub1cm_path      ,   // model
        armSub1cm_attrList  ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.armSub1cm_p, handles.busarmSub1_b, "bport1", 0, 0x10000000, 0x10000fff);

////////////////////////////////////////////////////////////////////////////////
//                               PSE armSub1pic1
////////////////////////////////////////////////////////////////////////////////


    const char *armSub1pic1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "IntICP"            ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP armSub1pic1_attrList = icmNewAttrList();

    handles.armSub1pic1_p = icmNewPSE(
        "armSub1pic1"       ,   // name
        armSub1pic1_path    ,   // model
        armSub1pic1_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.armSub1pic1_p, handles.busarmSub1_b, "bport1", 0, 0x14000000, 0x14000fff);

////////////////////////////////////////////////////////////////////////////////
//                               PSE armSub1pic2
////////////////////////////////////////////////////////////////////////////////


    const char *armSub1pic2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "IntICP"            ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP armSub1pic2_attrList = icmNewAttrList();

    handles.armSub1pic2_p = icmNewPSE(
        "armSub1pic2"       ,   // name
        armSub1pic2_path    ,   // model
        armSub1pic2_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.armSub1pic2_p, handles.busarmSub1_b, "bport1", 0, 0xca000000, 0xca000fff);

////////////////////////////////////////////////////////////////////////////////
//                               PSE armSub1pit
////////////////////////////////////////////////////////////////////////////////


    const char *armSub1pit_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "IcpCounterTimer"   ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP armSub1pit_attrList = icmNewAttrList();

    handles.armSub1pit_p = icmNewPSE(
        "armSub1pit"        ,   // name
        armSub1pit_path     ,   // model
        armSub1pit_attrList ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.armSub1pit_p, handles.busarmSub1_b, "bport1", 0, 0x13000000, 0x13000fff);

////////////////////////////////////////////////////////////////////////////////
//                               PSE armSub1icp
////////////////////////////////////////////////////////////////////////////////


    const char *armSub1icp_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "IcpControl"        ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP armSub1icp_attrList = icmNewAttrList();

    handles.armSub1icp_p = icmNewPSE(
        "armSub1icp"        ,   // name
        armSub1icp_path     ,   // model
        armSub1icp_attrList ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.armSub1icp_p, handles.busarmSub1_b, "bport1", 0, 0xcb000000, 0xcb00000f);

////////////////////////////////////////////////////////////////////////////////
//                               PSE armSub1ld1
////////////////////////////////////////////////////////////////////////////////


    const char *armSub1ld1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "DebugLedAndDipSwitch",    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP armSub1ld1_attrList = icmNewAttrList();

    handles.armSub1ld1_p = icmNewPSE(
        "armSub1ld1"        ,   // name
        armSub1ld1_path     ,   // model
        armSub1ld1_attrList ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.armSub1ld1_p, handles.busarmSub1_b, "bport1", 0, 0x1a000000, 0x1a000fff);

////////////////////////////////////////////////////////////////////////////////
//                               PSE armSub1kb1
////////////////////////////////////////////////////////////////////////////////


    const char *armSub1kb1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "KbPL050"           ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP armSub1kb1_attrList = icmNewAttrList();
    icmAddUns64Attr(armSub1kb1_attrList, "isMouse", 0LL);
    icmAddUns64Attr(armSub1kb1_attrList, "grabDisable", 0LL);

    handles.armSub1kb1_p = icmNewPSE(
        "armSub1kb1"        ,   // name
        armSub1kb1_path     ,   // model
        armSub1kb1_attrList ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.armSub1kb1_p, handles.busarmSub1_b, "bport1", 0, 0x18000000, 0x18000fff);

////////////////////////////////////////////////////////////////////////////////
//                               PSE armSub1ms1
////////////////////////////////////////////////////////////////////////////////


    const char *armSub1ms1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "KbPL050"           ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP armSub1ms1_attrList = icmNewAttrList();
    icmAddUns64Attr(armSub1ms1_attrList, "isMouse", 1LL);
    icmAddUns64Attr(armSub1ms1_attrList, "grabDisable", 1LL);

    handles.armSub1ms1_p = icmNewPSE(
        "armSub1ms1"        ,   // name
        armSub1ms1_path     ,   // model
        armSub1ms1_attrList ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.armSub1ms1_p, handles.busarmSub1_b, "bport1", 0, 0x19000000, 0x19000fff);

////////////////////////////////////////////////////////////////////////////////
//                               PSE armSub1rtc
////////////////////////////////////////////////////////////////////////////////


    const char *armSub1rtc_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "RtcPL031"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP armSub1rtc_attrList = icmNewAttrList();

    handles.armSub1rtc_p = icmNewPSE(
        "armSub1rtc"        ,   // name
        armSub1rtc_path     ,   // model
        armSub1rtc_attrList ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.armSub1rtc_p, handles.busarmSub1_b, "bport1", 0, 0x15000000, 0x15000fff);

////////////////////////////////////////////////////////////////////////////////
//                              PSE armSub1uart1
////////////////////////////////////////////////////////////////////////////////


    const char *armSub1uart1_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP armSub1uart1_attrList = icmNewAttrList();
    icmAddStringAttr(armSub1uart1_attrList, "variant", "ARM");
    icmAddStringAttr(armSub1uart1_attrList, "outfile", "uart1.log");
    icmAddUns64Attr(armSub1uart1_attrList, "finishOnDisconnect", 1LL);

    handles.armSub1uart1_p = icmNewPSE(
        "armSub1uart1"      ,   // name
        armSub1uart1_path   ,   // model
        armSub1uart1_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.armSub1uart1_p, handles.busarmSub1_b, "bport1", 0, 0x16000000, 0x16000fff);

////////////////////////////////////////////////////////////////////////////////
//                              PSE armSub1uart2
////////////////////////////////////////////////////////////////////////////////


    const char *armSub1uart2_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "UartPL011"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP armSub1uart2_attrList = icmNewAttrList();
    icmAddStringAttr(armSub1uart2_attrList, "variant", "ARM");
    icmAddUns64Attr(armSub1uart2_attrList, "finishOnDisconnect", 1LL);

    handles.armSub1uart2_p = icmNewPSE(
        "armSub1uart2"      ,   // name
        armSub1uart2_path   ,   // model
        armSub1uart2_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.armSub1uart2_p, handles.busarmSub1_b, "bport1", 0, 0x17000000, 0x17000fff);

////////////////////////////////////////////////////////////////////////////////
//                               PSE armSub1mmci
////////////////////////////////////////////////////////////////////////////////


    const char *armSub1mmci_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "MmciPL181"         ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP armSub1mmci_attrList = icmNewAttrList();

    handles.armSub1mmci_p = icmNewPSE(
        "armSub1mmci"       ,   // name
        armSub1mmci_path    ,   // model
        armSub1mmci_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.armSub1mmci_p, handles.busarmSub1_b, "bport1", 0, 0x1c000000, 0x1c000fff);

////////////////////////////////////////////////////////////////////////////////
//                               PSE armSub1lcd
////////////////////////////////////////////////////////////////////////////////


    const char *armSub1lcd_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "LcdPL110"          ,    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP armSub1lcd_attrList = icmNewAttrList();
    icmAddUns64Attr(armSub1lcd_attrList, "noGraphics", 1LL);

    handles.armSub1lcd_p = icmNewPSE(
        "armSub1lcd"        ,   // name
        armSub1lcd_path     ,   // model
        armSub1lcd_attrList ,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.armSub1lcd_p, handles.busarmSub1_b, "bport1", 0, 0xc0000000, 0xc0000fff);

    icmConnectPSEBus( handles.armSub1lcd_p, handles.busarmSub1_b, "memory", 0, 0x0, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                           PSE armSub1smartLoader
////////////////////////////////////////////////////////////////////////////////


    const char *armSub1smartLoader_path = icmGetVlnvString(
        0                   ,    // path (0 if from the product directory)
        "arm.ovpworld.org"  ,    // vendor
        0                   ,    // library
        "SmartLoaderArmLinux",    // name
        0                   ,    // version
        "pse"                    // model
    );

    icmAttrListP armSub1smartLoader_attrList = icmNewAttrList();
    icmAddUns64Attr(armSub1smartLoader_attrList, "disable", 1LL);

    handles.armSub1smartLoader_p = icmNewPSE(
        "armSub1smartLoader",   // name
        armSub1smartLoader_path,   // model
        armSub1smartLoader_attrList,   // attrlist
        0,       // unused
        0        // unused
    );

    icmConnectPSEBus( handles.armSub1smartLoader_p, handles.busarmSub1_b, "mport", 1, 0x0, 0xffffffff);

    icmConnectProcessorBusByName( handles.mipsle1_c, "INSTRUCTION", handles.busmipsMain_b );

    icmConnectProcessorBusByName( handles.mipsle1_c, "DATA", handles.busmipsMain_b );

    icmConnectProcessorBusByName( handles.armSub1arm1_c, "INSTRUCTION", handles.busarmSub1_b );

    icmConnectProcessorBusByName( handles.armSub1arm1_c, "DATA", handles.busarmSub1_b );

////////////////////////////////////////////////////////////////////////////////
//                           Memory Core_Board_SDRAM
////////////////////////////////////////////////////////////////////////////////

    handles.Core_Board_SDRAM_m = icmNewMemory("Core_Board_SDRAM", 0x7, 0x7ffffff);


    icmConnectMemoryToBus( handles.busmipsMain_b, "sp1", handles.Core_Board_SDRAM_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                            Memory Monitor_Flash
////////////////////////////////////////////////////////////////////////////////

    handles.Monitor_Flash_m = icmNewMemory("Monitor_Flash", 0x7, 0x3fffff);


    icmConnectMemoryToBus( handles.flashBus_b, "sp1", handles.Monitor_Flash_m, 0x1e000000);

////////////////////////////////////////////////////////////////////////////////
//                             Memory armSub1ram1
////////////////////////////////////////////////////////////////////////////////

    handles.armSub1ram1_m = icmNewMemory("armSub1ram1", 0x7, 0x7ffffff);


    icmConnectMemoryToBus( handles.busarmSub1_b, "sp1", handles.armSub1ram1_m, 0x80000000);

////////////////////////////////////////////////////////////////////////////////
//                           Memory armSub1ambaDummy
////////////////////////////////////////////////////////////////////////////////

    handles.armSub1ambaDummy_m = icmNewMemory("armSub1ambaDummy", 0x7, 0xfff);


    icmConnectMemoryToBus( handles.busarmSub1_b, "sp1", handles.armSub1ambaDummy_m, 0x1d000000);

////////////////////////////////////////////////////////////////////////////////
//                              Memory sharedRAM
////////////////////////////////////////////////////////////////////////////////

    handles.sharedRAM_m = icmNewMemory("sharedRAM", 0x7, 0xffff);


    icmConnectMemoryToBus( handles.busShared_b, "sp1", handles.sharedRAM_m, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                                 Bridge map
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.busmipsMain_b, handles.flashBus_b, "map", "sp1", "mp1", 0x1e000000, 0x1e3fffff, 0x1e000000);

////////////////////////////////////////////////////////////////////////////////
//                                Bridge remap1
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.busmipsMain_b, handles.flashBus_b, "remap1", "sp1", "mp1", 0x1e000000, 0x1e00000f, 0x1fc00000);

////////////////////////////////////////////////////////////////////////////////
//                                Bridge remap2
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.busmipsMain_b, handles.flashBus_b, "remap2", "sp1", "mp1", 0x1e000014, 0x1e3fffff, 0x1fc00014);

////////////////////////////////////////////////////////////////////////////////
//                          Bridge armSub1ram1Bridge
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.busarmSub1_b, handles.busarmSub1_b, "armSub1ram1Bridge", "sp", "mp", 0x80000000, 0x87ffffff, 0x0);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge busBridgeM1
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.busmipsMain_b, handles.busShared_b, "busBridgeM1", "sp1", "mp1", 0x0, 0xffff, 0x8000000);

////////////////////////////////////////////////////////////////////////////////
//                             Bridge busBridgeA1
////////////////////////////////////////////////////////////////////////////////


    icmNewBusBridge(handles.busarmSub1_b, handles.busShared_b, "busBridgeA1", "sp1", "mp1", 0x0, 0xffff, 0xa000000);

    if(!icmLoadProcessorMemory(handles.mipsle1_c, "mips.vmlinux", 0, 0, 0)){
        icmPrintf("%s", icmLastMessage());
        icmTerminate();
        icmExitSimulation(1);
    }

    if(!icmLoadProcessorMemory(handles.armSub1arm1_c, "arm.plus_demo.out", 0, 0, 0)){
        icmPrintf("%s", icmLastMessage());
        icmTerminate();
        icmExitSimulation(1);
    }


////////////////////////////////////////////////////////////////////////////////
//                                 CONNECTIONS
////////////////////////////////////////////////////////////////////////////////

    handles.i8259Int_n = icmNewNet("i8259Int" );

    icmConnectProcessorNet( handles.mipsle1_c, handles.i8259Int_n, "hwint0", 0);

    icmConnectPSENet( handles.intCtrlMaster_p, handles.i8259Int_n, "intp", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.armSub1irq_n = icmNewNet("armSub1irq" );

    icmConnectProcessorNet( handles.armSub1arm1_c, handles.armSub1irq_n, "irq", 0);

    icmConnectPSENet( handles.armSub1pic1_p, handles.armSub1irq_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.armSub1fiq_n = icmNewNet("armSub1fiq" );

    icmConnectProcessorNet( handles.armSub1arm1_c, handles.armSub1fiq_n, "fiq", 0);

    icmConnectPSENet( handles.armSub1pic1_p, handles.armSub1fiq_n, "fiq", 0);

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

    icmConnectPSENet( handles.uartCBUS_p, handles.intCtl_ir3_n, "intOut", 0);

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

    icmConnectPSENet( handles.mrtc_p, handles.intCtl_ir8_n, "timerInt", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.intCtl_ir12_n = icmNewNet("intCtl_ir12" );

    icmConnectPSENet( handles.intCtrlSlave_p, handles.intCtl_ir12_n, "ir4", 0);

    icmConnectPSENet( handles.Ps2Control_p, handles.intCtl_ir12_n, "mouseInterrupt", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.armSub1ir1_n = icmNewNet("armSub1ir1" );

    icmConnectPSENet( handles.armSub1pic1_p, handles.armSub1ir1_n, "ir1", 0);

    icmConnectPSENet( handles.armSub1uart1_p, handles.armSub1ir1_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.armSub1ir2_n = icmNewNet("armSub1ir2" );

    icmConnectPSENet( handles.armSub1pic1_p, handles.armSub1ir2_n, "ir2", 0);

    icmConnectPSENet( handles.armSub1uart2_p, handles.armSub1ir2_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.armSub1ir3_n = icmNewNet("armSub1ir3" );

    icmConnectPSENet( handles.armSub1pic1_p, handles.armSub1ir3_n, "ir3", 0);

    icmConnectPSENet( handles.armSub1kb1_p, handles.armSub1ir3_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.armSub1ir4_n = icmNewNet("armSub1ir4" );

    icmConnectPSENet( handles.armSub1pic1_p, handles.armSub1ir4_n, "ir4", 0);

    icmConnectPSENet( handles.armSub1ms1_p, handles.armSub1ir4_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.armSub1ir5_n = icmNewNet("armSub1ir5" );

    icmConnectPSENet( handles.armSub1pic1_p, handles.armSub1ir5_n, "ir5", 0);

    icmConnectPSENet( handles.armSub1pit_p, handles.armSub1ir5_n, "irq0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.armSub1ir6_n = icmNewNet("armSub1ir6" );

    icmConnectPSENet( handles.armSub1pic1_p, handles.armSub1ir6_n, "ir6", 0);

    icmConnectPSENet( handles.armSub1pit_p, handles.armSub1ir6_n, "irq1", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.armSub1ir7_n = icmNewNet("armSub1ir7" );

    icmConnectPSENet( handles.armSub1pic1_p, handles.armSub1ir7_n, "ir7", 0);

    icmConnectPSENet( handles.armSub1pit_p, handles.armSub1ir7_n, "irq2", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.armSub1ir8_n = icmNewNet("armSub1ir8" );

    icmConnectPSENet( handles.armSub1pic1_p, handles.armSub1ir8_n, "ir8", 0);

    icmConnectPSENet( handles.armSub1rtc_p, handles.armSub1ir8_n, "irq", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.armSub1ir23_n = icmNewNet("armSub1ir23" );

    icmConnectPSENet( handles.armSub1pic1_p, handles.armSub1ir23_n, "ir23", 0);

    icmConnectPSENet( handles.armSub1mmci_p, handles.armSub1ir23_n, "irq0", 0);

////////////////////////////////////////////////////////////////////////////////
    handles.armSub1ir24_n = icmNewNet("armSub1ir24" );

    icmConnectPSENet( handles.armSub1pic1_p, handles.armSub1ir24_n, "ir24", 0);

    icmConnectPSENet( handles.armSub1mmci_p, handles.armSub1ir24_n, "irq1", 0);
}
