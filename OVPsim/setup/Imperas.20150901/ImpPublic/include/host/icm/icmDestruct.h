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


#ifndef ICMDESTRUCT_H
#define ICMDESTRUCT_H

#include "icmTypes.h"

/// Free attributes list (call at end of simulation).
/// @param attrs The list to be freed.

void icmFreeAttrList (
    icmAttrListP attrs
);

/// Deprecated - Please use icmTerminate.
/// @param bus Bus object.

void icmFreeBus (
    icmBusP bus
);

/// Deprecated - Please use icmTerminate.
/// @param bridge The Bridge to Free.

void icmFreeBusBridge (
    icmBusBridgeP bridge
);

/// Deprecated - Please use icmTerminate.
/// @param fifo The FIFO object.

void icmFreeFifo (
    icmConnP fifo
);

/// Deprecated - Please use icmTerminate.
/// @param mmc The MMC to be freed.

void icmFreeMMC (
    icmMmcP mmc
);

/// Deprecated - Please use icmTerminate.
/// @param memory The memory object.

void icmFreeMemory (
    icmMemoryP memory
);

/// Deprecated - Please use icmTerminate.
/// @param net The net object to be freed.

void icmFreeNet (
    icmNetP net
);

/// Deprecated - Please use icmTerminate.
/// @param pse The PSE to be freed.

void icmFreePSE (
    icmPseP pse
);

/// Deprecated - Please use icmTerminate.
/// @param processor Processor to free.

void icmFreeProcessor (
    icmProcessorP processor
);


#endif /* ICMDESTRUCT_H */

