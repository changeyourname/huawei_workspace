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


#ifndef ICMSIMULATORSESSION_H
#define ICMSIMULATORSESSION_H

#include "icmTypes.h"

/// Set a seed for randomizing the order in which processors are processed a
/// time slice. The default is no randomization (seed=0).
/// @param lfsrSeed New seed.

void icmSetSimulationRandomSeed (
    Uns32 lfsrSeed
);

/// Set the simulation stop time (for icmSimulatePlatform) - takes effect at the
/// end of any current time slice. icmSimulatePlatform will return when this
/// stop time is reached.
/// @return True if successful.
/// @param newStopTime The new stop time (see icmTime).

Bool icmSetSimulationStopTime (
    icmTime newStopTime
);

/// Same as icmSetSimulationStopTime, accepting a double.
/// @return True if successful.
/// @param newStopTime The new stop time.

Bool icmSetSimulationStopTimeDouble (
    double newStopTime
);

/// Set the simulation time precision - all event times are rounded to this. Use
/// this if calling from MSVC.
/// @return True if successful.
/// @param precision The precision (see icmTime).

Bool icmSetSimulationTimePrecision (
    icmTime precision
);

/// Same as icmSetSimulationTimePrecision, accepting a double.
/// @return True if successful.
/// @param precision The precision (see icmTime).

Bool icmSetSimulationTimePrecisionDouble (
    double precision
);

/// Set the simulation time slice size (for icmSimulatePlatform) - takes effect
/// at the end of the current time slice.
/// @return True if successful.
/// @param newSliceSize The new slice duration (see icmTime).

Bool icmSetSimulationTimeSlice (
    icmTime newSliceSize
);

/// Same as icmSetSimulationTimeSlice, accepting a double. Use this if calling
/// from MSVC.
/// @return True if successful.
/// @param newSliceSize New slice duration.

Bool icmSetSimulationTimeSliceDouble (
    double newSliceSize
);

/// This specifies the maximum multiple of real time at which the simulation
/// should run. If this is not specified (and the ICM_WALLCLOCK attribute is not
/// specified) then the simulation will run as fast as possible. A value of 2.0
/// implies no faster than twice real time; a value of 0.5 implies no faster
/// than half real time. It may be necessary to specify this to keep interactive
/// prompts from going by too quickly or to get semi-hosted peripherals such as
/// UARTs or NICs to function properly.
/// @param factor Scale factor to apply.

void icmSetWallClockFactor (
    double factor
);


#endif /* ICMSIMULATORSESSION_H */

