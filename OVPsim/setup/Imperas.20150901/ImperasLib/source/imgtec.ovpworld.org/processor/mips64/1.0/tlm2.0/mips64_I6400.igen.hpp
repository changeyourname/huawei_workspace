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

#ifndef IMGTEC_OVPWORLD_ORG_PROCESSOR_MIPS64_I6400__1_0
#define IMGTEC_OVPWORLD_ORG_PROCESSOR_MIPS64_I6400__1_0

#include "ovpworld.org/modelSupport/tlmProcessor/1.0/tlm2.0/tlmProcessor.hpp"
using namespace sc_core;

class mips64_I6400 : public icmCpu
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "imgtec.ovpworld.org", "processor", "mips64", "1.0", "model");
    }

    const char *getSHL() {
        return icmGetVlnvString (NULL, "mips.ovpworld.org", "semihosting", "mips64Newlib", "1.0", "model");
    }

  public:
    icmCpuMasterPort     INSTRUCTION;
    icmCpuMasterPort     DATA;
    icmCpuInterrupt      reset;
    icmCpuInterrupt      dint;
    icmCpuInterrupt      int0;
    icmCpuInterrupt      int1;
    icmCpuInterrupt      int2;
    icmCpuInterrupt      int3;
    icmCpuInterrupt      int4;
    icmCpuInterrupt      int5;
    icmCpuInterrupt      int6;
    icmCpuInterrupt      int7;
    icmCpuInterrupt      int8;
    icmCpuInterrupt      int9;
    icmCpuInterrupt      int10;
    icmCpuInterrupt      int11;
    icmCpuInterrupt      int12;
    icmCpuInterrupt      int13;
    icmCpuInterrupt      int14;
    icmCpuInterrupt      int15;
    icmCpuInterrupt      int16;
    icmCpuInterrupt      int17;
    icmCpuInterrupt      int18;
    icmCpuInterrupt      int19;
    icmCpuInterrupt      int20;
    icmCpuInterrupt      int21;
    icmCpuInterrupt      int22;
    icmCpuInterrupt      int23;
    icmCpuInterrupt      int24;
    icmCpuInterrupt      int25;
    icmCpuInterrupt      int26;
    icmCpuInterrupt      int27;
    icmCpuInterrupt      int28;
    icmCpuInterrupt      int29;
    icmCpuInterrupt      int30;
    icmCpuInterrupt      int31;
    icmCpuInterrupt      int32;
    icmCpuInterrupt      int33;
    icmCpuInterrupt      int34;
    icmCpuInterrupt      int35;
    icmCpuInterrupt      int36;
    icmCpuInterrupt      int37;
    icmCpuInterrupt      int38;
    icmCpuInterrupt      int39;
    icmCpuInterrupt      int40;
    icmCpuInterrupt      int41;
    icmCpuInterrupt      int42;
    icmCpuInterrupt      int43;
    icmCpuInterrupt      int44;
    icmCpuInterrupt      int45;
    icmCpuInterrupt      int46;
    icmCpuInterrupt      int47;
    icmCpuInterrupt      int48;
    icmCpuInterrupt      int49;
    icmCpuInterrupt      int50;
    icmCpuInterrupt      int51;
    icmCpuInterrupt      int52;
    icmCpuInterrupt      int53;
    icmCpuInterrupt      int54;
    icmCpuInterrupt      int55;
    icmCpuInterrupt      int56;
    icmCpuInterrupt      int57;
    icmCpuInterrupt      int58;
    icmCpuInterrupt      int59;
    icmCpuInterrupt      int60;
    icmCpuInterrupt      int61;
    icmCpuInterrupt      int62;
    icmCpuInterrupt      int63;
    icmCpuInterrupt      int64;
    icmCpuInterrupt      int65;
    icmCpuInterrupt      int66;
    icmCpuInterrupt      int67;
    icmCpuInterrupt      int68;
    icmCpuInterrupt      int69;
    icmCpuInterrupt      int70;
    icmCpuInterrupt      int71;
    icmCpuInterrupt      int72;
    icmCpuInterrupt      int73;
    icmCpuInterrupt      int74;
    icmCpuInterrupt      int75;
    icmCpuInterrupt      int76;
    icmCpuInterrupt      int77;
    icmCpuInterrupt      int78;
    icmCpuInterrupt      int79;
    icmCpuInterrupt      int80;
    icmCpuInterrupt      int81;
    icmCpuInterrupt      int82;
    icmCpuInterrupt      int83;
    icmCpuInterrupt      int84;
    icmCpuInterrupt      int85;
    icmCpuInterrupt      int86;
    icmCpuInterrupt      int87;
    icmCpuInterrupt      int88;
    icmCpuInterrupt      int89;
    icmCpuInterrupt      int90;
    icmCpuInterrupt      int91;
    icmCpuInterrupt      int92;
    icmCpuInterrupt      int93;
    icmCpuInterrupt      int94;
    icmCpuInterrupt      int95;
    icmCpuInterrupt      int96;
    icmCpuInterrupt      int97;
    icmCpuInterrupt      int98;
    icmCpuInterrupt      int99;
    icmCpuInterrupt      int100;
    icmCpuInterrupt      int101;
    icmCpuInterrupt      int102;
    icmCpuInterrupt      int103;
    icmCpuInterrupt      int104;
    icmCpuInterrupt      int105;
    icmCpuInterrupt      int106;
    icmCpuInterrupt      int107;
    icmCpuInterrupt      int108;
    icmCpuInterrupt      int109;
    icmCpuInterrupt      int110;
    icmCpuInterrupt      int111;
    icmCpuInterrupt      int112;
    icmCpuInterrupt      int113;
    icmCpuInterrupt      int114;
    icmCpuInterrupt      int115;
    icmCpuInterrupt      int116;
    icmCpuInterrupt      int117;
    icmCpuInterrupt      int118;
    icmCpuInterrupt      int119;
    icmCpuInterrupt      int120;
    icmCpuInterrupt      int121;
    icmCpuInterrupt      int122;
    icmCpuInterrupt      int123;
    icmCpuInterrupt      int124;
    icmCpuInterrupt      int125;
    icmCpuInterrupt      int126;
    icmCpuInterrupt      int127;
    icmCpuInterrupt      dint_CPU0_VC0;
    icmCpuInterrupt      hwint0_CPU0_VC0;
    icmCpuInterrupt      hwint1_CPU0_VC0;
    icmCpuInterrupt      hwint2_CPU0_VC0;
    icmCpuInterrupt      hwint3_CPU0_VC0;
    icmCpuInterrupt      hwint4_CPU0_VC0;
    icmCpuInterrupt      hwint5_CPU0_VC0;
    icmCpuInterrupt      nmi_CPU0_VC0;
    icmCpuInterrupt      EICPresent_CPU0_VC0;
    icmCpuInterrupt      EIC_RIPL_CPU0_VC0;
    icmCpuInterrupt      EIC_EICSS_CPU0_VC0;
    icmCpuInterrupt      EIC_VectorNum_CPU0_VC0;
    icmCpuInterrupt      EIC_VectorOffset_CPU0_VC0;
    icmCpuInterrupt      EIC_GID_CPU0_VC0;
    icmCpuOutputNetPort  intISS_CPU0_VC0;
    icmCpuOutputNetPort  causeTI_CPU0_VC0;
    icmCpuOutputNetPort  causeIP0_CPU0_VC0;
    icmCpuOutputNetPort  causeIP1_CPU0_VC0;
    icmCpuInterrupt      hwint0;
    icmCpuInterrupt      Guest_EIC_RIPL_CPU0_VC0;
    icmCpuInterrupt      Guest_EIC_EICSS_CPU0_VC0;
    icmCpuInterrupt      Guest_EIC_VectorNum_CPU0_VC0;
    icmCpuInterrupt      Guest_EIC_VectorOffset_CPU0_VC0;
    icmCpuInterrupt      Guest_EIC_GID_CPU0_VC0;
    icmCpuOutputNetPort  Guest_intISS_CPU0_VC0;
    icmCpuOutputNetPort  Guest_causeTI_CPU0_VC0;
    icmCpuOutputNetPort  Guest_causeIP0_CPU0_VC0;
    icmCpuOutputNetPort  Guest_causeIP1_CPU0_VC0;
    icmCpuInterrupt      dint_CPU0_VC1;
    icmCpuInterrupt      hwint0_CPU0_VC1;
    icmCpuInterrupt      hwint1_CPU0_VC1;
    icmCpuInterrupt      hwint2_CPU0_VC1;
    icmCpuInterrupt      hwint3_CPU0_VC1;
    icmCpuInterrupt      hwint4_CPU0_VC1;
    icmCpuInterrupt      hwint5_CPU0_VC1;
    icmCpuInterrupt      nmi_CPU0_VC1;
    icmCpuInterrupt      EICPresent_CPU0_VC1;
    icmCpuInterrupt      EIC_RIPL_CPU0_VC1;
    icmCpuInterrupt      EIC_EICSS_CPU0_VC1;
    icmCpuInterrupt      EIC_VectorNum_CPU0_VC1;
    icmCpuInterrupt      EIC_VectorOffset_CPU0_VC1;
    icmCpuInterrupt      EIC_GID_CPU0_VC1;
    icmCpuOutputNetPort  intISS_CPU0_VC1;
    icmCpuOutputNetPort  causeTI_CPU0_VC1;
    icmCpuOutputNetPort  causeIP0_CPU0_VC1;
    icmCpuOutputNetPort  causeIP1_CPU0_VC1;
    icmCpuInterrupt      Guest_EIC_RIPL_CPU0_VC1;
    icmCpuInterrupt      Guest_EIC_EICSS_CPU0_VC1;
    icmCpuInterrupt      Guest_EIC_VectorNum_CPU0_VC1;
    icmCpuInterrupt      Guest_EIC_VectorOffset_CPU0_VC1;
    icmCpuInterrupt      Guest_EIC_GID_CPU0_VC1;
    icmCpuOutputNetPort  Guest_intISS_CPU0_VC1;
    icmCpuOutputNetPort  Guest_causeTI_CPU0_VC1;
    icmCpuOutputNetPort  Guest_causeIP0_CPU0_VC1;
    icmCpuOutputNetPort  Guest_causeIP1_CPU0_VC1;
    icmCpuInterrupt      dint_CPU1_VC0;
    icmCpuInterrupt      hwint0_CPU1_VC0;
    icmCpuInterrupt      hwint1_CPU1_VC0;
    icmCpuInterrupt      hwint2_CPU1_VC0;
    icmCpuInterrupt      hwint3_CPU1_VC0;
    icmCpuInterrupt      hwint4_CPU1_VC0;
    icmCpuInterrupt      hwint5_CPU1_VC0;
    icmCpuInterrupt      nmi_CPU1_VC0;
    icmCpuInterrupt      EICPresent_CPU1_VC0;
    icmCpuInterrupt      EIC_RIPL_CPU1_VC0;
    icmCpuInterrupt      EIC_EICSS_CPU1_VC0;
    icmCpuInterrupt      EIC_VectorNum_CPU1_VC0;
    icmCpuInterrupt      EIC_VectorOffset_CPU1_VC0;
    icmCpuInterrupt      EIC_GID_CPU1_VC0;
    icmCpuOutputNetPort  intISS_CPU1_VC0;
    icmCpuOutputNetPort  causeTI_CPU1_VC0;
    icmCpuOutputNetPort  causeIP0_CPU1_VC0;
    icmCpuOutputNetPort  causeIP1_CPU1_VC0;
    icmCpuInterrupt      Guest_EIC_RIPL_CPU1_VC0;
    icmCpuInterrupt      Guest_EIC_EICSS_CPU1_VC0;
    icmCpuInterrupt      Guest_EIC_VectorNum_CPU1_VC0;
    icmCpuInterrupt      Guest_EIC_VectorOffset_CPU1_VC0;
    icmCpuInterrupt      Guest_EIC_GID_CPU1_VC0;
    icmCpuOutputNetPort  Guest_intISS_CPU1_VC0;
    icmCpuOutputNetPort  Guest_causeTI_CPU1_VC0;
    icmCpuOutputNetPort  Guest_causeIP0_CPU1_VC0;
    icmCpuOutputNetPort  Guest_causeIP1_CPU1_VC0;
    icmCpuInterrupt      dint_CPU1_VC1;
    icmCpuInterrupt      hwint0_CPU1_VC1;
    icmCpuInterrupt      hwint1_CPU1_VC1;
    icmCpuInterrupt      hwint2_CPU1_VC1;
    icmCpuInterrupt      hwint3_CPU1_VC1;
    icmCpuInterrupt      hwint4_CPU1_VC1;
    icmCpuInterrupt      hwint5_CPU1_VC1;
    icmCpuInterrupt      nmi_CPU1_VC1;
    icmCpuInterrupt      EICPresent_CPU1_VC1;
    icmCpuInterrupt      EIC_RIPL_CPU1_VC1;
    icmCpuInterrupt      EIC_EICSS_CPU1_VC1;
    icmCpuInterrupt      EIC_VectorNum_CPU1_VC1;
    icmCpuInterrupt      EIC_VectorOffset_CPU1_VC1;
    icmCpuInterrupt      EIC_GID_CPU1_VC1;
    icmCpuOutputNetPort  intISS_CPU1_VC1;
    icmCpuOutputNetPort  causeTI_CPU1_VC1;
    icmCpuOutputNetPort  causeIP0_CPU1_VC1;
    icmCpuOutputNetPort  causeIP1_CPU1_VC1;
    icmCpuInterrupt      Guest_EIC_RIPL_CPU1_VC1;
    icmCpuInterrupt      Guest_EIC_EICSS_CPU1_VC1;
    icmCpuInterrupt      Guest_EIC_VectorNum_CPU1_VC1;
    icmCpuInterrupt      Guest_EIC_VectorOffset_CPU1_VC1;
    icmCpuInterrupt      Guest_EIC_GID_CPU1_VC1;
    icmCpuOutputNetPort  Guest_intISS_CPU1_VC1;
    icmCpuOutputNetPort  Guest_causeTI_CPU1_VC1;
    icmCpuOutputNetPort  Guest_causeIP0_CPU1_VC1;
    icmCpuOutputNetPort  Guest_causeIP1_CPU1_VC1;
    icmCpuInterrupt      dint_CPU2_VC0;
    icmCpuInterrupt      hwint0_CPU2_VC0;
    icmCpuInterrupt      hwint1_CPU2_VC0;
    icmCpuInterrupt      hwint2_CPU2_VC0;
    icmCpuInterrupt      hwint3_CPU2_VC0;
    icmCpuInterrupt      hwint4_CPU2_VC0;
    icmCpuInterrupt      hwint5_CPU2_VC0;
    icmCpuInterrupt      nmi_CPU2_VC0;
    icmCpuInterrupt      EICPresent_CPU2_VC0;
    icmCpuInterrupt      EIC_RIPL_CPU2_VC0;
    icmCpuInterrupt      EIC_EICSS_CPU2_VC0;
    icmCpuInterrupt      EIC_VectorNum_CPU2_VC0;
    icmCpuInterrupt      EIC_VectorOffset_CPU2_VC0;
    icmCpuInterrupt      EIC_GID_CPU2_VC0;
    icmCpuOutputNetPort  intISS_CPU2_VC0;
    icmCpuOutputNetPort  causeTI_CPU2_VC0;
    icmCpuOutputNetPort  causeIP0_CPU2_VC0;
    icmCpuOutputNetPort  causeIP1_CPU2_VC0;
    icmCpuInterrupt      Guest_EIC_RIPL_CPU2_VC0;
    icmCpuInterrupt      Guest_EIC_EICSS_CPU2_VC0;
    icmCpuInterrupt      Guest_EIC_VectorNum_CPU2_VC0;
    icmCpuInterrupt      Guest_EIC_VectorOffset_CPU2_VC0;
    icmCpuInterrupt      Guest_EIC_GID_CPU2_VC0;
    icmCpuOutputNetPort  Guest_intISS_CPU2_VC0;
    icmCpuOutputNetPort  Guest_causeTI_CPU2_VC0;
    icmCpuOutputNetPort  Guest_causeIP0_CPU2_VC0;
    icmCpuOutputNetPort  Guest_causeIP1_CPU2_VC0;
    icmCpuInterrupt      dint_CPU2_VC1;
    icmCpuInterrupt      hwint0_CPU2_VC1;
    icmCpuInterrupt      hwint1_CPU2_VC1;
    icmCpuInterrupt      hwint2_CPU2_VC1;
    icmCpuInterrupt      hwint3_CPU2_VC1;
    icmCpuInterrupt      hwint4_CPU2_VC1;
    icmCpuInterrupt      hwint5_CPU2_VC1;
    icmCpuInterrupt      nmi_CPU2_VC1;
    icmCpuInterrupt      EICPresent_CPU2_VC1;
    icmCpuInterrupt      EIC_RIPL_CPU2_VC1;
    icmCpuInterrupt      EIC_EICSS_CPU2_VC1;
    icmCpuInterrupt      EIC_VectorNum_CPU2_VC1;
    icmCpuInterrupt      EIC_VectorOffset_CPU2_VC1;
    icmCpuInterrupt      EIC_GID_CPU2_VC1;
    icmCpuOutputNetPort  intISS_CPU2_VC1;
    icmCpuOutputNetPort  causeTI_CPU2_VC1;
    icmCpuOutputNetPort  causeIP0_CPU2_VC1;
    icmCpuOutputNetPort  causeIP1_CPU2_VC1;
    icmCpuInterrupt      Guest_EIC_RIPL_CPU2_VC1;
    icmCpuInterrupt      Guest_EIC_EICSS_CPU2_VC1;
    icmCpuInterrupt      Guest_EIC_VectorNum_CPU2_VC1;
    icmCpuInterrupt      Guest_EIC_VectorOffset_CPU2_VC1;
    icmCpuInterrupt      Guest_EIC_GID_CPU2_VC1;
    icmCpuOutputNetPort  Guest_intISS_CPU2_VC1;
    icmCpuOutputNetPort  Guest_causeTI_CPU2_VC1;
    icmCpuOutputNetPort  Guest_causeIP0_CPU2_VC1;
    icmCpuOutputNetPort  Guest_causeIP1_CPU2_VC1;
    icmCpuInterrupt      dint_CPU3_VC0;
    icmCpuInterrupt      hwint0_CPU3_VC0;
    icmCpuInterrupt      hwint1_CPU3_VC0;
    icmCpuInterrupt      hwint2_CPU3_VC0;
    icmCpuInterrupt      hwint3_CPU3_VC0;
    icmCpuInterrupt      hwint4_CPU3_VC0;
    icmCpuInterrupt      hwint5_CPU3_VC0;
    icmCpuInterrupt      nmi_CPU3_VC0;
    icmCpuInterrupt      EICPresent_CPU3_VC0;
    icmCpuInterrupt      EIC_RIPL_CPU3_VC0;
    icmCpuInterrupt      EIC_EICSS_CPU3_VC0;
    icmCpuInterrupt      EIC_VectorNum_CPU3_VC0;
    icmCpuInterrupt      EIC_VectorOffset_CPU3_VC0;
    icmCpuInterrupt      EIC_GID_CPU3_VC0;
    icmCpuOutputNetPort  intISS_CPU3_VC0;
    icmCpuOutputNetPort  causeTI_CPU3_VC0;
    icmCpuOutputNetPort  causeIP0_CPU3_VC0;
    icmCpuOutputNetPort  causeIP1_CPU3_VC0;
    icmCpuInterrupt      Guest_EIC_RIPL_CPU3_VC0;
    icmCpuInterrupt      Guest_EIC_EICSS_CPU3_VC0;
    icmCpuInterrupt      Guest_EIC_VectorNum_CPU3_VC0;
    icmCpuInterrupt      Guest_EIC_VectorOffset_CPU3_VC0;
    icmCpuInterrupt      Guest_EIC_GID_CPU3_VC0;
    icmCpuOutputNetPort  Guest_intISS_CPU3_VC0;
    icmCpuOutputNetPort  Guest_causeTI_CPU3_VC0;
    icmCpuOutputNetPort  Guest_causeIP0_CPU3_VC0;
    icmCpuOutputNetPort  Guest_causeIP1_CPU3_VC0;
    icmCpuInterrupt      dint_CPU3_VC1;
    icmCpuInterrupt      hwint0_CPU3_VC1;
    icmCpuInterrupt      hwint1_CPU3_VC1;
    icmCpuInterrupt      hwint2_CPU3_VC1;
    icmCpuInterrupt      hwint3_CPU3_VC1;
    icmCpuInterrupt      hwint4_CPU3_VC1;
    icmCpuInterrupt      hwint5_CPU3_VC1;
    icmCpuInterrupt      nmi_CPU3_VC1;
    icmCpuInterrupt      EICPresent_CPU3_VC1;
    icmCpuInterrupt      EIC_RIPL_CPU3_VC1;
    icmCpuInterrupt      EIC_EICSS_CPU3_VC1;
    icmCpuInterrupt      EIC_VectorNum_CPU3_VC1;
    icmCpuInterrupt      EIC_VectorOffset_CPU3_VC1;
    icmCpuInterrupt      EIC_GID_CPU3_VC1;
    icmCpuOutputNetPort  intISS_CPU3_VC1;
    icmCpuOutputNetPort  causeTI_CPU3_VC1;
    icmCpuOutputNetPort  causeIP0_CPU3_VC1;
    icmCpuOutputNetPort  causeIP1_CPU3_VC1;
    icmCpuInterrupt      Guest_EIC_RIPL_CPU3_VC1;
    icmCpuInterrupt      Guest_EIC_EICSS_CPU3_VC1;
    icmCpuInterrupt      Guest_EIC_VectorNum_CPU3_VC1;
    icmCpuInterrupt      Guest_EIC_VectorOffset_CPU3_VC1;
    icmCpuInterrupt      Guest_EIC_GID_CPU3_VC1;
    icmCpuOutputNetPort  Guest_intISS_CPU3_VC1;
    icmCpuOutputNetPort  Guest_causeTI_CPU3_VC1;
    icmCpuOutputNetPort  Guest_causeIP0_CPU3_VC1;
    icmCpuOutputNetPort  Guest_causeIP1_CPU3_VC1;

    mips64_I6400(
        sc_module_name        name,
        const unsigned int    ID,
        icmNewProcAttrs       attrs        = ICM_ATTR_DEFAULT,
        icmAttrListObject    *attrList    = NULL,
        const char           *semiHost    = NULL,
        Uns32                 addressBits = 32,
        bool                  dmi         = true,
        Uns32                 cpuFlags    = 0
     )
    : icmCpu(name, ID, "mips64", getModel(), 0, semiHost ? ((0 == strlen(semiHost)) ? 0 : semiHost) : getSHL(), attrs, attrList, addressBits, dmi, cpuFlags)
    , INSTRUCTION (this, "INSTRUCTION", 37)
    , DATA (this, "DATA", 37)
    , reset("reset", this)
    , dint("dint", this)
    , int0("int0", this)
    , int1("int1", this)
    , int2("int2", this)
    , int3("int3", this)
    , int4("int4", this)
    , int5("int5", this)
    , int6("int6", this)
    , int7("int7", this)
    , int8("int8", this)
    , int9("int9", this)
    , int10("int10", this)
    , int11("int11", this)
    , int12("int12", this)
    , int13("int13", this)
    , int14("int14", this)
    , int15("int15", this)
    , int16("int16", this)
    , int17("int17", this)
    , int18("int18", this)
    , int19("int19", this)
    , int20("int20", this)
    , int21("int21", this)
    , int22("int22", this)
    , int23("int23", this)
    , int24("int24", this)
    , int25("int25", this)
    , int26("int26", this)
    , int27("int27", this)
    , int28("int28", this)
    , int29("int29", this)
    , int30("int30", this)
    , int31("int31", this)
    , int32("int32", this)
    , int33("int33", this)
    , int34("int34", this)
    , int35("int35", this)
    , int36("int36", this)
    , int37("int37", this)
    , int38("int38", this)
    , int39("int39", this)
    , int40("int40", this)
    , int41("int41", this)
    , int42("int42", this)
    , int43("int43", this)
    , int44("int44", this)
    , int45("int45", this)
    , int46("int46", this)
    , int47("int47", this)
    , int48("int48", this)
    , int49("int49", this)
    , int50("int50", this)
    , int51("int51", this)
    , int52("int52", this)
    , int53("int53", this)
    , int54("int54", this)
    , int55("int55", this)
    , int56("int56", this)
    , int57("int57", this)
    , int58("int58", this)
    , int59("int59", this)
    , int60("int60", this)
    , int61("int61", this)
    , int62("int62", this)
    , int63("int63", this)
    , int64("int64", this)
    , int65("int65", this)
    , int66("int66", this)
    , int67("int67", this)
    , int68("int68", this)
    , int69("int69", this)
    , int70("int70", this)
    , int71("int71", this)
    , int72("int72", this)
    , int73("int73", this)
    , int74("int74", this)
    , int75("int75", this)
    , int76("int76", this)
    , int77("int77", this)
    , int78("int78", this)
    , int79("int79", this)
    , int80("int80", this)
    , int81("int81", this)
    , int82("int82", this)
    , int83("int83", this)
    , int84("int84", this)
    , int85("int85", this)
    , int86("int86", this)
    , int87("int87", this)
    , int88("int88", this)
    , int89("int89", this)
    , int90("int90", this)
    , int91("int91", this)
    , int92("int92", this)
    , int93("int93", this)
    , int94("int94", this)
    , int95("int95", this)
    , int96("int96", this)
    , int97("int97", this)
    , int98("int98", this)
    , int99("int99", this)
    , int100("int100", this)
    , int101("int101", this)
    , int102("int102", this)
    , int103("int103", this)
    , int104("int104", this)
    , int105("int105", this)
    , int106("int106", this)
    , int107("int107", this)
    , int108("int108", this)
    , int109("int109", this)
    , int110("int110", this)
    , int111("int111", this)
    , int112("int112", this)
    , int113("int113", this)
    , int114("int114", this)
    , int115("int115", this)
    , int116("int116", this)
    , int117("int117", this)
    , int118("int118", this)
    , int119("int119", this)
    , int120("int120", this)
    , int121("int121", this)
    , int122("int122", this)
    , int123("int123", this)
    , int124("int124", this)
    , int125("int125", this)
    , int126("int126", this)
    , int127("int127", this)
    , dint_CPU0_VC0("dint_CPU0_VC0", this)
    , hwint0_CPU0_VC0("hwint0_CPU0_VC0", this)
    , hwint1_CPU0_VC0("hwint1_CPU0_VC0", this)
    , hwint2_CPU0_VC0("hwint2_CPU0_VC0", this)
    , hwint3_CPU0_VC0("hwint3_CPU0_VC0", this)
    , hwint4_CPU0_VC0("hwint4_CPU0_VC0", this)
    , hwint5_CPU0_VC0("hwint5_CPU0_VC0", this)
    , nmi_CPU0_VC0("nmi_CPU0_VC0", this)
    , EICPresent_CPU0_VC0("EICPresent_CPU0_VC0", this)
    , EIC_RIPL_CPU0_VC0("EIC_RIPL_CPU0_VC0", this)
    , EIC_EICSS_CPU0_VC0("EIC_EICSS_CPU0_VC0", this)
    , EIC_VectorNum_CPU0_VC0("EIC_VectorNum_CPU0_VC0", this)
    , EIC_VectorOffset_CPU0_VC0("EIC_VectorOffset_CPU0_VC0", this)
    , EIC_GID_CPU0_VC0("EIC_GID_CPU0_VC0", this)
    , intISS_CPU0_VC0("intISS_CPU0_VC0", this)
    , causeTI_CPU0_VC0("causeTI_CPU0_VC0", this)
    , causeIP0_CPU0_VC0("causeIP0_CPU0_VC0", this)
    , causeIP1_CPU0_VC0("causeIP1_CPU0_VC0", this)
    , hwint0("hwint0", this)
    , Guest_EIC_RIPL_CPU0_VC0("Guest.EIC_RIPL_CPU0_VC0", this)
    , Guest_EIC_EICSS_CPU0_VC0("Guest.EIC_EICSS_CPU0_VC0", this)
    , Guest_EIC_VectorNum_CPU0_VC0("Guest.EIC_VectorNum_CPU0_VC0", this)
    , Guest_EIC_VectorOffset_CPU0_VC0("Guest.EIC_VectorOffset_CPU0_VC0", this)
    , Guest_EIC_GID_CPU0_VC0("Guest.EIC_GID_CPU0_VC0", this)
    , Guest_intISS_CPU0_VC0("Guest.intISS_CPU0_VC0", this)
    , Guest_causeTI_CPU0_VC0("Guest.causeTI_CPU0_VC0", this)
    , Guest_causeIP0_CPU0_VC0("Guest.causeIP0_CPU0_VC0", this)
    , Guest_causeIP1_CPU0_VC0("Guest.causeIP1_CPU0_VC0", this)
    , dint_CPU0_VC1("dint_CPU0_VC1", this)
    , hwint0_CPU0_VC1("hwint0_CPU0_VC1", this)
    , hwint1_CPU0_VC1("hwint1_CPU0_VC1", this)
    , hwint2_CPU0_VC1("hwint2_CPU0_VC1", this)
    , hwint3_CPU0_VC1("hwint3_CPU0_VC1", this)
    , hwint4_CPU0_VC1("hwint4_CPU0_VC1", this)
    , hwint5_CPU0_VC1("hwint5_CPU0_VC1", this)
    , nmi_CPU0_VC1("nmi_CPU0_VC1", this)
    , EICPresent_CPU0_VC1("EICPresent_CPU0_VC1", this)
    , EIC_RIPL_CPU0_VC1("EIC_RIPL_CPU0_VC1", this)
    , EIC_EICSS_CPU0_VC1("EIC_EICSS_CPU0_VC1", this)
    , EIC_VectorNum_CPU0_VC1("EIC_VectorNum_CPU0_VC1", this)
    , EIC_VectorOffset_CPU0_VC1("EIC_VectorOffset_CPU0_VC1", this)
    , EIC_GID_CPU0_VC1("EIC_GID_CPU0_VC1", this)
    , intISS_CPU0_VC1("intISS_CPU0_VC1", this)
    , causeTI_CPU0_VC1("causeTI_CPU0_VC1", this)
    , causeIP0_CPU0_VC1("causeIP0_CPU0_VC1", this)
    , causeIP1_CPU0_VC1("causeIP1_CPU0_VC1", this)
    , Guest_EIC_RIPL_CPU0_VC1("Guest.EIC_RIPL_CPU0_VC1", this)
    , Guest_EIC_EICSS_CPU0_VC1("Guest.EIC_EICSS_CPU0_VC1", this)
    , Guest_EIC_VectorNum_CPU0_VC1("Guest.EIC_VectorNum_CPU0_VC1", this)
    , Guest_EIC_VectorOffset_CPU0_VC1("Guest.EIC_VectorOffset_CPU0_VC1", this)
    , Guest_EIC_GID_CPU0_VC1("Guest.EIC_GID_CPU0_VC1", this)
    , Guest_intISS_CPU0_VC1("Guest.intISS_CPU0_VC1", this)
    , Guest_causeTI_CPU0_VC1("Guest.causeTI_CPU0_VC1", this)
    , Guest_causeIP0_CPU0_VC1("Guest.causeIP0_CPU0_VC1", this)
    , Guest_causeIP1_CPU0_VC1("Guest.causeIP1_CPU0_VC1", this)
    , dint_CPU1_VC0("dint_CPU1_VC0", this)
    , hwint0_CPU1_VC0("hwint0_CPU1_VC0", this)
    , hwint1_CPU1_VC0("hwint1_CPU1_VC0", this)
    , hwint2_CPU1_VC0("hwint2_CPU1_VC0", this)
    , hwint3_CPU1_VC0("hwint3_CPU1_VC0", this)
    , hwint4_CPU1_VC0("hwint4_CPU1_VC0", this)
    , hwint5_CPU1_VC0("hwint5_CPU1_VC0", this)
    , nmi_CPU1_VC0("nmi_CPU1_VC0", this)
    , EICPresent_CPU1_VC0("EICPresent_CPU1_VC0", this)
    , EIC_RIPL_CPU1_VC0("EIC_RIPL_CPU1_VC0", this)
    , EIC_EICSS_CPU1_VC0("EIC_EICSS_CPU1_VC0", this)
    , EIC_VectorNum_CPU1_VC0("EIC_VectorNum_CPU1_VC0", this)
    , EIC_VectorOffset_CPU1_VC0("EIC_VectorOffset_CPU1_VC0", this)
    , EIC_GID_CPU1_VC0("EIC_GID_CPU1_VC0", this)
    , intISS_CPU1_VC0("intISS_CPU1_VC0", this)
    , causeTI_CPU1_VC0("causeTI_CPU1_VC0", this)
    , causeIP0_CPU1_VC0("causeIP0_CPU1_VC0", this)
    , causeIP1_CPU1_VC0("causeIP1_CPU1_VC0", this)
    , Guest_EIC_RIPL_CPU1_VC0("Guest.EIC_RIPL_CPU1_VC0", this)
    , Guest_EIC_EICSS_CPU1_VC0("Guest.EIC_EICSS_CPU1_VC0", this)
    , Guest_EIC_VectorNum_CPU1_VC0("Guest.EIC_VectorNum_CPU1_VC0", this)
    , Guest_EIC_VectorOffset_CPU1_VC0("Guest.EIC_VectorOffset_CPU1_VC0", this)
    , Guest_EIC_GID_CPU1_VC0("Guest.EIC_GID_CPU1_VC0", this)
    , Guest_intISS_CPU1_VC0("Guest.intISS_CPU1_VC0", this)
    , Guest_causeTI_CPU1_VC0("Guest.causeTI_CPU1_VC0", this)
    , Guest_causeIP0_CPU1_VC0("Guest.causeIP0_CPU1_VC0", this)
    , Guest_causeIP1_CPU1_VC0("Guest.causeIP1_CPU1_VC0", this)
    , dint_CPU1_VC1("dint_CPU1_VC1", this)
    , hwint0_CPU1_VC1("hwint0_CPU1_VC1", this)
    , hwint1_CPU1_VC1("hwint1_CPU1_VC1", this)
    , hwint2_CPU1_VC1("hwint2_CPU1_VC1", this)
    , hwint3_CPU1_VC1("hwint3_CPU1_VC1", this)
    , hwint4_CPU1_VC1("hwint4_CPU1_VC1", this)
    , hwint5_CPU1_VC1("hwint5_CPU1_VC1", this)
    , nmi_CPU1_VC1("nmi_CPU1_VC1", this)
    , EICPresent_CPU1_VC1("EICPresent_CPU1_VC1", this)
    , EIC_RIPL_CPU1_VC1("EIC_RIPL_CPU1_VC1", this)
    , EIC_EICSS_CPU1_VC1("EIC_EICSS_CPU1_VC1", this)
    , EIC_VectorNum_CPU1_VC1("EIC_VectorNum_CPU1_VC1", this)
    , EIC_VectorOffset_CPU1_VC1("EIC_VectorOffset_CPU1_VC1", this)
    , EIC_GID_CPU1_VC1("EIC_GID_CPU1_VC1", this)
    , intISS_CPU1_VC1("intISS_CPU1_VC1", this)
    , causeTI_CPU1_VC1("causeTI_CPU1_VC1", this)
    , causeIP0_CPU1_VC1("causeIP0_CPU1_VC1", this)
    , causeIP1_CPU1_VC1("causeIP1_CPU1_VC1", this)
    , Guest_EIC_RIPL_CPU1_VC1("Guest.EIC_RIPL_CPU1_VC1", this)
    , Guest_EIC_EICSS_CPU1_VC1("Guest.EIC_EICSS_CPU1_VC1", this)
    , Guest_EIC_VectorNum_CPU1_VC1("Guest.EIC_VectorNum_CPU1_VC1", this)
    , Guest_EIC_VectorOffset_CPU1_VC1("Guest.EIC_VectorOffset_CPU1_VC1", this)
    , Guest_EIC_GID_CPU1_VC1("Guest.EIC_GID_CPU1_VC1", this)
    , Guest_intISS_CPU1_VC1("Guest.intISS_CPU1_VC1", this)
    , Guest_causeTI_CPU1_VC1("Guest.causeTI_CPU1_VC1", this)
    , Guest_causeIP0_CPU1_VC1("Guest.causeIP0_CPU1_VC1", this)
    , Guest_causeIP1_CPU1_VC1("Guest.causeIP1_CPU1_VC1", this)
    , dint_CPU2_VC0("dint_CPU2_VC0", this)
    , hwint0_CPU2_VC0("hwint0_CPU2_VC0", this)
    , hwint1_CPU2_VC0("hwint1_CPU2_VC0", this)
    , hwint2_CPU2_VC0("hwint2_CPU2_VC0", this)
    , hwint3_CPU2_VC0("hwint3_CPU2_VC0", this)
    , hwint4_CPU2_VC0("hwint4_CPU2_VC0", this)
    , hwint5_CPU2_VC0("hwint5_CPU2_VC0", this)
    , nmi_CPU2_VC0("nmi_CPU2_VC0", this)
    , EICPresent_CPU2_VC0("EICPresent_CPU2_VC0", this)
    , EIC_RIPL_CPU2_VC0("EIC_RIPL_CPU2_VC0", this)
    , EIC_EICSS_CPU2_VC0("EIC_EICSS_CPU2_VC0", this)
    , EIC_VectorNum_CPU2_VC0("EIC_VectorNum_CPU2_VC0", this)
    , EIC_VectorOffset_CPU2_VC0("EIC_VectorOffset_CPU2_VC0", this)
    , EIC_GID_CPU2_VC0("EIC_GID_CPU2_VC0", this)
    , intISS_CPU2_VC0("intISS_CPU2_VC0", this)
    , causeTI_CPU2_VC0("causeTI_CPU2_VC0", this)
    , causeIP0_CPU2_VC0("causeIP0_CPU2_VC0", this)
    , causeIP1_CPU2_VC0("causeIP1_CPU2_VC0", this)
    , Guest_EIC_RIPL_CPU2_VC0("Guest.EIC_RIPL_CPU2_VC0", this)
    , Guest_EIC_EICSS_CPU2_VC0("Guest.EIC_EICSS_CPU2_VC0", this)
    , Guest_EIC_VectorNum_CPU2_VC0("Guest.EIC_VectorNum_CPU2_VC0", this)
    , Guest_EIC_VectorOffset_CPU2_VC0("Guest.EIC_VectorOffset_CPU2_VC0", this)
    , Guest_EIC_GID_CPU2_VC0("Guest.EIC_GID_CPU2_VC0", this)
    , Guest_intISS_CPU2_VC0("Guest.intISS_CPU2_VC0", this)
    , Guest_causeTI_CPU2_VC0("Guest.causeTI_CPU2_VC0", this)
    , Guest_causeIP0_CPU2_VC0("Guest.causeIP0_CPU2_VC0", this)
    , Guest_causeIP1_CPU2_VC0("Guest.causeIP1_CPU2_VC0", this)
    , dint_CPU2_VC1("dint_CPU2_VC1", this)
    , hwint0_CPU2_VC1("hwint0_CPU2_VC1", this)
    , hwint1_CPU2_VC1("hwint1_CPU2_VC1", this)
    , hwint2_CPU2_VC1("hwint2_CPU2_VC1", this)
    , hwint3_CPU2_VC1("hwint3_CPU2_VC1", this)
    , hwint4_CPU2_VC1("hwint4_CPU2_VC1", this)
    , hwint5_CPU2_VC1("hwint5_CPU2_VC1", this)
    , nmi_CPU2_VC1("nmi_CPU2_VC1", this)
    , EICPresent_CPU2_VC1("EICPresent_CPU2_VC1", this)
    , EIC_RIPL_CPU2_VC1("EIC_RIPL_CPU2_VC1", this)
    , EIC_EICSS_CPU2_VC1("EIC_EICSS_CPU2_VC1", this)
    , EIC_VectorNum_CPU2_VC1("EIC_VectorNum_CPU2_VC1", this)
    , EIC_VectorOffset_CPU2_VC1("EIC_VectorOffset_CPU2_VC1", this)
    , EIC_GID_CPU2_VC1("EIC_GID_CPU2_VC1", this)
    , intISS_CPU2_VC1("intISS_CPU2_VC1", this)
    , causeTI_CPU2_VC1("causeTI_CPU2_VC1", this)
    , causeIP0_CPU2_VC1("causeIP0_CPU2_VC1", this)
    , causeIP1_CPU2_VC1("causeIP1_CPU2_VC1", this)
    , Guest_EIC_RIPL_CPU2_VC1("Guest.EIC_RIPL_CPU2_VC1", this)
    , Guest_EIC_EICSS_CPU2_VC1("Guest.EIC_EICSS_CPU2_VC1", this)
    , Guest_EIC_VectorNum_CPU2_VC1("Guest.EIC_VectorNum_CPU2_VC1", this)
    , Guest_EIC_VectorOffset_CPU2_VC1("Guest.EIC_VectorOffset_CPU2_VC1", this)
    , Guest_EIC_GID_CPU2_VC1("Guest.EIC_GID_CPU2_VC1", this)
    , Guest_intISS_CPU2_VC1("Guest.intISS_CPU2_VC1", this)
    , Guest_causeTI_CPU2_VC1("Guest.causeTI_CPU2_VC1", this)
    , Guest_causeIP0_CPU2_VC1("Guest.causeIP0_CPU2_VC1", this)
    , Guest_causeIP1_CPU2_VC1("Guest.causeIP1_CPU2_VC1", this)
    , dint_CPU3_VC0("dint_CPU3_VC0", this)
    , hwint0_CPU3_VC0("hwint0_CPU3_VC0", this)
    , hwint1_CPU3_VC0("hwint1_CPU3_VC0", this)
    , hwint2_CPU3_VC0("hwint2_CPU3_VC0", this)
    , hwint3_CPU3_VC0("hwint3_CPU3_VC0", this)
    , hwint4_CPU3_VC0("hwint4_CPU3_VC0", this)
    , hwint5_CPU3_VC0("hwint5_CPU3_VC0", this)
    , nmi_CPU3_VC0("nmi_CPU3_VC0", this)
    , EICPresent_CPU3_VC0("EICPresent_CPU3_VC0", this)
    , EIC_RIPL_CPU3_VC0("EIC_RIPL_CPU3_VC0", this)
    , EIC_EICSS_CPU3_VC0("EIC_EICSS_CPU3_VC0", this)
    , EIC_VectorNum_CPU3_VC0("EIC_VectorNum_CPU3_VC0", this)
    , EIC_VectorOffset_CPU3_VC0("EIC_VectorOffset_CPU3_VC0", this)
    , EIC_GID_CPU3_VC0("EIC_GID_CPU3_VC0", this)
    , intISS_CPU3_VC0("intISS_CPU3_VC0", this)
    , causeTI_CPU3_VC0("causeTI_CPU3_VC0", this)
    , causeIP0_CPU3_VC0("causeIP0_CPU3_VC0", this)
    , causeIP1_CPU3_VC0("causeIP1_CPU3_VC0", this)
    , Guest_EIC_RIPL_CPU3_VC0("Guest.EIC_RIPL_CPU3_VC0", this)
    , Guest_EIC_EICSS_CPU3_VC0("Guest.EIC_EICSS_CPU3_VC0", this)
    , Guest_EIC_VectorNum_CPU3_VC0("Guest.EIC_VectorNum_CPU3_VC0", this)
    , Guest_EIC_VectorOffset_CPU3_VC0("Guest.EIC_VectorOffset_CPU3_VC0", this)
    , Guest_EIC_GID_CPU3_VC0("Guest.EIC_GID_CPU3_VC0", this)
    , Guest_intISS_CPU3_VC0("Guest.intISS_CPU3_VC0", this)
    , Guest_causeTI_CPU3_VC0("Guest.causeTI_CPU3_VC0", this)
    , Guest_causeIP0_CPU3_VC0("Guest.causeIP0_CPU3_VC0", this)
    , Guest_causeIP1_CPU3_VC0("Guest.causeIP1_CPU3_VC0", this)
    , dint_CPU3_VC1("dint_CPU3_VC1", this)
    , hwint0_CPU3_VC1("hwint0_CPU3_VC1", this)
    , hwint1_CPU3_VC1("hwint1_CPU3_VC1", this)
    , hwint2_CPU3_VC1("hwint2_CPU3_VC1", this)
    , hwint3_CPU3_VC1("hwint3_CPU3_VC1", this)
    , hwint4_CPU3_VC1("hwint4_CPU3_VC1", this)
    , hwint5_CPU3_VC1("hwint5_CPU3_VC1", this)
    , nmi_CPU3_VC1("nmi_CPU3_VC1", this)
    , EICPresent_CPU3_VC1("EICPresent_CPU3_VC1", this)
    , EIC_RIPL_CPU3_VC1("EIC_RIPL_CPU3_VC1", this)
    , EIC_EICSS_CPU3_VC1("EIC_EICSS_CPU3_VC1", this)
    , EIC_VectorNum_CPU3_VC1("EIC_VectorNum_CPU3_VC1", this)
    , EIC_VectorOffset_CPU3_VC1("EIC_VectorOffset_CPU3_VC1", this)
    , EIC_GID_CPU3_VC1("EIC_GID_CPU3_VC1", this)
    , intISS_CPU3_VC1("intISS_CPU3_VC1", this)
    , causeTI_CPU3_VC1("causeTI_CPU3_VC1", this)
    , causeIP0_CPU3_VC1("causeIP0_CPU3_VC1", this)
    , causeIP1_CPU3_VC1("causeIP1_CPU3_VC1", this)
    , Guest_EIC_RIPL_CPU3_VC1("Guest.EIC_RIPL_CPU3_VC1", this)
    , Guest_EIC_EICSS_CPU3_VC1("Guest.EIC_EICSS_CPU3_VC1", this)
    , Guest_EIC_VectorNum_CPU3_VC1("Guest.EIC_VectorNum_CPU3_VC1", this)
    , Guest_EIC_VectorOffset_CPU3_VC1("Guest.EIC_VectorOffset_CPU3_VC1", this)
    , Guest_EIC_GID_CPU3_VC1("Guest.EIC_GID_CPU3_VC1", this)
    , Guest_intISS_CPU3_VC1("Guest.intISS_CPU3_VC1", this)
    , Guest_causeTI_CPU3_VC1("Guest.causeTI_CPU3_VC1", this)
    , Guest_causeIP0_CPU3_VC1("Guest.causeIP0_CPU3_VC1", this)
    , Guest_causeIP1_CPU3_VC1("Guest.causeIP1_CPU3_VC1", this)
    {
    }

    void before_end_of_elaboration() {
        DATA.bindIfNotBound();
    }

    void dmi(bool on) {
        m_dmi = on;
        if(!on) {
            INSTRUCTION.invalidateDMI();
            DATA.invalidateDMI();
        }
    }
}; /* class mips64_I6400 */

#endif
