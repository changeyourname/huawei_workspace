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

/*
 * This is a list of all built-in formals accepted by Imperas simulators.
 *
 */

#ifndef OPF_FORMALS_H
#define OPF_FORMALS_H

///////////////////////////////////////////////////////////////////////////////
// Parameters applicable to a processor instance
///////////////////////////////////////////////////////////////////////////////

/* If the processor is not connected to a bus, use this number of address bits */
#define BIF_ADDR_BITS                  "addrbits"

/* Set a unique ID for this CPU */
#define BIF_CPU_ID                     "cpuid"

/* MDP does not not use gdb with this processor */
#define BIF_DEBUG_BASIC                "debugbasic"

/* This processor will load it's default semihost library */
#define BIF_DEFAULT_SEMIHOST           "defaultsemihost"

/* Load VAP tools */
#define BIF_ENABLE_TOOLS                "enabletools"

/* Load VAP tools for PSE*/
#define BIF_ENABLE_TOOLS_PSE            "enabletoolspse"

/* Set this processor endian (most processors with selectable endian use this name). */
#define BIF_ENDIAN                     "endian"

/* specify a file to be a read by a gdb connected to this processor */
#define BIF_GDB_COMMAND_FILE           "gdbcommandfile"

/* Additional command-line flags for the gdb connected to this processor */
#define BIF_GDB_FLAGS                  "alternategdbflags"

/* tell gdb to execute this file before the prompt is displayed */
#define BIF_GDB_INIT                   "gdbinit"

/* override the default path to the gdb connected to this processor */
#define BIF_GDB_PATH                   "alternategdbpath"

/* The simulator will intercept calls to Imperas special functions */
#define BIF_IMPERAS_INTERCEPTS         "enableimperasintercepts"

/* VAP tools do SMP analysis */
#define BIF_ENABLE_SMP_TOOLS           "enableSMPTools"

/* For internal use */
#define BIF_FETCH_VALIDATE             "fetchvalidate"

/* Use physical rather than virtual addresses when loading application code
 * for this processor. */
#define BIF_LOAD_PHYSICAL              "loadphysical"

/* Use VMA rather than LMA on Elf file loads for this processor */
#define BIF_ELF_USE_VMA                "elfusevma"

/* limit the maximum number of instructions to be executed */
#define BIF_MAX_INSTRUCTIONS           "maxinstructions"

/* specify the MIPS rate of this processor (in MHz) */
#define BIF_MIPS                       "mips"

/* Pass flags a 32-bit word of flags to this model.
 * (The model must be coded to accept it). */
#define BIF_MODEL_FLAGS                "debugflags"

/* When a processor exception is encountered, the processor will execute the
 * exception rather than stopping the simulation */
#define BIF_SIMEX                      "simulateexceptions"

/* Ignore the start address in the hardware or the loaded application,
 * and start at this specified address instead. */
#define BIF_START_ADDRESS              "startaddress"

/* Enable instruction tracing */
#define BIF_TRACE                      "trace"

/* For internal use */
#define BIF_TRACE_NO_ANNUL             "tracenoannul"

/* Turn on the trace history buffer */
#define BIF_TRACE_BUFFER               "tracebuffer"

/* Turn on the trace of register changes */
#define BIF_TRACE_CHANGE               "tracechange"

/* Turn off tracing after this many instructions */
#define BIF_TRACE_COUNT                "tracecount"

/* Include a per-processor instruction count in the trace output */
#define BIF_TRACE_SHOW_ICOUNT          "traceshowicount"

/* Turn tracing on after this many instructions */
#define BIF_TRACE_START                "tracestart"

/* Print processor register contents after each instruction */
#define BIF_TRACE_REGS_AFTER           "traceregsafter"

/* Print processor register contents before each instruction */
#define BIF_TRACE_REGS_BEFORE          "traceregsbefore"

/* Trace memory starting at this address - NOT USED */
#define BIF_TRACE_MEM_ADDR             "tracememaddr"

/* Trace memory this many bytes - NOT USED  */
#define BIF_TRACE_MEM_SIZE             "tracememsize"

/* Array of user flags sent to the semihost library to pass to main()  */
#define BIF_USER_ARGV                 "userargv"

/* Trace memory this many bytes - NOT USED  */
#define BIF_VARIANT                   "variant"

///////////////////////////////////////////////////////////////////////////////
// Parameters applicable to a peripheral instance
///////////////////////////////////////////////////////////////////////////////

#define BIF_DIAGS                      "diagnosticlevel"

///////////////////////////////////////////////////////////////////////////////
// Parameters applicable to a root module
///////////////////////////////////////////////////////////////////////////////

/* Run the pse constructors before dropping into the debugger */
#define BIF_DEBUG_PSE_CONSTRUCTORS     "debugpseconstructors"

/* Debug TCL Batch Files (separated by semicolons) */
#define BIF_DEBUG_BATCH_FILE           "batch"

/* Debug MI Mode */
#define BIF_DEBUG_MI_MODE              "mi"

/* Debug TCL Mode (After any batch files) */
#define BIF_DEBUG_TCL_MODE             "interactive"

/* Debug GDB Mode (After any batch files) */
#define BIF_DEBUG_GDB_MODE             "idebug"

