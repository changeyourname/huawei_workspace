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
//    Master Port mp1
//    Slave Port sp1

#ifndef OVPWORLD_ORG_MMC_WT_1WAY_32BYTELINE_2048TAGS__1_0
#define OVPWORLD_ORG_MMC_WT_1WAY_32BYTELINE_2048TAGS__1_0
#include "ovpworld.org/modelSupport/tlmMMC/1.0/tlm2.0/tlmMmc.hpp"
using namespace sc_core;

class wt_1way_32byteline_2048tags : public icmMMC
{
  private:
    const char *getModel() {
        return icmGetVlnvString (NULL, "ovpworld.org", "mmc", "wt_1way_32byteline_2048tags", "1.0", "model");
    }

  public:
    icmMMCSlavePort sp1;
    icmMMCMasterPort mp1;

    wt_1way_32byteline_2048tags(sc_module_name name, icmAttrListObject *initialAttrs = 0 )
        : icmMMC(name, getModel(), 0, initialAttrs)
        , sp1(this, "sp1", 0xffffffff)
        , mp1(this, "mp1", 32)
    {
    }

}; /* class wt_1way_32byteline_2048tags */

#endif
