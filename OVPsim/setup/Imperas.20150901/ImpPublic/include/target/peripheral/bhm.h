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

/* bhm.h */

#ifndef BHM_BHM_H
#define BHM_BHM_H

#include "peripheral/impTypes.h"

/// Use this for native file paths

#define BHM_MAX_PATH 1024

/// Handle to an event

typedef Uns32 bhmEventHandle;

typedef enum bhmRestartReasonE {
    BHM_RR_TRIGGERED= 0,     /**< restarted because event was triggered*/
    BHM_RR_DELEVENT = 1,     /**< restarted because event was deleted*/
    BHM_RR_BADEVENT = 2,     /**< failed to wait because event handle was bad*/
} bhmRestartReason;

typedef bhmRestartReason pseRestartReason;

typedef enum bhmSystemEventTypeE {
    BHM_SE_START_OF_SIMULATION = 0, /**< triggers at start of simulation */
    BHM_SE_END_OF_SIMULATION   = 1, /**< triggers at end of simulation */
    BHM_SE_LAST                = 2  /**< Do not use, keep this last */
} bhmSystemEventType;

////////////////////////////////////////////////////////////////////////////////
/// PROCESS CREATION AND DELETION INTERFACE
////////////////////////////////////////////////////////////////////////////////

///
/// Handle to a created thread.
///
typedef Uns32 bhmThreadHandle;

/// Called when the user defined thread is started (this implements the thread).
// @param   user         user-supplied value.
typedef void  (*bhmCBThreadFunc)(void *user);

///
/// Create a new thread. The processor will execute the callback function
/// 'cb', which is passed 'user' as an argument.

/// @param cb     Callback function which implements the thread.
/// @param user   Passed back to the user function 'cb'
/// @param name   The name used to identify the thread in the debugger.
/// @param sp     Pointer to the region to be used a s stack. The user
///                  is responsible for getting the end of the region correct.
/// @return          Handle to new thread or null.

bhmThreadHandle bhmCreateThread(
    bhmCBThreadFunc cb,
    void          *user,
    const char    *name,
    void          *sp
);

///
/// Kill a process created by bhmCreateThread.
///
/// @param h     Handle of thread to be killed.
///
/// @return      Bool return True if 'another' thread was killed.

Bool bhmDeleteThread(bhmThreadHandle h);


////////////////////////////////////////////////////////////////////////////////
/// EVENT INTERFACE
////////////////////////////////////////////////////////////////////////////////

/// Create an event handle on which threads can wait
/// @return  handle to created event

bhmEventHandle bhmCreateEvent(void);

/// Create an event handle on which threads can wait
/// This variant will be visible to the debugger etc.
/// @return           handle to created event
/// @param   name     name of the event (to be seen by debugger)
/// @param   desc     short description (to be seen by debugger)

bhmEventHandle bhmCreateNamedEvent(const char *name, const char *desc);

/// Delete an event handle, restarting all threads waiting on it.
/// @param handle    Handle to event to delete.
/// @return     success/failure.

Bool bhmDeleteEvent(bhmEventHandle handle);

/// Stop the current thread until the event is triggered
/// @param      handle Handle to the event to wait for.
/// @return     reason that the wait completed.

bhmRestartReason bhmWaitEvent(bhmEventHandle handle);

/// Trigger an event after the specified delay. This will restart any processes
/// waiting in the event at that time. Note that if the event is already
/// scheduled to be triggered at a future time, the new delay will replace the
/// existing delay (i.e. the event will be rescheduled).
/// TODO : need to be able to cancel event before the delay elapses.
/// @param     h      Handle to event to trigger.
/// @param     delay  Delay until trigger occurs.

Bool bhmTriggerAfter(bhmEventHandle h, double delay);

/// Immediately trigger an event, restarting any threads waiting for it, This
/// is NOT equivalent to bhmTriggerAfter(h, 0); because this happens without suspending.
/// @param     h      Handle to event to trigger.
/// @return           success/failure   (if the handle is invalid).
Bool bhmTriggerEvent(bhmEventHandle h);

