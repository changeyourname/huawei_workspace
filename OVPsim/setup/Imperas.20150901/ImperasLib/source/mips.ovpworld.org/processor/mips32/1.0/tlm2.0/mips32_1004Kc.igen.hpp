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

#ifndef MIPS_OVPWORLD_ORG_PROCESSOR_MIPS32_1004KC__1_0
#define MIPS_OVPWORLD_ORG_PROCESSOR_MIPS32_1004KC__1_0

#include "ovpworld.org/modelSupport/tlmProcessor/1.0/tlm2.0/tlmProcessor.hpp"
using namespace sc_core;

class mips32_1004Kc : public icmCpu
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "mips.ovpworld.org", "processor", "mips32", "1.0", "model");
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
    icmCpuInterrupt      yq_CPU0;
    icmCpuInterrupt      hwint0_CPU0_VPE0;
    icmCpuInterrupt      hwint1_CPU0_VPE0;
    icmCpuInterrupt      hwint2_CPU0_VPE0;
    icmCpuInterrupt      hwint3_CPU0_VPE0;
    icmCpuInterrupt      hwint4_CPU0_VPE0;
    icmCpuInterrupt      hwint5_CPU0_VPE0;
    icmCpuInterrupt      nmi_CPU0_VPE0;
    icmCpuInterrupt      hwint0;
    icmCpuInterrupt      hwint0_CPU0_VPE1;
    icmCpuInterrupt      hwint1_CPU0_VPE1;
    icmCpuInterrupt      hwint2_CPU0_VPE1;
    icmCpuInterrupt      hwint3_CPU0_VPE1;
    icmCpuInterrupt      hwint4_CPU0_VPE1;
    icmCpuInterrupt      hwint5_CPU0_VPE1;
    icmCpuInterrupt      nmi_CPU0_VPE1;
    icmCpuInterrupt      yq_CPU1;
    icmCpuInterrupt      hwint0_CPU1_VPE0;
    icmCpuInterrupt      hwint1_CPU1_VPE0;
    icmCpuInterrupt      hwint2_CPU1_VPE0;
    icmCpuInterrupt      hwint3_CPU1_VPE0;
    icmCpuInterrupt      hwint4_CPU1_VPE0;
    icmCpuInterrupt      hwint5_CPU1_VPE0;
    icmCpuInterrupt      nmi_CPU1_VPE0;
    icmCpuInterrupt      hwint0_CPU1_VPE1;
    icmCpuInterrupt      hwint1_CPU1_VPE1;
    icmCpuInterrupt      hwint2_CPU1_VPE1;
    icmCpuInterrupt      hwint3_CPU1_VPE1;
    icmCpuInterrupt      hwint4_CPU1_VPE1;
    icmCpuInterrupt      hwint5_CPU1_VPE1;
    icmCpuInterrupt      nmi_CPU1_VPE1;
    icmCpuInterrupt      yq_CPU2;
    icmCpuInterrupt      hwint0_CPU2_VPE0;
    icmCpuInterrupt      hwint1_CPU2_VPE0;
    icmCpuInterrupt      hwint2_CPU2_VPE0;
    icmCpuInterrupt      hwint3_CPU2_VPE0;
    icmCpuInterrupt      hwint4_CPU2_VPE0;
    icmCpuInterrupt      hwint5_CPU2_VPE0;
    icmCpuInterrupt      nmi_CPU2_VPE0;
    icmCpuInterrupt      hwint0_CPU2_VPE1;
    icmCpuInterrupt      hwint1_CPU2_VPE1;
    icmCpuInterrupt      hwint2_CPU2_VPE1;
    icmCpuInterrupt      hwint3_CPU2_VPE1;
    icmCpuInterrupt      hwint4_CPU2_VPE1;
    icmCpuInterrupt      hwint5_CPU2_VPE1;
    icmCpuInterrupt      nmi_CPU2_VPE1;
    icmCpuInterrupt      yq_CPU3;
    icmCpuInterrupt      hwint0_CPU3_VPE0;
    icmCpuInterrupt      hwint1_CPU3_VPE0;
    icmCpuInterrupt      hwint2_CPU3_VPE0;
    icmCpuInterrupt      hwint3_CPU3_VPE0;
    icmCpuInterrupt      hwint4_CPU3_VPE0;
    icmCpuInterrupt      hwint5_CPU3_VPE0;
    icmCpuInterrupt      nmi_CPU3_VPE0;
    icmCpuInterrupt      hwint0_CPU3_VPE1;
    icmCpuInterrupt      hwint1_CPU3_VPE1;
    icmCpuInterrupt      hwint2_CPU3_VPE1;
    icmCpuInterrupt      hwint3_CPU3_VPE1;
    icmCpuInterrupt      hwint4_CPU3_VPE1;
    icmCpuInterrupt      hwint5_CPU3_VPE1;
    icmCpuInterrupt      nmi_CPU3_VPE1;

    mips32_1004Kc(
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
    , INSTRUCTION (this, "INSTRUCTION", 32)
    , DATA (this, "DATA", 32)
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
    , yq_CPU0("yq_CPU0", this)
    , hwint0_CPU0_VPE0("hwint0_CPU0_VPE0", this)
    , hwint1_CPU0_VPE0("hwint1_CPU0_VPE0", this)
    , hwint2_CPU0_VPE0("hwint2_CPU0_VPE0", this)
    , hwint3_CPU0_VPE0("hwint3_CPU0_VPE0", this)
    , hwint4_CPU0_VPE0("hwint4_CPU0_VPE0", this)
    , hwint5_CPU0_VPE0("hwint5_CPU0_VPE0", this)
    , nmi_CPU0_VPE0("nmi_CPU0_VPE0", this)
    , hwint0("hwint0", this)
    , hwint0_CPU0_VPE1("hwint0_CPU0_VPE1", this)
    , hwint1_CPU0_VPE1("hwint1_CPU0_VPE1", this)
    , hwint2_CPU0_VPE1("hwint2_CPU0_VPE1", this)
    , hwint3_CPU0_VPE1("hwint3_CPU0_VPE1", this)
    , hwint4_CPU0_VPE1("hwint4_CPU0_VPE1", this)
    , hwint5_CPU0_VPE1("hwint5_CPU0_VPE1", this)
    , nmi_CPU0_VPE1("nmi_CPU0_VPE1", this)
    , yq_CPU1("yq_CPU1", this)
    , hwint0_CPU1_VPE0("hwint0_CPU1_VPE0", this)
    , hwint1_CPU1_VPE0("hwint1_CPU1_VPE0", this)
    , hwint2_CPU1_VPE0("hwint2_CPU1_VPE0", this)
    , hwint3_CPU1_VPE0("hwint3_CPU1_VPE0", this)
    , hwint4_CPU1_VPE0("hwint4_CPU1_VPE0", this)
    , hwint5_CPU1_VPE0("hwint5_CPU1_VPE0", this)
    , nmi_CPU1_VPE0("nmi_CPU1_VPE0", this)
    , hwint0_CPU1_VPE1("hwint0_CPU1_VPE1", this)
    , hwint1_CPU1_VPE1("hwint1_CPU1_VPE1", this)
    , hwint2_CPU1_VPE1("hwint2_CPU1_VPE1", this)
    , hwint3_CPU1_VPE1("hwint3_CPU1_VPE1", this)
    , hwint4_CPU1_VPE1("hwint4_CPU1_VPE1", this)
    , hwint5_CPU1_VPE1("hwint5_CPU1_VPE1", this)
    , nmi_CPU1_VPE1("nmi_CPU1_VPE1", this)
    , yq_CPU2("yq_CPU2", this)
    , hwint0_CPU2_VPE0("hwint0_CPU2_VPE0", this)
    , hwint1_CPU2_VPE0("hwint1_CPU2_VPE0", this)
    , hwint2_CPU2_VPE0("hwint2_CPU2_VPE0", this)
    , hwint3_CPU2_VPE0("hwint3_CPU2_VPE0", this)
    , hwint4_CPU2_VPE0("hwint4_CPU2_VPE0", this)
    , hwint5_CPU2_VPE0("hwint5_CPU2_VPE0", this)
    , nmi_CPU2_VPE0("nmi_CPU2_VPE0", this)
    , hwint0_CPU2_VPE1("hwint0_CPU2_VPE1", this)
    , hwint1_CPU2_VPE1("hwint1_CPU2_VPE1", this)
    , hwint2_CPU2_VPE1("hwint2_CPU2_VPE1", this)
    , hwint3_CPU2_VPE1("hwint3_CPU2_VPE1", this)
    , hwint4_CPU2_VPE1("hwint4_CPU2_VPE1", this)
    , hwint5_CPU2_VPE1("hwint5_CPU2_VPE1", this)
    , nmi_CPU2_VPE1("nmi_CPU2_VPE1", this)
    , yq_CPU3("yq_CPU3", this)
    , hwint0_CPU3_VPE0("hwint0_CPU3_VPE0", this)
    , hwint1_CPU3_VPE0("hwint1_CPU3_VPE0", this)
    , hwint2_CPU3_VPE0("hwint2_CPU3_VPE0", this)
    , hwint3_CPU3_VPE0("hwint3_CPU3_VPE0", this)
    , hwint4_CPU3_VPE0("hwint4_CPU3_VPE0", this)
    , hwint5_CPU3_VPE0("hwint5_CPU3_VPE0", this)
    , nmi_CPU3_VPE0("nmi_CPU3_VPE0", this)
    , hwint0_CPU3_VPE1("hwint0_CPU3_VPE1", this)
    , hwint1_CPU3_VPE1("hwint1_CPU3_VPE1", this)
    , hwint2_CPU3_VPE1("hwint2_CPU3_VPE1", this)
    , hwint3_CPU3_VPE1("hwint3_CPU3_VPE1", this)
    , hwint4_CPU3_VPE1("hwint4_CPU3_VPE1", this)
    , hwint5_CPU3_VPE1("hwint5_CPU3_VPE1", this)
    , nmi_CPU3_VPE1("nmi_CPU3_VPE1", this)
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
}; /* class mips32_1004Kc */

#endif