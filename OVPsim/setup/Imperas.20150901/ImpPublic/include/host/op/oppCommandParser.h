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


#ifndef OPPCOMMANDPARSER_H
#define OPPCOMMANDPARSER_H

#include "optTypes.h"

/// Return true if the named argument has been used on the command line.
/// @return Path to object file if exactly one is specified.
/// @param parser The parser.
/// @param name   name of the flag (without the '-').

Bool oppCmdArgUsed (
    optCmdParserP parser,
    const char  * name
);

/// Install a handler to be called when a flag is not recognized.
/// @param parser   The parser.
/// @param handler  Handler called when flag is not recognized.
/// @param userData User data passed to error handler.

void oppCmdErrorHandler (
    optCmdParserP        parser,
    optCmdErrorHandlerFn handler,
    void*                userData
);

/// Parse an argument list using the currently installed flags.
/// @return Returns true if arguments were parsed with no errors.
/// @param parser The parser.
/// @param argc   Number of arguments.
/// @param argv   Null terminated array of strings, such as passed to main.

Bool oppCmdParseArgs (
    optCmdParserP parser,
    Uns32         argc,
    const char ** argv
);

/// Parse a file using the currently installed flags.
/// @return Returns true if file was parsed with no errors.
/// @param parser The parser.
/// @param path   Path to an existing file.

Bool oppCmdParseFile (
    optCmdParserP parser,
    const char *  path
);

/// Create a standard parser and parse an argument list. Use this if no custom
/// arguments are required. Does not return if errros are detected.
/// @param client  Name of the client (usually the program, argv[0]).
/// @param useMask Which flags are included.
/// @param argc    Number of arguments.
/// @param argv    Array of strings such as passed to main.

void oppCmdParseStd (
    const char*   client,
    Uns32         useMask,
    Uns32         argc,
    const char ** argv
);

/// Add legal argument to a parser. Adding a duplicate argument will cause a
/// fatal error.
/// @param parser      The parser.
/// @param name        Flag name.
/// @param shortName   Optional single character alternative.
/// @param argDesc     Optional description of the argument.
/// @param group       Optional group (clarifies -help output).
/// @param type        Argument type (see enumerations).
/// @param pointer     Pointer to callback or data to be modified.
/// @param description For help messages.
/// @param useMask     Use mask. Each nibble controls a mode. n0=in eng mode,
///                    n1=product mode.
/// @param userData    User data passed to callback.
/// @param mandatory   If true, this argument must be specified.

void oppCmdParserAdd (
    optCmdParserP parser,
    const char*   name,
    const char*   shortName,
    const char*   argDesc,
    const char*   group,
    optFlagType   type,
    void*         pointer,
    const char*   description,
    Uns32         useMask,
    Uns32         userData,
    Bool          mandatory
);

/// Create an instance of a command parser.
/// @return The new parser.
/// @param client  Name of the client (usually the program, argv[0]).
/// @param useMask Which flags are included.

optCmdParserP oppCmdParserNew (
    const char* client,
    Uns32       useMask
);

/// Delete an instance of a command parser.
/// @param parser The parser to be destroyed.

void oppCmdParserOld (
    optCmdParserP parser
);

/// Print this message with -help if command line errors are found.
/// @param parser  Parser.
/// @param message General help message.

void oppCmdUsageMessage (
    optCmdParserP parser,
    const char *  message
);

/// Return the only application specified on the command line.
/// @return The only application specified on the command line.

const char * oppDefaultApplication (void);


#endif /* OPPCOMMANDPARSER_H */