/// Cancel a waiting event
/// @param     h      Handle to waiting event to cancel.
/// @return           success/failure   (if the handle is invalid).

Bool bhmCancelTrigger(bhmEventHandle h);

/// Return a handle to a system event object
/// @return  handle to system event

bhmEventHandle bhmGetSystemEvent(bhmSystemEventType eventType);

////////////////////////////////////////////////////////////////////////////////
/// TIME INTERFACE
////////////////////////////////////////////////////////////////////////////////

/// Use this time with bhmWaitDelay to delay until the next quantum
#define QUANTUM_DELAY -1.0

/// Delay current thread for the passed time
/// @param    delay   microseconds delay to wait .
/// @return           success/failure

Bool bhmWaitDelay(double delay);

/// Get the current simulated time
/// @return     Time (in microseconds) since start of simulation.
///             in bhmMessage, print with "%e"

double bhmGetCurrentTime(void);

////////////////////////////////////////////////////////////////////////////////
/// DEBUG/DIAGNOSTICS
////////////////////////////////////////////////////////////////////////////////

/// Send formatted text to the simulator output stream.
/// The text is prefixed with the severity, the prefix code and the model
/// instance name. Use this for user-level diagnostics.
/// @param severity    "I"=Info
///                    "W"=Warning
///                    "E"=Error
///                    "F"=Fatal (aborts the simulator)
/// @param prefix      a short code to identify this message.
///                    This makes the message easy to extract using text tools.
/// @param format      printf format string (see gnu printf for details)
/// @param ...         this is a vararg function
/// @return            number of characters printed (note: capped at 1024).

Uns32 bhmMessage(
    const char *severity,
    const char *prefix,
    const char *format,
    ...
) __attribute__(( format (printf, 3,4)));

/// Deprecated. Please use bhmInstallDiagCB.
///
/// Return current diagnostic level
/// @return diagnostic level
/// bits 0&1:         0=off
///                   1=low       (start-up, mode-change etc)
///                   2=medium    (each operation)
///                   3=high      Most detailed. This also turns on system diagnostics
///                               which shows activity on events, registers and ports.
/// bits 2-31: reserved
Uns32 bhmGetDiagnosticLevel(void);

/// general mask macros to be used to get the current PSE diagnostic level
#define BHM_DIAG_MASK_LOW(_diag)        ((_diag & 3) > 0)
#define BHM_DIAG_MASK_MEDIUM(_diag)     ((_diag & 3) > 1)
#define BHM_DIAG_MASK_HIGH(_diag)       ((_diag & 3) > 2)

/// mask macro to get diagnostics to be passed to PSE intercept/semihost (if used)
#define BHM_DIAG_MASK_SEMIHOST(_diag)   ((_diag >> 2) & 3)

/// Deprecated. Please use bhmInstallDiagCB.
/// Use these macros to refer to bhmGetDiagnosticLevel
/// e.g.   if (BHM_DIAG_LOW)  bhmMessage(
#define BHM_DIAG_LOW     (BHM_DIAG_MASK_LOW(bhmGetDiagnosticLevel()))
#define BHM_DIAG_MEDIUM  (BHM_DIAG_MASK_MEDIUM(bhmGetDiagnosticLevel()))
#define BHM_DIAG_HIGH    (BHM_DIAG_MASK_HIGH(bhmGetDiagnosticLevel()))


/// Prototype for diagnostic level function.
/// This function should set your local diagnostic level control variable.
/// @param    level    new level
typedef void (*bhmSetDiagnosticLevel)(Uns32 level);

/// Install a function to set the local diagnostic level
/// This function supersedes bhmGetDiagnosticLevel()
/// @param   cb    the callback function
void bhmInstallDiagCB(bhmSetDiagnosticLevel cb);

/// Send formatted text to the simulator output stream
/// @param format      printf format string (see gnu printf for details)
/// @param ...         this is a vararg function
/// @return            number of characters printed (note: capped at 1024).
/// This sends output to the simulator log without any pre-pended data.
/// Only use this to produce tables, xml or data of your own format.
Uns32 bhmPrintf(const char *format, ...) __attribute__((format (printf, 1,2)));

