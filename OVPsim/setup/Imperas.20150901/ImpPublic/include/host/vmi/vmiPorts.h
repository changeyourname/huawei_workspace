/*
 *
 * Copyright (c) 2005-2015 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License Agreement
 * that you accepted before downloading this file.
 *
 * This header forms part of the Software but may be included and used unaltered
 * in derivative works.
 *
 * For more information, please visit www.OVPworld.org or www.imperas.com
 */

/******************************************************************************/
/*                                                                            */
/*            V I R T U A L   M A C H I N E   I N T E R F A C E               */
/*                                                                            */
/*                              P O R T S                                     */
/*                                                                            */
/******************************************************************************/

#ifndef VMI_PORTS_H
#define VMI_PORTS_H

#include "vmi/vmiTypes.h"
#include "vmi/vmiTyperefs.h"
#include "hostapi/impTypes.h"

//
// Bus-port types
//
typedef enum vmiBusPortTypeE {
    vmi_BP_MASTER,
    vmi_BP_SLAVE,
    vmi_BP_MASTER_SLAVE
} vmiBusPortType;

typedef enum vmiDomainTypeE {
    vmi_DOM_CODE,     // code domain port
    vmi_DOM_DATA,     // data domain port
    vmi_DOM_OTHER     // other domain port
} vmiDomainType;

typedef struct vmiBusPortS {

    const char      *name;
    vmiBusPortType   type;
    vmiDomainType    domainType;
    struct           {Uns8 min; Uns8 max; Uns8 unset;} addrBits;
    Bool             mustBeConnected;

    // space for documentation
    const char      *description;
    void            *descriptionDom;

    // domain is non-NULL if port is connected
    memDomainP       domain;

} vmiBusPort;

#define VMI_BUS_PORT_SPECS_FN(_NAME) vmiBusPortP _NAME ( \
    vmiProcessorP processor,    \
    vmiBusPortP   prev          \
)

typedef VMI_BUS_PORT_SPECS_FN((*vmiBusPortSpecsFn));

#define VMI_END_BUS_PORTS {0}

//
// Get the memory domain (if any) from a bus port
//
inline static memDomainP vmirtGetBusPortDomain(
    vmiProcessorP processor,
    vmiBusPortP   busPort
) {
    return busPort->domain;
}

//
// Net-port types
//
typedef enum vmiNetPortTypeE {
    vmi_NP_INPUT,
    vmi_NP_OUTPUT,
    vmi_NP_INOUT
} vmiNetPortType;

typedef struct vmiNetPortS {

    const char      *name;
    vmiNetPortType   type;
    void            *userData;

    // callback for input or I/O net change
    vmiNetChangeFn   netChangeCB;
    Uns32           *handle;

    // space for documentation
    const char      *description;
    void            *descriptionDom;

    Bool            mustBeConnected;

} vmiNetPort;

#define VMI_NET_PORT_SPECS_FN(_NAME) vmiNetPortP _NAME ( \
    vmiProcessorP processor,    \
    vmiNetPortP   prev          \
)

typedef VMI_NET_PORT_SPECS_FN((*vmiNetPortSpecsFn));

#define VMI_END_NET_PORTS {0}


//
// Fifo-port types
//
typedef enum vmiFifoPortTypeE {
    vmi_FIFO_INPUT,
    vmi_FIFO_OUTPUT
} vmiFifoPortType;

typedef struct vmiFifoPortS {

    const char      *name;
    vmiFifoPortType  type;
    Uns32            bits;
    void           **handle;
    void            *userData;

    // space for documentation
    const char      *description;
    void            *descriptionDom;

} vmiFifoPort;

#define VMI_FIFO_PORT_SPECS_FN(_NAME) vmiFifoPortP _NAME ( \
    vmiProcessorP processor,    \
    vmiFifoPortP  prev          \
)

typedef VMI_FIFO_PORT_SPECS_FN((*vmiFifoPortSpecsFn));

#define VMI_END_FIFO_PORTS {0}

#endif

