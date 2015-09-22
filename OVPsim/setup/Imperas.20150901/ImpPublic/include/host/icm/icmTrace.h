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


#ifndef ICMTRACE_H
#define ICMTRACE_H

#include "icmTypes.h"

/// Disable trace buffer for the passed processor.
/// @param processor Turn off trace buffer for this processor.

void icmDisableTraceBuffer (
    icmProcessorP processor
);

/// Dump the processor trace buffer.
/// @param processor The processor of interest.

void icmDumpTraceBuffer (
    icmProcessorP processor
);

/// Enable trace buffer for the passed processor The trace buffer records the
/// last few addresses the processor executed, so that when a problem occurs, a
/// short instruction history can be recovered.
/// @param processor Turn on trace buffer for this processor.

void icmEnableTraceBuffer (
    icmProcessorP processor
);

/// Disable tracing for the processor after 'iDelta' more instructions.
/// @param processor Turn off tracing for this processor.
/// @param iDelta    Number of instructions before tracing is turned off.

void icmTraceOffAfter (
    icmProcessorP processor,
    Uns64         iDelta
);

/// Enable tracing for the processor after 'iDelta' more instructions Tracing
/// causes a single line of text to be output (including a disassembly of the
/// current instruction). Note that global simulation attributes control the
/// amount of extra detail that are added to the trace. This can include
/// converting addresses to labels by looking in the object file, or giving a
/// complete register dump after each instruction.
/// @param processor Turn on tracing for this processor.
/// @param iDelta    Number of instructions before tracing is turned on.

void icmTraceOnAfter (
    icmProcessorP processor,
    Uns64         iDelta
);


#endif /* ICMTRACE_H */