////////////////////////////////////////////////////////////////////////////////
/// SIMULATOR CONTROL
////////////////////////////////////////////////////////////////////////////////

/// Halt simulation immediately

void bhmFinish(void);

////////////////////////////////////////////////////////////////////////////////
/// ATTRIBUTE INTERFACE
////////////////////////////////////////////////////////////////////////////////

/// Fetch a string attribute for the current peripheral.
/// @param attributeName     Name of attribute to be fetched.
/// @param string            String to be updated with value.
/// @param length            max length to be filled in.
/// @return success(1)/failure(0)

Uns32 bhmStringAttribute(const char *attributeName, char *string, Uns32 length);

/// Fetch an integer attribute for the current peripheral.
/// @param attributeName     Name of attribute to be fetched.
/// @param ptr               pointer to value to be updated.
/// @return success(1)/failure(0)

Uns32 bhmIntegerAttribute(const char *attributeName, Uns32 *ptr);

// Alias for IntegerAttribute
#define bhmUns32Attribute bhmIntegerAttribute

/// Fetch a 64-bit integer attribute for the current peripheral.
/// @param attributeName     Name of attribute to be fetched.
/// @param ptr               pointer to value to be updated.
/// @return success(1)/failure(0)

Uns32 bhmUns64Attribute(const char *attributeName, Uns64 *ptr);

/// Fetch a 64-bit integer attribute for the current peripheral.
/// @param attributeName     Name of attribute to be fetched.
/// @return set and true(1) / not set or false (0)

Bool bhmBoolAttribute(const char *attributeName);

////////////////////////////////////////////////////////////////////////////////
/// RECORD/REPLAY INTERFACE
////////////////////////////////////////////////////////////////////////////////

/// Use this interface to record external events which change the
/// state a of a peripheral so that it can be replayed without external stimulus.

/// Open a recording stream.
/// Call this during startup. It returns True if recording is required.
/// @return False:(no recording) True:(recording required).

Bool bhmRecordStart(void);

/// Save one event
/// @param type        application-specific type code
/// @param bytes       number of bytes of application data to to save (can be zero).
/// @param data        pointer to data block to save.

void bhmRecordEvent(Uns32 type, Uns32 bytes, const void *data);

/// Queries the platform to see if replay is required and if so, begins the session.
/// Call this during startup. It returns True if replay is required.
/// @return False:(no replay) True:(replay required).

Bool bhmReplayStart(void);

/// Read one event from the log
/// @param time        pointer to time variable which will be updated with
///                    current time.
/// @param type        pointer to application-specific type code which will be
///                    updated with record type.
/// @param maxBytes    maximum number number of bytes of application data to to
///                    restore (can be zero).
/// @param data        pointer to data block to fill with restored data.
/// @return            number of application data bytes in record, -1 if end-of-file.

Int32 bhmReplayEvent(double *time, Uns32 *type, Uns32 maxBytes, void *data);

/// close record file

void bhmRecordFinish(void);

/// close replay file

void bhmReplayFinish(void);

////////////////////////////////////////////////////////////////////////////////
/// SAVE/RESTORE INTERFACE
////////////////////////////////////////////////////////////////////////////////

/// Used to describe status of save/restore operation

typedef enum bhmSaveRestoreStatusE {
    BHM_SRS_ERROR,      /// error in save/restore restore
    BHM_SRS_OK,         /// successful operation
    BHM_SRS_END_LIST    /// end of list (bhmSaveElement/bhmRestoreElement only)
} bhmSaveRestoreStatus;

/// Macros for save/restore of named variables

