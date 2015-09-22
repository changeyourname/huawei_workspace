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

// MODEL IO:
//    Slave Port INTCP0
//    Net output  RESET;
//    Net output  NMI0;
//    Net output  NMI1;
//    Net output  NMI2;
//    Net output  INTP;
//    Net input  INTACK;
//    Net input  MIRETI;
//    Net input  IRESET;
//    Net input  NMI_00;
//    Net input  NMI_01;
//    Net input  NMI_02;
//    Net input  NMI_03;
//    Net input  NMI_04;
//    Net input  NMI_05;
//    Net input  NMI_06;
//    Net input  NMI_07;
//    Net input  NMI_08;
//    Net input  NMI_09;
//    Net input  NMI_10;
//    Net input  NMI_11;
//    Net input  NMI_12;
//    Net input  NMI_13;
//    Net input  NMI_14;
//    Net input  NMI_15;
//    Net input  NMI_16;
//    Net input  NMI_17;
//    Net input  NMI_18;
//    Net input  NMI_19;
//    Net input  NMI_20;
//    Net input  NMI_21;
//    Net input  NMI_22;
//    Net input  NMI_23;
//    Net input  NMI_24;
//    Net input  NMI_25;
//    Net input  NMI_26;
//    Net input  NMI_27;
//    Net input  NMI_28;
//    Net input  NMI_29;
//    Net input  NMI_30;
//    Net input  NMI_31;
//    Net input  NMI_32;
//    Net input  NMI_33;
//    Net input  NMI_34;
//    Net input  NMI_35;
//    Net input  NMI_36;
//    Net input  NMI_37;
//    Net input  NMI_38;
//    Net input  NMI_39;
//    Net input  NMI_40;
//    Net input  NMI_41;
//    Net input  NMI_42;
//    Net input  NMI_43;
//    Net input  NMI_44;
//    Net input  NMI_45;
//    Net input  NMI_46;
//    Net input  NMI_47;
//    Net input  NMI_48;
//    Net input  NMI_49;
//    Net input  NMI_50;
//    Net input  NMI_51;
//    Net input  NMI_52;
//    Net input  NMI_53;
//    Net input  NMI_54;
//    Net input  NMI_55;
//    Net input  NMI_56;
//    Net input  NMI_57;
//    Net input  NMI_58;
//    Net input  NMI_59;
//    Net input  NMI_60;
//    Net input  NMI_61;
//    Net input  NMI_62;
//    Net input  NMI_63;
//    Net input  INT_00;
//    Net input  INT_01;
//    Net input  INT_02;
//    Net input  INT_03;
//    Net input  INT_04;
//    Net input  INT_05;
//    Net input  INT_06;
//    Net input  INT_07;
//    Net input  INT_08;
//    Net input  INT_09;
//    Net input  INT_10;
//    Net input  INT_11;
//    Net input  INT_12;
//    Net input  INT_13;
//    Net input  INT_14;
//    Net input  INT_15;
//    Net input  INT_16;
//    Net input  INT_17;
//    Net input  INT_18;
//    Net input  INT_19;
//    Net input  INT_20;
//    Net input  INT_21;
//    Net input  INT_22;
//    Net input  INT_23;
//    Net input  INT_24;
//    Net input  INT_25;
//    Net input  INT_26;
//    Net input  INT_27;
//    Net input  INT_28;
//    Net input  INT_29;
//    Net input  INT_30;
//    Net input  INT_31;
//    Net input  INT_32;
//    Net input  INT_33;
//    Net input  INT_34;
//    Net input  INT_35;
//    Net input  INT_36;
//    Net input  INT_37;
//    Net input  INT_38;
//    Net input  INT_39;
//    Net input  INT_40;
//    Net input  INT_41;
//    Net input  INT_42;
//    Net input  INT_43;
//    Net input  INT_44;
//    Net input  INT_45;
//    Net input  INT_46;
//    Net input  INT_47;
//    Net input  INT_48;
//    Net input  INT_49;
//    Net input  INT_50;
//    Net input  INT_51;
//    Net input  INT_52;
//    Net input  INT_53;
//    Net input  INT_54;
//    Net input  INT_55;
//    Net input  INT_56;
//    Net input  INT_57;
//    Net input  INT_58;
//    Net input  INT_59;
//    Net input  INT_60;
//    Net input  INT_61;
//    Net input  INT_62;
//    Net input  INT_63;
//    Net input  INT_64;
//    Net input  INT_65;
//    Net input  INT_66;
//    Net input  INT_67;
//    Net input  INT_68;
//    Net input  INT_69;
//    Net input  INT_70;
//    Net input  INT_71;
//    Net input  INT_72;
//    Net input  INT_73;
//    Net input  INT_74;
//    Net input  INT_75;
//    Net input  INT_76;
//    Net input  INT_77;
//    Net input  INT_78;
//    Net input  INT_79;
//    Net input  INT_80;
//    Net input  INT_81;
//    Net input  INT_82;
//    Net input  INT_83;
//    Net input  INT_84;
//    Net input  INT_85;
//    Net input  INT_86;
//    Net input  INT_87;
//    Net input  INT_88;
//    Net input  INT_89;
//    Net input  INT_90;
//    Net input  INT_91;
//    Net input  INT_92;
//    Net input  INT_93;
//    Net input  INT_94;
//    Net input  INT_95;
//    Net input  INT_96;
//    Net input  INT_97;
//    Net input  INT_98;
//    Net input  INT_99;
//    Net input  INT_100;
//    Net input  INT_101;
//    Net input  INT_102;
//    Net input  INT_103;
//    Net input  INT_104;
//    Net input  INT_105;
//    Net input  INT_106;
//    Net input  INT_107;
//    Net input  INT_108;
//    Net input  INT_109;
//    Net input  INT_110;
//    Net input  INT_111;
//    Net input  INT_112;
//    Net input  INT_113;
//    Net input  INT_114;
//    Net input  INT_115;
//    Net input  INT_116;

