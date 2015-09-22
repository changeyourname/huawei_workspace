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

#ifndef IMGTEC_OVPWORLD_ORG_PROCESSOR_MIPS32_P5600__1_0
#define IMGTEC_OVPWORLD_ORG_PROCESSOR_MIPS32_P5600__1_0

#include "ovpworld.org/modelSupport/tlmProcessor/1.0/tlm2.0/tlmProcessor.hpp"
using namespace sc_core;

class mips32_P5600 : public icmCpu
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "imgtec.ovpworld.org", "processor", "mips32", "1.0", "model");
    }

    const char *getSHL() {
        return icmGetVlnvString (NULL, "mips.ovpworld.org", "semihosting", "mips32SDE", "1.0", "model");
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
    icmCpuInterrupt      reset_CPU0;
    icmCpuInterrupt      hwint0_CPU0;
    icmCpuInterrupt      hwint1_CPU0;
    icmCpuInterrupt      hwint2_CPU0;
    icmCpuInterrupt      hwint3_CPU0;
    icmCpuInterrupt      hwint4_CPU0;
    icmCpuInterrupt      hwint5_CPU0;
    icmCpuInterrupt      nmi_CPU0;
    icmCpuInterrupt      EICPresent_CPU0;
    icmCpuInterrupt      EIC_RIPL_CPU0;
    icmCpuInterrupt      EIC_EICSS_CPU0;
    icmCpuInterrupt      EIC_VectorNum_CPU0;
    icmCpuInterrupt      EIC_VectorOffset_CPU0;
    icmCpuInterrupt      EIC_GID_CPU0;
    icmCpuOutputNetPort  intISS_CPU0;
    icmCpuOutputNetPort  causeTI_CPU0;
    icmCpuOutputNetPort  causeIP0_CPU0;
    icmCpuOutputNetPort  causeIP1_CPU0;
    icmCpuInterrupt      hwint0;
    icmCpuInterrupt      Guest_EIC_RIPL_CPU0;
    icmCpuInterrupt      Guest_EIC_EICSS_CPU0;
    icmCpuInterrupt      Guest_EIC_VectorNum_CPU0;
    icmCpuInterrupt      Guest_EIC_VectorOffset_CPU0;
    icmCpuInterrupt      Guest_EIC_GID_CPU0;
    icmCpuOutputNetPort  Guest_intISS_CPU0;
    icmCpuOutputNetPort  Guest_causeTI_CPU0;
    icmCpuOutputNetPort  Guest_causeIP0_CPU0;
    icmCpuOutputNetPort  Guest_causeIP1_CPU0;
    icmCpuInterrupt      reset_CPU1;
    icmCpuInterrupt      hwint0_CPU1;
    icmCpuInterrupt      hwint1_CPU1;
    icmCpuInterrupt      hwint2_CPU1;
    icmCpuInterrupt      hwint3_CPU1;
    icmCpuInterrupt      hwint4_CPU1;
    icmCpuInterrupt      hwint5_CPU1;
    icmCpuInterrupt      nmi_CPU1;
    icmCpuInterrupt      EICPresent_CPU1;
    icmCpuInterrupt      EIC_RIPL_CPU1;
    icmCpuInterrupt      EIC_EICSS_CPU1;
    icmCpuInterrupt      EIC_VectorNum_CPU1;
    icmCpuInterrupt      EIC_VectorOffset_CPU1;
    icmCpuInterrupt      EIC_GID_CPU1;
    icmCpuOutputNetPort  intISS_CPU1;
    icmCpuOutputNetPort  causeTI_CPU1;
    icmCpuOutputNetPort  causeIP0_CPU1;
    icmCpuOutputNetPort  causeIP1_CPU1;
    icmCpuInterrupt      Guest_EIC_RIPL_CPU1;
    icmCpuInterrupt      Guest_EIC_EICSS_CPU1;
    icmCpuInterrupt      Guest_EIC_VectorNum_CPU1;
    icmCpuInterrupt      Guest_EIC_VectorOffset_CPU1;
    icmCpuInterrupt      Guest_EIC_GID_CPU1;
    icmCpuOutputNetPort  Guest_intISS_CPU1;
    icmCpuOutputNetPort  Guest_causeTI_CPU1;
    icmCpuOutputNetPort  Guest_causeIP0_CPU1;
    icmCpuOutputNetPort  Guest_causeIP1_CPU1;
    icmCpuInterrupt      reset_CPU2;
    icmCpuInterrupt      hwint0_CPU2;
    icmCpuInterrupt      hwint1_CPU2;
    icmCpuInterrupt      hwint2_CPU2;
    icmCpuInterrupt      hwint3_CPU2;
    icmCpuInterrupt      hwint4_CPU2;
    icmCpuInterrupt      hwint5_CPU2;
    icmCpuInterrupt      nmi_CPU2;
    icmCpuInterrupt      EICPresent_CPU2;
    icmCpuInterrupt      EIC_RIPL_CPU2;
    icmCpuInterrupt      EIC_EICSS_CPU2;
    icmCpuInterrupt      EIC_VectorNum_CPU2;
    icmCpuInterrupt      EIC_VectorOffset_CPU2;
    icmCpuInterrupt      EIC_GID_CPU2;
    icmCpuOutputNetPort  intISS_CPU2;
    icmCpuOutputNetPort  causeTI_CPU2;
    icmCpuOutputNetPort  causeIP0_CPU2;
    icmCpuOutputNetPort  causeIP1_CPU2;
    icmCpuInterrupt      Guest_EIC_RIPL_CPU2;
    icmCpuInterrupt      Guest_EIC_EICSS_CPU2;
    icmCpuInterrupt      Guest_EIC_VectorNum_CPU2;
    icmCpuInterrupt      Guest_EIC_VectorOffset_CPU2;
    icmCpuInterrupt      Guest_EIC_GID_CPU2;
    icmCpuOutputNetPort  Guest_intISS_CPU2;
    icmCpuOutputNetPort  Guest_causeTI_CPU2;
    icmCpuOutputNetPort  Guest_causeIP0_CPU2;
    icmCpuOutputNetPort  Guest_causeIP1_CPU2;
    icmCpuInterrupt      reset_CPU3;
    icmCpuInterrupt      hwint0_CPU3;
    icmCpuInterrupt      hwint1_CPU3;
    icmCpuInterrupt      hwint2_CPU3;
    icmCpuInterrupt      hwint3_CPU3;
    icmCpuInterrupt      hwint4_CPU3;
    icmCpuInterrupt      hwint5_CPU3;
    icmCpuInterrupt      nmi_CPU3;
    icmCpuInterrupt      EICPresent_CPU3;
    icmCpuInterrupt      EIC_RIPL_CPU3;
    icmCpuInterrupt      EIC_EICSS_CPU3;
    icmCpuInterrupt      EIC_VectorNum_CPU3;
    icmCpuInterrupt      EIC_VectorOffset_CPU3;
    icmCpuInterrupt      EIC_GID_CPU3;
    icmCpuOutputNetPort  intISS_CPU3;
    icmCpuOutputNetPort  causeTI_CPU3;
    icmCpuOutputNetPort  causeIP0_CPU3;
    icmCpuOutputNetPort  causeIP1_CPU3;
    icmCpuInterrupt      Guest_EIC_RIPL_CPU3;
    icmCpuInterrupt      Guest_EIC_EICSS_CPU3;
    icmCpuInterrupt      Guest_EIC_VectorNum_CPU3;
    icmCpuInterrupt      Guest_EIC_VectorOffset_CPU3;
    icmCpuInterrupt      Guest_EIC_GID_CPU3;
    icmCpuOutputNetPort  Guest_intISS_CPU3;
    icmCpuOutputNetPort  Guest_causeTI_CPU3;
    icmCpuOutputNetPort  Guest_causeIP0_CPU3;
    icmCpuOutputNetPort  Guest_causeIP1_CPU3;

    mips32_P5600(
        sc_module_name        name,
        const unsigned int    ID,
        icmNewProcAttrs       attrs        = ICM_ATTR_DEFAULT,
        icmAttrListObject    *attrList    = NULL,
        const char           *semiHost    = NULL,
        Uns32                 addressBits = 32,
        bool                  dmi         = true,
        Uns32                 cpuFlags    = 0
     )
    : icmCpu(name, ID, "mips32", getModel(), 0, semiHost ? ((0 == strlen(semiHost)) ? 0 : semiHost) : getSHL(), attrs, attrList, addressBits, dmi, cpuFlags)
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
    , reset_CPU0("reset_CPU0", this)
    , hwint0_CPU0("hwint0_CPU0", this)
    , hwint1_CPU0("hwint1_CPU0", this)
    , hwint2_CPU0("hwint2_CPU0", this)
    , hwint3_CPU0("hwint3_CPU0", this)
    , hwint4_CPU0("hwint4_CPU0", this)
    , hwint5_CPU0("hwint5_CPU0", this)
    , nmi_CPU0("nmi_CPU0", this)
    , EICPresent_CPU0("EICPresent_CPU0", this)
    , EIC_RIPL_CPU0("EIC_RIPL_CPU0", this)
    , EIC_EICSS_CPU0("EIC_EICSS_CPU0", this)
    , EIC_VectorNum_CPU0("EIC_VectorNum_CPU0", this)
    , EIC_VectorOffset_CPU0("EIC_VectorOffset_CPU0", this)
    , EIC_GID_CPU0("EIC_GID_CPU0", this)
    , intISS_CPU0("intISS_CPU0", this)
    , causeTI_CPU0("causeTI_CPU0", this)
    , causeIP0_CPU0("causeIP0_CPU0", this)
    , causeIP1_CPU0("causeIP1_CPU0", this)
    , hwint0("hwint0", this)
    , Guest_EIC_RIPL_CPU0("Guest.EIC_RIPL_CPU0", this)
    , Guest_EIC_EICSS_CPU0("Guest.EIC_EICSS_CPU0", this)
    , Guest_EIC_VectorNum_CPU0("Guest.EIC_VectorNum_CPU0", this)
    , Guest_EIC_VectorOffset_CPU0("Guest.EIC_VectorOffset_CPU0", this)
    , Guest_EIC_GID_CPU0("Guest.EIC_GID_CPU0", this)
    , Guest_intISS_CPU0("Guest.intISS_CPU0", this)
    , Guest_causeTI_CPU0("Guest.causeTI_CPU0", this)
    , Guest_causeIP0_CPU0("Guest.causeIP0_CPU0", this)
    , Guest_causeIP1_CPU0("Guest.causeIP1_CPU0", this)
    , reset_CPU1("reset_CPU1", this)
    , hwint0_CPU1("hwint0_CPU1", this)
    , hwint1_CPU1("hwint1_CPU1", this)
    , hwint2_CPU1("hwint2_CPU1", this)
    , hwint3_CPU1("hwint3_CPU1", this)
    , hwint4_CPU1("hwint4_CPU1", this)
    , hwint5_CPU1("hwint5_CPU1", this)
    , nmi_CPU1("nmi_CPU1", this)
    , EICPresent_CPU1("EICPresent_CPU1", this)
    , EIC_RIPL_CPU1("EIC_RIPL_CPU1", this)
    , EIC_EICSS_CPU1("EIC_EICSS_CPU1", this)
    , EIC_VectorNum_CPU1("EIC_VectorNum_CPU1", this)
    , EIC_VectorOffset_CPU1("EIC_VectorOffset_CPU1", this)
    , EIC_GID_CPU1("EIC_GID_CPU1", this)
    , intISS_CPU1("intISS_CPU1", this)
    , causeTI_CPU1("causeTI_CPU1", this)
    , causeIP0_CPU1("causeIP0_CPU1", this)
    , causeIP1_CPU1("causeIP1_CPU1", this)
    , Guest_EIC_RIPL_CPU1("Guest.EIC_RIPL_CPU1", this)
    , Guest_EIC_EICSS_CPU1("Guest.EIC_EICSS_CPU1", this)
    , Guest_EIC_VectorNum_CPU1("Guest.EIC_VectorNum_CPU1", this)
    , Guest_EIC_VectorOffset_CPU1("Guest.EIC_VectorOffset_CPU1", this)
    , Guest_EIC_GID_CPU1("Guest.EIC_GID_CPU1", this)
    , Guest_intISS_CPU1("Guest.intISS_CPU1", this)
    , Guest_causeTI_CPU1("Guest.causeTI_CPU1", this)
    , Guest_causeIP0_CPU1("Guest.causeIP0_CPU1", this)
    , Guest_causeIP1_CPU1("Guest.causeIP1_CPU1", this)
    , reset_CPU2("reset_CPU2", this)
    , hwint0_CPU2("hwint0_CPU2", this)
    , hwint1_CPU2("hwint1_CPU2", this)
    , hwint2_CPU2("hwint2_CPU2", this)
    , hwint3_CPU2("hwint3_CPU2", this)
    , hwint4_CPU2("hwint4_CPU2", this)
    , hwint5_CPU2("hwint5_CPU2", this)
    , nmi_CPU2("nmi_CPU2", this)
    , EICPresent_CPU2("EICPresent_CPU2", this)
    , EIC_RIPL_CPU2("EIC_RIPL_CPU2", this)
    , EIC_EICSS_CPU2("EIC_EICSS_CPU2", this)
    , EIC_VectorNum_CPU2("EIC_VectorNum_CPU2", this)
    , EIC_VectorOffset_CPU2("EIC_VectorOffset_CPU2", this)
    , EIC_GID_CPU2("EIC_GID_CPU2", this)
    , intISS_CPU2("intISS_CPU2", this)
    , causeTI_CPU2("causeTI_CPU2", this)
    , causeIP0_CPU2("causeIP0_CPU2", this)
    , causeIP1_CPU2("causeIP1_CPU2", this)
    , Guest_EIC_RIPL_CPU2("Guest.EIC_RIPL_CPU2", this)
    , Guest_EIC_EICSS_CPU2("Guest.EIC_EICSS_CPU2", this)
    , Guest_EIC_VectorNum_CPU2("Guest.EIC_VectorNum_CPU2", this)
    , Guest_EIC_VectorOffset_CPU2("Guest.EIC_VectorOffset_CPU2", this)
    , Guest_EIC_GID_CPU2("Guest.EIC_GID_CPU2", this)
    , Guest_intISS_CPU2("Guest.intISS_CPU2", this)
    , Guest_causeTI_CPU2("Guest.causeTI_CPU2", this)
    , Guest_causeIP0_CPU2("Guest.causeIP0_CPU2", this)
    , Guest_causeIP1_CPU2("Guest.causeIP1_CPU2", this)
    , reset_CPU3("reset_CPU3", this)
    , hwint0_CPU3("hwint0_CPU3", this)
    , hwint1_CPU3("hwint1_CPU3", this)
    , hwint2_CPU3("hwint2_CPU3", this)
    , hwint3_CPU3("hwint3_CPU3", this)
    , hwint4_CPU3("hwint4_CPU3", this)
    , hwint5_CPU3("hwint5_CPU3", this)
    , nmi_CPU3("nmi_CPU3", this)
    , EICPresent_CPU3("EICPresent_CPU3", this)
    , EIC_RIPL_CPU3("EIC_RIPL_CPU3", this)
    , EIC_EICSS_CPU3("EIC_EICSS_CPU3", this)
    , EIC_VectorNum_CPU3("EIC_VectorNum_CPU3", this)
    , EIC_VectorOffset_CPU3("EIC_VectorOffset_CPU3", this)
    , EIC_GID_CPU3("EIC_GID_CPU3", this)
    , intISS_CPU3("intISS_CPU3", this)
    , causeTI_CPU3("causeTI_CPU3", this)
    , causeIP0_CPU3("causeIP0_CPU3", this)
    , causeIP1_CPU3("causeIP1_CPU3", this)
    , Guest_EIC_RIPL_CPU3("Guest.EIC_RIPL_CPU3", this)
    , Guest_EIC_EICSS_CPU3("Guest.EIC_EICSS_CPU3", this)
    , Guest_EIC_VectorNum_CPU3("Guest.EIC_VectorNum_CPU3", this)
    , Guest_EIC_VectorOffset_CPU3("Guest.EIC_VectorOffset_CPU3", this)
    , Guest_EIC_GID_CPU3("Guest.EIC_GID_CPU3", this)
    , Guest_intISS_CPU3("Guest.intISS_CPU3", this)
    , Guest_causeTI_CPU3("Guest.causeTI_CPU3", this)
    , Guest_causeIP0_CPU3("Guest.causeIP0_CPU3", this)
    , Guest_causeIP1_CPU3("Guest.causeIP1_CPU3", this)
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
}; /* class mips32_P5600 */

#endif