#define BHM_SAVE_VAR(_NAME) \
    bhmSave(#_NAME, &(_NAME), sizeof(_NAME))
#define BHM_RESTORE_VAR(_NAME) \
    bhmRestore(#_NAME, &(_NAME), sizeof(_NAME))

/// Save a named value using the active save context
/// @param name     name of record to save
/// @param value    pointer to value to save
/// @param bytes    size of data value in bytes
/// @return         success status

bhmSaveRestoreStatus bhmSave(
    const char *name,
    const void *value,
    Uns32       bytes
);

/// Restore a named value using the active restore context
/// @param name     name of record to restore
/// @param value    pointer to value to restore
/// @param bytes    size of data value in bytes
/// @return         success status

bhmSaveRestoreStatus bhmRestore(
    const char *name,
    void       *value,
    Uns32       bytes
);

// Save a list element using the active save context. Pass NULL to value to
// indicate the last element of the list
/// @param elementName  name of element
/// @param endName      name used to indicate terminated element list
/// @param value        pointer to element value to save
/// @param bytes        size of element value in bytes
/// @return             success status

bhmSaveRestoreStatus bhmSaveElement(
    const char *elementName,
    const char *endName,
    const void *value,
    Uns32       bytes
);

// Restore a list element using the active restore context. The return value
// is BHM_SRS_OK if an element is successfully restored, or BHM_SRS_END_LIST if
// the list terminator has been read.
/// @param elementName  name of element
/// @param endName      name used to indicate terminated element list
/// @param value        pointer to element value to restore
/// @param bytes        size of element value in bytes
/// @return             success status

bhmSaveRestoreStatus bhmRestoreElement(
    const char *elementName,
    const char *endName,
    void       *value,
    Uns32       bytes
);

///////////////////////////////////////////////////////////////////////////////
/// SERIAL SUPPORT
///////////////////////////////////////////////////////////////////////////////

///
/// Handle to a channel
///
typedef Int32 bhmChannelHandle;

///
/// Create a new serial channel, blocking the simulator until it its connected to an
/// external program

/// @param portp        Pointer to integer port number.
///                     If null, sockets are not used.
///                     If pointing to zero, a port is allocated by the system and the value overwritten.
///                     If non-zero, the port number is used.
///                     Ignored if console is true, overrides parameter sourcefile

/// @param logfile      A string specifying a file to record all serial device output.
///                     On a Unix system, use tail -f file to watch the device output.

/// @param sourcefile   A file to use as source for the serial device.
///                     Note that this data will be read as fast as the model requests it.
///                     Ignored if console is true.
///                     Ignored if portp is non-null.

/// @param portfile     Used in conjunction with portp. A file with this name is written
///                     when the portn number is known.
///                     Overridden by the console parameter.

/// @param verbose      Send UART output to the simulator log

/// @param console      Pop up a console window, and connect using a socket.
///                     Overrides the port and sourcefile parameters
///
///                     The terminal program which runs in the console is
///                     $IMPERAS_HOME/bin/[architecture]/terminal.exe
///                     which is supplied with various Demo packages.
///                     The program can be overridden using the environment variable
///                     IMPERAS_TERMINAL_PROGRAM, e.g.
///       export IMPERAS_TERMINAL_PROGRAM="/usr/bin/telnet %s %d"
///       set    IMPERAS_TERMINAL_PROGRAM = "C:\Program Files\Windows NT\hypertrm.exe" /t %s:%d
///       (%s and %d are replaced by the system with host and port number)

/// @param finishOnDisconnect  When the socket disconnects, finish the simulation.

/// @return             The channel number, or -1 if it fails

Int32 bhmSerOpenBlocking(
    Uns32      *portp,
    const char *logfile,
    const char *sourcefile,
    const char *portfile,
    Bool        verbose,
    Bool        console,
    Bool        finishOnDisconnect
);

///
/// Create a new serial channel, blocking the simulator until it its connected to an
/// external program. Derive all the operating modes of the serial channel from model
/// parameters instead of arguments. These are the parameters:

/// console     string   If specified, port number is ignored, and a console pops up automatically.
///                      This source is the 1st priority input.
/// portnum     integer  If set, listen on this port.
///                      If set to zero, allocate a port from the pool and listen on that.
///                      See portfile and console attributes below.
///                      This is the 2nd highest priority source.
/// infile      string   Name of file to use for device source. This is the 3rd priority input.

/// outfile     string   Name of file to write device output (can be used in addition to other modes).

/// portFile    string   If portnum was specified as zero, write the port number to this file when it's known.
/// log         string   If specified, serial output will go to simulator log in addition to other modes.
/// finishondisconnect
///             string   If set, disconnecting the port will cause the simulation to finish.
///
/// @return             The channel number, (the simulator dies if this function fails).

Int32 bhmSerOpenAuto(void);

///
/// Include this macro in the model's formal parameter list
/// to declare the formal parameters used by bhmSerOpenAuto()
/// in igen.exe TCL, use:
///     imodeladdformalmacro -name BHM_SER_OPEN_AUTO_FORMALS
///
#define BHM_SER_OPEN_AUTO_FORMALS \
    { .name = "console",            .type = ppm_PT_BOOL,   .description = "If specified, port number is ignored, and a console pops up automatically" }, \
    { .name = "portnum",            .type = ppm_PT_UNS32,  .description = "If set, listen on this port. If set to zero, allocate a port from the pool and listen on that." }, \
    { .name = "infile",             .type = ppm_PT_STRING, .description = "Name of file to use for device source" }, \
    { .name = "outfile",            .type = ppm_PT_STRING, .description = "Name of file to write device output" }, \
    { .name = "portFile",           .type = ppm_PT_STRING, .description = "If portnum was specified as zero, write the port number to this file when it's known" }, \
    { .name = "log",                .type = ppm_PT_BOOL,   .description = "If specified, serial output will go to simulator log" }, \
    { .name = "finishOnDisconnect", .type = ppm_PT_BOOL,   .description = "If set, disconnecting the port will cause the simulation to finish" }

///
/// Include this macro in the model's formal parameter list
/// to declare the formal parameters used for record and replay
/// in igen.exe TCL, use:
///     imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS
///
#define BHM_RECORD_REPLAY_FORMALS \
    { .name = "record",   .type = ppm_PT_STRING, .description = "Record external events into this file" }, \
    { .name = "replay",   .type = ppm_PT_STRING, .description = "Replay external events from this file" }

/// Read data from the channel. Does not block.

/// @param ch           The channel number returned by serOpenBLocking
/// @param buffer       Pointer to character buffer
/// @param length       Maximum number of characters to read
/// @return             Actual number of characters read (might be zero)

Uns32 bhmSerReadN(Int32 ch, Uns8 *buffer, Uns32 length);

/// Write data to the channel. Does not block.

/// @param ch           The channel number returned by serOpenBLocking
/// @param buffer       Pointer to character buffer
/// @param length       Number of characters in the buffer
/// @return             Actual number of characters written (might be zero if socket is not open)

Uns32 bhmSerWriteN(Int32 ch, Uns8 *buffer, Uns32 length);

/// Read data from the channel. May block the calling PSE thread.

/// @param ch           The channel number returned by serOpenBLocking
/// @param buffer       Pointer to character buffer
/// @param length       Maximum number of characters to read
/// @return             Actual number of characters read (might be zero)

Uns32 bhmSerReadB(Int32 ch, Uns8 *buffer, Uns32 length);

/// Write data to the channel. May block the calling PSE thread.

/// @param ch           The channel number returned by serOpenBLocking
/// @param buffer       Pointer to character buffer
/// @param length       Number of characters in the buffer
/// @return             Actual number of characters written (might be zero if socket is not open)

Uns32 bhmSerWriteB(Int32 ch, Uns8 *buffer, Uns32 length);

/// Legacy aliases for non-blocking read and write

#define bhmSerRead  bhmSerReadN
#define bhmSerWrite bhmSerWriteN

/// Close the channel.
/// @param ch           The channel to be closed. This will also flush log files.

void bhmSerClose(Uns32 ch);

/////////////////////////////////////////////////////////////////////////////////////////////////
// ETHERNET SUPPORT
/////////////////////////////////////////////////////////////////////////////////////////////////
/// Create a new ethernet channel
///
/// @param tap_device   Name of TAP device
/// @param redir        Redirection instruction
/// @param tftp_path    Path to root of tftp directory
/// @return             File descriptor of new channel

Int32 bhmEthernetOpen(
    const char *tap_device,
    const char *redir,
    const char *tftp_path
);

/// Create a new ethernet channel, using these parameters:
/// tap_device   string  Name of TAP device
/// redir        string  Redirection instruction
/// tftp_path    string  Path to root of tftp directory
/// outfile      string  Create this ethernet log file
/// @return      File descriptor of new channel

Int32 bhmEthernetOpenAuto();
///
/// Include this macro in the model's formal parameter list
/// to declare the formal parameters used by bhmEthernetOpenAuto()
/// in igen.exe TCL, use:
///     imodeladdformalmacro -name BHM_ETHERNET_OPEN_AUTO_FORMALS
///
#define BHM_ETHERNET_OPEN_AUTO_FORMALS \
    { .name = "tapDevice",          .type = ppm_PT_STRING, .description = "The name of the TAP device" }, \
    { .name = "redir",              .type = ppm_PT_STRING, .description = "Redirection instruction" }, \
    { .name = "tftpPrefix",         .type = ppm_PT_STRING, .description = "Path to the root of the tftp directory" }


/// Read frame of data from the channel. Does not block.
///
/// @param ch           The channel number returned by serOpenBLocking
/// @param buffer       Pointer to character buffer
/// @param length       Number of characters in the buffer
/// @param timeMS       Time to wait in milliseconds
/// @param poll         Not used
/// @return             Actual number of characters written (might be zero if socket is not open)

Uns32 bhmEthernetReadFrameN(
    Int32 ch,
    Uns8 *buffer,
    Uns32 length,
    Uns32 timeMS,
    Uns32 poll
);

/// Write frame data to the channel. Does not block.
///
/// @param ch           The channel number returned by serOpenBLocking
/// @param buffer       Pointer to character buffer
/// @param length       Number of characters in the buffer
/// @return             Actual number of characters written (might be zero if socket is not open)

Uns32 bhmEthernetWriteFrameN(Int32 ch, Uns8 *buffer, Uns32 length);

/// Read frame of data from the channel. May block the calling PSE thread.
///
/// @param ch           The channel number returned by serOpenBLocking
/// @param buffer       Pointer to character buffer
/// @param length       Number of characters in the buffer
/// @param timeMS       Time to wait in milliseconds
/// @param poll         Not used
/// @return             Actual number of characters written (might be zero if socket is not open)

Uns32 bhmEthernetReadFrameB(
    Int32 ch,
    Uns8 *buffer,
    Uns32 length,
    Uns32 timeMS,
    Uns32 poll
);

/// Write frame data to the channel. May block the calling PSE thread.
///
/// @param ch           The channel number returned by serOpenBLocking
/// @param buffer       Pointer to character buffer
/// @param length       Number of characters in the buffer
/// @return             Actual number of characters written (might be zero if socket is not open)

Uns32 bhmEthernetWriteFrameB(Int32 ch, Uns8 *buffer, Uns32 length);

/// Legacy aliases for non-blocking read and write

#define bhmEthernetReadFrame  bhmEthernetReadFrameN
#define bhmEthernetWriteFrame bhmEthernetWriteFrameN

/// Return the current channel status
///
/// @param ch           The channel number returned by serOpenBLocking
/// @param stat         Pointer to 32bit status integer
/// @return             Zero if success.

Uns32 bhmEthernetGetStatus(Int32 ch, Int32 *stat);

/// Close the channel
///
/// @param ch           The channel number returned by serOpenBLocking
/// @return             Zero if success

Uns32 bhmEthernetClose(Int32 ch);

void bhmFuncExit(void);

/////////////////////////////////////////////////////////////////////////////////////////////////
// USB SUPPORT
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
// DISK DRIVE SUPPORT
/////////////////////////////////////////////////////////////////////////////////////////////////

#endif
