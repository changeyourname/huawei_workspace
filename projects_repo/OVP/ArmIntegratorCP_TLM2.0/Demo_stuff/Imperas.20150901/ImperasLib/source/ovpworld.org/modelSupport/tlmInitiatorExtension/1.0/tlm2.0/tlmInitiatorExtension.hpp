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


#ifndef __TLM_INITIATOR_EXTENSION_H__
#define __TLM_INITIATOR_EXTENSION_H__

#include "tlm.h"

class icmInitiatorExtension: public tlm::tlm_extension<icmInitiatorExtension> {
public:

    /// constructor
    icmInitiatorExtension() {}

    /// destructor
    ~icmInitiatorExtension() {}

    /// copy
    void copy_from(const tlm_extension_base &extension) {
        m_initiator = static_cast<icmInitiatorExtension const &>(extension).m_initiator;
    }

    /// clone
    tlm::tlm_extension_base* clone() const {
        return new icmInitiatorExtension(*this);
    }

    // member variables
    void *m_initiator;
};

#endif
