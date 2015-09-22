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


#ifndef OPMMESSAGE_H
#define OPMMESSAGE_H

#include "optTypes.h"

/// Add to list of functions called when opmExit is called.
/// @param fn Function to be called.

void opmAtExit (
    optExitFn fn
);

/// Print the product banner (unless --nobanner is specified).

void opmBanner (void);

/// Return how many opmMessage(E) have occurred.
/// @return Number of errors to date.

Uns32 opmErrors (void);

/// Use this to exit the program instead of exit().
/// @param returnCode Program return code.

void opmExit (
    Uns32 returnCode
);

/// Returns the last message to occur.
/// @return String or empty string.

const char* opmLastMessage (void);

/// Send formatted text to the simulator output stream. The text is prefixed
/// with the severity, the prefix code and the model instance name. Use this for
/// user-level diagnostics.
/// @param severity I=Info, W=Warning, E=Error, F=Fatal (aborts the
///                 simulator).
/// @param ident    A short code to identify this message. This makes the
///                 message easy to extract using text tools.
/// @param fmt      Printf format string (see gnu printf for details).
/// @param ...      This is a vararg function.

void opmMessage (
    const char* severity,
    const char* ident,
    const char* fmt,
                ...
) __attribute__(( format (printf, 3,4)));

/// Direct all text output from the simulator to these callbacks.
/// @param outputcb The text output function.
/// @param quitcb   Function called before simulator exits (use this to flush
///                 your text).
/// @param userData Pass this in the userData argument.

void opmMessageDirect (
    optTextOutputFn outputcb,
    optQuitFn       quitcb,
    void*           userData
);

/// Turn off messages with an ident beginning with the passed string.
/// @param ident The start of the ident to be turned off. e.g. OP_ turns off
///              messages beginning OP_.

void opmMessageDisable (
    const char* ident
);

/// Use this to respond to the simulator -verbose flag.
/// @return True if platform should be verbose.

Bool opmMessageQuiet (void);

/// Suppress warning messages.
/// @return The old value.
/// @param quiet No warnings.

Bool opmMessageSetNoWarn (
    Bool quiet
);

/// Suppress info messages.
/// @return The old value.
/// @param quiet Quiet mode.

Bool opmMessageSetQuiet (
    Bool quiet
);

/// Are we in global verbose mode.
/// @return True if verbose.

Bool opmMessageVerbose (void);

/// Return the state of the --nobanner flag.
/// @return Returns true if no banner should be printed.

Bool opmNoBanner (void);

/// Send formatted text to the simulator output stream.
/// @param fmt Printf format string (see gnu printf for details).
/// @param ... varargs.

void opmPrintf (
    const char* fmt,
                ...
);

/// Reset the error count.
/// @param old Old error count.

void opmResetErrors (
    Uns32 old
);

/// Abort, using a va_list.
/// @param ident A short code to identify this message. This makes the
///              message easy to extract using text tools.
/// @param fmt   Printf format string (see gnu printf for details).
/// @param ap    Varargs list.

void opmVAbort (
    const char* ident,
    const char* fmt,
    va_list     ap
);

/// As for icmMessage, but using a va_list.
/// @param severity I=Info, W=Warning, E=Error, F=Fatal (aborts the
///                 simulator).
/// @param ident    A short code to identify this message. This makes the
///                 message easy to extract using text tools.
/// @param fmt      Printf format string (see gnu printf for details).
/// @param ap       Varargs list.

void opmVMessage (
    const char* severity,
    const char* ident,
    const char* fmt,
    va_list     ap
);

/// Send formatted text to the simulator output stream.
/// @param fmt Printf format string (see gnu printf for details).
/// @param ap  Varargs list header.

void opmVPrintf (
    const char* fmt,
    va_list     ap
);


#endif /* OPMMESSAGE_H */

