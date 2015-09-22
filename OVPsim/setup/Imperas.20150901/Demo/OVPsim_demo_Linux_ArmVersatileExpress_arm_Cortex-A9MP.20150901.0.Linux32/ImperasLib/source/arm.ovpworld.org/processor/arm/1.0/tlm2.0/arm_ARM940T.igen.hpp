/*
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * YOU MAY USE THE SOFTWARE SUBJECT TO THE LICENSE TERMS BELOW
 * PROVIDED THAT YOU ENSURE THAT THIS NOTICE IS REPLICATED UNMODIFIED
 * AND IN ITS ENTIRETY IN ALL DISTRIBUTIONS OF THE SOFTWARE,
 * MODIFIED OR UNMODIFIED, IN SOURCE CODE OR IN BINARY FORM.
 *
 * In respect of all models:
 *   The license shall not be construed as granting a license to create a hardware
 *   implementation of the functionality of the software licensed hereunder.
 *
 * In respect of ARM related models:
 *   The license below extends only for your use of the software for the sole
 *   purpose of designing, developing, analyzing, debugging, testing,
 *   verifying, validating and optimizing software which: (a) (i) is for ARM
 *   based systems; and (ii) does not incorporate the ARM Models or any part
 *   thereof; and (b) such ARM Models may not be used to emulate an ARM based
 *   system to run application software in a production or live environment.
 *
 *   The license does not entitle you to use the ARM models for evaluating
 *   the validity of any ARM patent.
 *
 * The license is non-exclusive, worldwide, non-transferable and revocable.
 *
 * Licensed under an Imperas Modified Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.ovpworld.org/licenses/OVP_MODIFIED_1.1_APACHE_OPEN_SOURCE_LICENSE_2.0.pdf
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

#ifndef ARM_OVPWORLD_ORG_PROCESSOR_ARM_ARM940T__1_0
#define ARM_OVPWORLD_ORG_PROCESSOR_ARM_ARM940T__1_0

#include "ovpworld.org/modelSupport/tlmProcessor/1.0/tlm2.0/tlmProcessor.hpp"
using namespace sc_core;

class arm_ARM940T : public icmCpu
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "arm.ovpworld.org", "processor", "arm", "1.0", "model");
    }

    const char *getSHL() {
        return icmGetVlnvString (NULL, "arm.ovpworld.org", "semihosting", "armNewlib", "1.0", "model");
    }

  public:
    icmCpuMasterPort     INSTRUCTION;
    icmCpuMasterPort     DATA;
    icmCpuInterrupt      reset;
    icmCpuInterrupt      fiq;
    icmCpuInterrupt      irq;

    arm_ARM940T(
        sc_module_name        name,
        const unsigned int    ID,
        icmNewProcAttrs       attrs        = ICM_ATTR_DEFAULT,
        icmAttrListObject    *attrList    = NULL,
        const char           *semiHost    = NULL,
        Uns32                 addressBits = 32,
        bool                  dmi         = true,
        Uns32                 cpuFlags    = 0
     )
    : icmCpu(name, ID, "arm", getModel(), 0, semiHost ? ((0 == strlen(semiHost)) ? 0 : semiHost) : getSHL(), attrs, attrList, addressBits, dmi, cpuFlags)
    , INSTRUCTION (this, "INSTRUCTION", 32)
    , DATA (this, "DATA", 32)
    , reset("reset", this)
    , fiq("fiq", this)
    , irq("irq", this)
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
}; /* class arm_ARM940T */

#endif
