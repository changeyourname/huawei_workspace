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


#ifndef ICMTEXT_H
#define ICMTEXT_H

#include "icmTypes.h"

/// Call this function during exit.
/// @param cb Function to be called (may be more than one).

void icmAtExit (
    icmExitFn cb
);

/// Print the simulator banner (unless --nobanner is specified).

void icmBanner (void);

/// Returns how many errors have been reported so far.
/// @return Number of errors reported by icmMessage(E).

Uns32 icmErrors (void);

/// Use this in place of exit().
/// @param exitCode Process exit code.

void icmExitSimulation (
    Uns32 exitCode
);

/// Turn off messages with an ident beginning with the passed string.
/// @param ident The start of the ident to be turned off. e.g. ICM_ turns off
///              messages beginning ICM_.

void icmIgnoreMessage (
    const char* ident
);

/// Returns the last message to occur.
/// @return String or empty string.

const char* icmLastMessage (void);

/// Send formatted text to the simulator output stream. The text is prefixed
/// with the severity, the prefix code and the model instance name. Use this for
/// user-level diagnostics.
/// @param severity I=Info W=Warning E=Error F=Fatal (aborts the simulator).
/// @param ident    A short code to identify this message. This makes the
///                 message easy to extract using text tools.
/// @param fmt      Printf format string (see gnu printf for details).
/// @param ...      This is a vararg function.

void icmMessage (
    const char* severity,
    const char* ident,
    const char* fmt,
                ...
) __attribute__(( format (printf, 3,4)));

/// Use this to respond to the simulator -verbose flag.
/// @return True if platform should be verbose.

Bool icmMessageQuiet (void);

/// Turn warning messages on/off.
/// @return old value.
/// @param quiet Warning messages on.

Bool icmMessageSetNoWarn (
    Bool quiet
);

/// Turn Info messages on/off.
/// @return old value.
/// @param quiet Info messages on.

Bool icmMessageSetQuiet (
    Bool quiet
);

/// Use this to respond to the simulator -verbose flag.
/// @return True if platform should be verbose.

Bool icmMessageVerbose (void);

/// Return the state of the --nobanner flag.
/// @return Returns true if no banner should be printed.

Bool icmNoBanner (void);

/// Send formatted text to the simulator output stream. This sends output to the
/// simulator log without any prepended data. Only use this to produce tables,
/// xml or data of your own format.
/// @param fmt Printf format string (see gnu printf for details).
/// @param ... This is a vararg function.

void icmPrintf (
    const char* fmt,
                ...
) __attribute__((format (printf, 1,2)));

/// Reset the error count.
/// @param old Old error count.

void icmResetErrors (
    Uns32 old
);

/// Call this function to intercept all text output from the simulator.
/// @param outputcb The text output function.
/// @param quitcb   Function to quit the simulator.
/// @param userData Pass this in the userData argument.

void icmSetTextOutputFn (
    icmTextOutputFn outputcb,
    icmQuitFn       quitcb,
    void*           userData
);

/// As for icmVMessage, but does not return. Use for internal errors.
/// @param ident A short code to identify this message.
/// @param fmt   Printf format string (see gnu printf for details).
/// @param ap    Varargs list.

void icmVAbort (
    const char* ident,
    const char* fmt,
    va_list     ap
);

/// As for icmMessage, but using a va_list.
/// @param severity I=Info W=Warning E=Error F=Fatal (aborts the simulator).
/// @param ident    A short code to identify this message. This makes the
///                 message easy to extract using text tools.
/// @param fmt      Printf format string (see gnu printf for details).
/// @param ap       Varargs list.

void icmVMessage (
    const char* severity,
    const char* ident,
    const char* fmt,
    va_list     ap
);

/// Send formatted text to the simulator output stream.
/// @param fmt Printf format string (see gnu printf for details).
/// @param ap  Varargs list header.

void icmVPrintf (
    const char* fmt,
    va_list     ap
);


#endif /* ICMTEXT_H */