#ifndef RENESAS_OVPWORLD_ORG_PERIPHERAL_INTC__1_0
#define RENESAS_OVPWORLD_ORG_PERIPHERAL_INTC__1_0
#include "ovpworld.org/modelSupport/tlmPeripheral/1.0/tlm2.0/tlmPeripheral.hpp"
using namespace sc_core;

class intc : public icmPeripheral
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "renesas.ovpworld.org", "peripheral", "intc", "1.0", "pse");
    }

  public:
    icmSlavePort        INTCP0;
    icmOutputNetPort RESET;
    icmOutputNetPort NMI0;
    icmOutputNetPort NMI1;
    icmOutputNetPort NMI2;
    icmOutputNetPort INTP;
    icmInputNetPort INTACK;
    icmInputNetPort MIRETI;
    icmInputNetPort IRESET;
    icmInputNetPort NMI_00;
    icmInputNetPort NMI_01;
    icmInputNetPort NMI_02;
    icmInputNetPort NMI_03;
    icmInputNetPort NMI_04;
    icmInputNetPort NMI_05;
    icmInputNetPort NMI_06;
    icmInputNetPort NMI_07;
    icmInputNetPort NMI_08;
    icmInputNetPort NMI_09;
    icmInputNetPort NMI_10;
    icmInputNetPort NMI_11;
    icmInputNetPort NMI_12;
    icmInputNetPort NMI_13;
    icmInputNetPort NMI_14;
    icmInputNetPort NMI_15;
    icmInputNetPort NMI_16;
    icmInputNetPort NMI_17;
    icmInputNetPort NMI_18;
    icmInputNetPort NMI_19;
    icmInputNetPort NMI_20;
    icmInputNetPort NMI_21;
    icmInputNetPort NMI_22;
    icmInputNetPort NMI_23;
    icmInputNetPort NMI_24;
    icmInputNetPort NMI_25;
    icmInputNetPort NMI_26;
    icmInputNetPort NMI_27;
    icmInputNetPort NMI_28;
    icmInputNetPort NMI_29;
    icmInputNetPort NMI_30;
    icmInputNetPort NMI_31;
    icmInputNetPort NMI_32;
    icmInputNetPort NMI_33;
    icmInputNetPort NMI_34;
    icmInputNetPort NMI_35;
    icmInputNetPort NMI_36;
    icmInputNetPort NMI_37;
    icmInputNetPort NMI_38;
    icmInputNetPort NMI_39;
    icmInputNetPort NMI_40;
    icmInputNetPort NMI_41;
    icmInputNetPort NMI_42;
    icmInputNetPort NMI_43;
    icmInputNetPort NMI_44;
    icmInputNetPort NMI_45;
    icmInputNetPort NMI_46;
    icmInputNetPort NMI_47;
    icmInputNetPort NMI_48;
    icmInputNetPort NMI_49;
    icmInputNetPort NMI_50;
    icmInputNetPort NMI_51;
    icmInputNetPort NMI_52;
    icmInputNetPort NMI_53;
    icmInputNetPort NMI_54;
    icmInputNetPort NMI_55;
    icmInputNetPort NMI_56;
    icmInputNetPort NMI_57;
    icmInputNetPort NMI_58;
    icmInputNetPort NMI_59;
    icmInputNetPort NMI_60;
    icmInputNetPort NMI_61;
    icmInputNetPort NMI_62;
    icmInputNetPort NMI_63;
    icmInputNetPort INT_00;
    icmInputNetPort INT_01;
    icmInputNetPort INT_02;
    icmInputNetPort INT_03;
    icmInputNetPort INT_04;
    icmInputNetPort INT_05;
    icmInputNetPort INT_06;
    icmInputNetPort INT_07;
    icmInputNetPort INT_08;
    icmInputNetPort INT_09;
    icmInputNetPort INT_10;
    icmInputNetPort INT_11;
    icmInputNetPort INT_12;
    icmInputNetPort INT_13;
    icmInputNetPort INT_14;
    icmInputNetPort INT_15;
    icmInputNetPort INT_16;
    icmInputNetPort INT_17;
    icmInputNetPort INT_18;
    icmInputNetPort INT_19;
    icmInputNetPort INT_20;
    icmInputNetPort INT_21;
    icmInputNetPort INT_22;
    icmInputNetPort INT_23;
    icmInputNetPort INT_24;
    icmInputNetPort INT_25;
    icmInputNetPort INT_26;
    icmInputNetPort INT_27;
    icmInputNetPort INT_28;
    icmInputNetPort INT_29;
    icmInputNetPort INT_30;
    icmInputNetPort INT_31;
    icmInputNetPort INT_32;
    icmInputNetPort INT_33;
    icmInputNetPort INT_34;
    icmInputNetPort INT_35;
    icmInputNetPort INT_36;
    icmInputNetPort INT_37;
    icmInputNetPort INT_38;
    icmInputNetPort INT_39;
    icmInputNetPort INT_40;
    icmInputNetPort INT_41;
    icmInputNetPort INT_42;
    icmInputNetPort INT_43;
    icmInputNetPort INT_44;
    icmInputNetPort INT_45;
    icmInputNetPort INT_46;
    icmInputNetPort INT_47;
    icmInputNetPort INT_48;
    icmInputNetPort INT_49;
    icmInputNetPort INT_50;
    icmInputNetPort INT_51;
    icmInputNetPort INT_52;
    icmInputNetPort INT_53;
    icmInputNetPort INT_54;
    icmInputNetPort INT_55;
    icmInputNetPort INT_56;
    icmInputNetPort INT_57;
    icmInputNetPort INT_58;
    icmInputNetPort INT_59;
    icmInputNetPort INT_60;
    icmInputNetPort INT_61;
    icmInputNetPort INT_62;
    icmInputNetPort INT_63;
    icmInputNetPort INT_64;
    icmInputNetPort INT_65;
    icmInputNetPort INT_66;
    icmInputNetPort INT_67;
    icmInputNetPort INT_68;
    icmInputNetPort INT_69;
    icmInputNetPort INT_70;
    icmInputNetPort INT_71;
    icmInputNetPort INT_72;
    icmInputNetPort INT_73;
    icmInputNetPort INT_74;
    icmInputNetPort INT_75;
    icmInputNetPort INT_76;
    icmInputNetPort INT_77;
    icmInputNetPort INT_78;
    icmInputNetPort INT_79;
    icmInputNetPort INT_80;
    icmInputNetPort INT_81;
    icmInputNetPort INT_82;
    icmInputNetPort INT_83;
    icmInputNetPort INT_84;
    icmInputNetPort INT_85;
    icmInputNetPort INT_86;
    icmInputNetPort INT_87;
    icmInputNetPort INT_88;
    icmInputNetPort INT_89;
    icmInputNetPort INT_90;
    icmInputNetPort INT_91;
    icmInputNetPort INT_92;
    icmInputNetPort INT_93;
    icmInputNetPort INT_94;
    icmInputNetPort INT_95;
    icmInputNetPort INT_96;
    icmInputNetPort INT_97;
    icmInputNetPort INT_98;
    icmInputNetPort INT_99;
    icmInputNetPort INT_100;
    icmInputNetPort INT_101;
    icmInputNetPort INT_102;
    icmInputNetPort INT_103;
    icmInputNetPort INT_104;
    icmInputNetPort INT_105;
    icmInputNetPort INT_106;
    icmInputNetPort INT_107;
    icmInputNetPort INT_108;
    icmInputNetPort INT_109;
    icmInputNetPort INT_110;
    icmInputNetPort INT_111;
    icmInputNetPort INT_112;
    icmInputNetPort INT_113;
    icmInputNetPort INT_114;
    icmInputNetPort INT_115;
    icmInputNetPort INT_116;

    intc(sc_module_name name, icmAttrListObject *initialAttrs = 0 )
        : icmPeripheral(name, getModel(), 0, initialAttrs)
        , INTCP0(this, "INTCP0", 0xfc) // static
        , RESET(this, "RESET")
        , NMI0(this, "NMI0")
        , NMI1(this, "NMI1")
        , NMI2(this, "NMI2")
        , INTP(this, "INTP")
        , INTACK(this, "INTACK")
        , MIRETI(this, "MIRETI")
        , IRESET(this, "IRESET")
        , NMI_00(this, "NMI_00")
        , NMI_01(this, "NMI_01")
        , NMI_02(this, "NMI_02")
        , NMI_03(this, "NMI_03")
        , NMI_04(this, "NMI_04")
        , NMI_05(this, "NMI_05")
        , NMI_06(this, "NMI_06")
        , NMI_07(this, "NMI_07")
        , NMI_08(this, "NMI_08")
        , NMI_09(this, "NMI_09")
        , NMI_10(this, "NMI_10")
        , NMI_11(this, "NMI_11")
        , NMI_12(this, "NMI_12")
        , NMI_13(this, "NMI_13")
        , NMI_14(this, "NMI_14")
        , NMI_15(this, "NMI_15")
        , NMI_16(this, "NMI_16")
        , NMI_17(this, "NMI_17")
        , NMI_18(this, "NMI_18")
        , NMI_19(this, "NMI_19")
        , NMI_20(this, "NMI_20")
        , NMI_21(this, "NMI_21")
        , NMI_22(this, "NMI_22")
        , NMI_23(this, "NMI_23")
        , NMI_24(this, "NMI_24")
        , NMI_25(this, "NMI_25")
        , NMI_26(this, "NMI_26")
        , NMI_27(this, "NMI_27")
        , NMI_28(this, "NMI_28")
        , NMI_29(this, "NMI_29")
        , NMI_30(this, "NMI_30")
        , NMI_31(this, "NMI_31")
        , NMI_32(this, "NMI_32")
        , NMI_33(this, "NMI_33")
        , NMI_34(this, "NMI_34")
        , NMI_35(this, "NMI_35")
        , NMI_36(this, "NMI_36")
        , NMI_37(this, "NMI_37")
        , NMI_38(this, "NMI_38")
        , NMI_39(this, "NMI_39")
        , NMI_40(this, "NMI_40")
        , NMI_41(this, "NMI_41")
        , NMI_42(this, "NMI_42")
        , NMI_43(this, "NMI_43")
        , NMI_44(this, "NMI_44")
        , NMI_45(this, "NMI_45")
        , NMI_46(this, "NMI_46")
        , NMI_47(this, "NMI_47")
        , NMI_48(this, "NMI_48")
        , NMI_49(this, "NMI_49")
        , NMI_50(this, "NMI_50")
        , NMI_51(this, "NMI_51")
        , NMI_52(this, "NMI_52")
        , NMI_53(this, "NMI_53")
        , NMI_54(this, "NMI_54")
        , NMI_55(this, "NMI_55")
        , NMI_56(this, "NMI_56")
        , NMI_57(this, "NMI_57")
        , NMI_58(this, "NMI_58")
        , NMI_59(this, "NMI_59")
        , NMI_60(this, "NMI_60")
        , NMI_61(this, "NMI_61")
        , NMI_62(this, "NMI_62")
        , NMI_63(this, "NMI_63")
        , INT_00(this, "INT_00")
        , INT_01(this, "INT_01")
        , INT_02(this, "INT_02")
        , INT_03(this, "INT_03")
        , INT_04(this, "INT_04")
        , INT_05(this, "INT_05")
        , INT_06(this, "INT_06")
        , INT_07(this, "INT_07")
        , INT_08(this, "INT_08")
        , INT_09(this, "INT_09")
        , INT_10(this, "INT_10")
        , INT_11(this, "INT_11")
        , INT_12(this, "INT_12")
        , INT_13(this, "INT_13")
        , INT_14(this, "INT_14")
        , INT_15(this, "INT_15")
        , INT_16(this, "INT_16")
        , INT_17(this, "INT_17")
        , INT_18(this, "INT_18")
        , INT_19(this, "INT_19")
        , INT_20(this, "INT_20")
        , INT_21(this, "INT_21")
        , INT_22(this, "INT_22")
        , INT_23(this, "INT_23")
        , INT_24(this, "INT_24")
        , INT_25(this, "INT_25")
        , INT_26(this, "INT_26")
        , INT_27(this, "INT_27")
        , INT_28(this, "INT_28")
        , INT_29(this, "INT_29")
        , INT_30(this, "INT_30")
        , INT_31(this, "INT_31")
        , INT_32(this, "INT_32")
        , INT_33(this, "INT_33")
        , INT_34(this, "INT_34")
        , INT_35(this, "INT_35")
        , INT_36(this, "INT_36")
        , INT_37(this, "INT_37")
        , INT_38(this, "INT_38")
        , INT_39(this, "INT_39")
        , INT_40(this, "INT_40")
        , INT_41(this, "INT_41")
        , INT_42(this, "INT_42")
        , INT_43(this, "INT_43")
        , INT_44(this, "INT_44")
        , INT_45(this, "INT_45")
        , INT_46(this, "INT_46")
        , INT_47(this, "INT_47")
        , INT_48(this, "INT_48")
        , INT_49(this, "INT_49")
        , INT_50(this, "INT_50")
        , INT_51(this, "INT_51")
        , INT_52(this, "INT_52")
        , INT_53(this, "INT_53")
        , INT_54(this, "INT_54")
        , INT_55(this, "INT_55")
        , INT_56(this, "INT_56")
        , INT_57(this, "INT_57")
        , INT_58(this, "INT_58")
        , INT_59(this, "INT_59")
        , INT_60(this, "INT_60")
        , INT_61(this, "INT_61")
        , INT_62(this, "INT_62")
        , INT_63(this, "INT_63")
        , INT_64(this, "INT_64")
        , INT_65(this, "INT_65")
        , INT_66(this, "INT_66")
        , INT_67(this, "INT_67")
        , INT_68(this, "INT_68")
        , INT_69(this, "INT_69")
        , INT_70(this, "INT_70")
        , INT_71(this, "INT_71")
        , INT_72(this, "INT_72")
        , INT_73(this, "INT_73")
        , INT_74(this, "INT_74")
        , INT_75(this, "INT_75")
        , INT_76(this, "INT_76")
        , INT_77(this, "INT_77")
        , INT_78(this, "INT_78")
        , INT_79(this, "INT_79")
        , INT_80(this, "INT_80")
        , INT_81(this, "INT_81")
        , INT_82(this, "INT_82")
        , INT_83(this, "INT_83")
        , INT_84(this, "INT_84")
        , INT_85(this, "INT_85")
        , INT_86(this, "INT_86")
        , INT_87(this, "INT_87")
        , INT_88(this, "INT_88")
        , INT_89(this, "INT_89")
        , INT_90(this, "INT_90")
        , INT_91(this, "INT_91")
        , INT_92(this, "INT_92")
        , INT_93(this, "INT_93")
        , INT_94(this, "INT_94")
        , INT_95(this, "INT_95")
        , INT_96(this, "INT_96")
        , INT_97(this, "INT_97")
        , INT_98(this, "INT_98")
        , INT_99(this, "INT_99")
        , INT_100(this, "INT_100")
        , INT_101(this, "INT_101")
        , INT_102(this, "INT_102")
        , INT_103(this, "INT_103")
        , INT_104(this, "INT_104")
        , INT_105(this, "INT_105")
        , INT_106(this, "INT_106")
        , INT_107(this, "INT_107")
        , INT_108(this, "INT_108")
        , INT_109(this, "INT_109")
        , INT_110(this, "INT_110")
        , INT_111(this, "INT_111")
        , INT_112(this, "INT_112")
        , INT_113(this, "INT_113")
        , INT_114(this, "INT_114")
        , INT_115(this, "INT_115")
        , INT_116(this, "INT_116")
    {
    }

}; /* class intc */

#endif