/* Run in IGEN or CPUGEN modes */
#define BIF_CGEN                       "cgen"
#define BIF_IGEN                       "igen"
#define BIF_ISS                        "iss"

/* Override default dictionary size */
#define BIF_DICT_SIZE                  "dictsize"

/* Options for GDB and MP GUI */
#define BIF_EGUI_OPTIONS                "eguioptions"

/* Set the simulation finish time */
#define BIF_FINISH_TIME                "finishtime"

/* 'pop-up' a GDB console */
#define BIF_GDB_CONSOLE                "gdbconsole"

/* Start GDB EGUI */
#define BIF_GDB_EGUI                   "gdbegui"

/* Start GDB GUI */
#define BIF_GDB_GUI                    "gdbgui"

/* 'pop-up' a multiprocessor debug console */
#define BIF_MPD_CONSOLE                "mpdconsole"

/* Start MPD EGUI */
#define BIF_MPD_EGUI                   "mpdegui"

/* Start MPD GUI */
#define BIF_MPD_GUI                    "mpdgui"

/* 'pop-up' a multiprocessor debug console */
#define BIF_MPD_FULL_NAMES             "mpdfullnames"

/* Listen for but do not wait for a debugger connection */
#define BIF_NO_RSP_WAIT                "rspnowait"

/* for internal use only */
#define BIF_NO_SIMULATION              "nosimulation"

/* Enable limited parallel simulation */
#define BIF_NO_OPTIMIZE                "nooptimze"

/* Enable limited parallel simulation */
#define BIF_PARALLEL                  "parallel"

/* Enable unlimited parallel simulation */
#define BIF_PARALLEL_MAX              "parallelmax"

/* Parallel simulation options */
#define BIF_PARALLEL_OPT              "parallelopt"

/* Set number of parallel threads */
#define BIF_PARALLEL_THREADS          "parallelthreads"

/* Print all bus connections */
#define BIF_PRINT_BUSES                "showbuses"

/* Print all available model commands for this platform */
#define BIF_PRINT_COMMANDS             "showcommands"

/* Print all available model commands for this platform */
#define BIF_PRINT_DOMAINS              "showdomains"

#define BIF_PRINT_DESIGNS              "showdesigns"
#define BIF_PRINT_MODELS               "showmodels"
#define BIF_PRINT_MODULES              "showmodules"
#define BIF_PRINT_PERIPHERALS          "showperipherals"
#define BIF_PRINT_PLATFORMS            "showplatforms"
#define BIF_PRINT_PROCESSORS           "showprocessors"

/* Print all environment variable accepted by this product */
#define BIF_PRINT_ENV                  "showenv"

/* Show all formal parameters in the platform */
#define BIF_PRINT_FORMALS              "showformals"

/* Show model-specific formal parameters in the platform */
#define BIF_PRINT_MODEL_FORMALS        "showmodelformals"

/* Show system formal parameters in the platform */
#define BIF_PRINT_SYSTEM_FORMALS       "showsystemformals"

/* Show all license personality names */
#define BIF_OBJECT_LOADER              "objectloader"

/* Show all license personality names */
#define BIF_LIST_PERSONALITIES         "listpersonalities"

/* Show current personality */
#define BIF_PRINT_PERSONALITY          "showpersonality"

/* set the quantum (in seconds) */
#define BIF_QUANTUM                    "quantum"

/* Seed for random number generation */
#define BIF_QUANTUM_SEED               "quantumseed"

/* Output VCD file name for quantum trace */
#define BIF_QUANTUM_TRACE              "quantumtracefile"

/* Start of quantum in which to search for non-determinism */
#define BIF_QUANTUM_DIFF               "quantumdifftime"

/* for internal use */
#define BIF_READ_FRAME_INFO            "readframeinfo"

/* models record to   this directory */
#define BIF_REC_DIR                    "recorddir"

/* models replay from this directory */
#define BIF_REP_DIR                    "replaydir"

/* for internal use */
#define BIF_REPORT_MEMORY              "memorystats"

/* specify and enable a remote debugger port */
#define BIF_REMOTE_DEBUG_PORT          "remotedebugport"

/* Allow control-C to stop the simulator */
#define BIF_STOP_ON_CTRLC              "stoponcontrolc"

/* Do not print banners at start and end of simulation
 * (restricted to certain products) */
#define BIF_SUPPRESS_BANNER            "suppressbanner"

/* Notify the simulator that it is encapsulated in SystemC */
#define BIF_SYSTEMC                    "systemc"

/* Set the simulator time precision */
#define BIF_TIME_PRECISION             "timeprecision"

/* Enable tracing of simulator shared data */
#define BIF_TRACE_SHARED_DATA          "traceshareddata"

/* Enable verbose mode. The simulator will print more information */
#define BIF_VERBOSE                    "verbose"

/* for internal use */
#define BIF_VERBOSE_DICT               "verbosedictionary"

/* set the simulator wallclock factor to 1.0 */
#define BIF_WALLCLOCK                  "wallclock"

/* Specify a simulator wallclock factor */
#define BIF_WALLCLOCK_FACTOR           "wallclockfactor"

///////////////////////////////////////////////////////////////////////////////
// Parameters applicable to an MMC
///////////////////////////////////////////////////////////////////////////////

/* MMC Transparent mode */
#define BIF_TRANSPARENT                "transparent"

#endif
