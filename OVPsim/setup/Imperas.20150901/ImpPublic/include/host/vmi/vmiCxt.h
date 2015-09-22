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
/*            A B S T R A C T   C O N T E X T   R O U T I N E S               */
/*                                                                            */
/******************************************************************************/

#ifndef VMI_CXT_H
#define VMI_CXT_H

#include "vmi/simAddrTypes.h"
#include "vmi/vmiTypes.h"
#include "vmi/vmiTyperefs.h"


////////////////////////////////////////////////////////////////////////////////
// CPU-MODEL-TO-CONTEXT CALLBACKS
////////////////////////////////////////////////////////////////////////////////

//
// Utility functions for 1, 2, 4 and 8 byte code fetches from the passed address
// The result is read using the current processor endianness
//
Uns8  vmicxtFetch1Byte(vmiProcessorP processor, Addr simAddress);
Uns16 vmicxtFetch2Byte(vmiProcessorP processor, Addr simAddress);
Uns32 vmicxtFetch4Byte(vmiProcessorP processor, Addr simAddress);
Uns64 vmicxtFetch8Byte(vmiProcessorP processor, Addr simAddress);

#endif
