
var dataExists = 1; // must exist and be set to 1

var pageTitle = "OVP LOCAL Documentation";
var documentName = "the OVP Products";
var headerGraphic = "doc_header.gif";

var secTitle = new Array();
var secFile = new Array();
var secDescr = new Array();
var secExist = new Array();
var secDoxygen = new Array();

var z = 0;
secTitle[z] = "Installation, Getting Started with OVP, and Cross-Compiling Applications";
secDescr[z] = "<a href=../Imperas_Installation_and_Getting_Started.pdf> Imperas_Installation_and_Getting_Started.pdf.</a> ";
secDescr[z] += "<br/><b>Contents:</b><br/>Initial readme and installation notes.<br/>Where and how to get MinGW (Minimalist Gnu system for Windows) and MSYS shell.<br/>How to download and install the different processor toolkits from the OVPworld.org site.<br/><b>Cross Compiling Applications</b> for the different processors (GCC etc).<br/>An introduction to Compiling platforms & harnesses written with the OVP ICM API.<br/>Loading applications to run on embedded processor models.<br/>Putting it all together with an application running on an OVP platform.<br/>A more detailed look at cross compiling applications on Windows.";
z++;

secTitle[z] = "Creating, Modifying, and compiling platforms using the OVP ICM API";
secFile[z] = "OVPsim_and_CpuManager_User_Guide.pdf";
secDescr[z] = "<b>Contents:</b><br/>An introduction to creating platforms. Building simple single processor platforms.<br/>Creating the Model instance. Loading an executable.<br/>Compiling a Platform C file. Running a simulation. Simulation options with ICM attributes.<br/>Model Tracing. User Attributes. Reading and writing CPU registers.<br/>Generating Disassembly output. Simulating one instruction. Instruction counts.<br/>Semihosting. Accessing processor memory. Adding memory watchpoints.<br/>External memory. Debugging bus connections. Attaching a debugger.<br/>Multiprocessor support.";
z++;

secTitle[z] = "<a href=../api/icm/html/index.html> Doxygen ICM API : Function Reference from headers.</a> ";
secDescr[z] = "Browsable walk through the header files of the C and C++ platform building API.";
z++;

secTitle[z] = "Control File User Guide";
secFile[z]  = "OVP_Control_File_User_Guide.pdf";
secDescr[z] = "<b>Contents:</b><br/>How a Control File can be used to override the configuration of a virtual platform and its components. How it can be used to control the simulation. This allows changes to a platform for which a user has no source or to allow changes without the need to re-compile. ";
secDescr[z] += "It also allows control when the model is buried in, for example a SystemC platform.<br/>";
secDescr[z] += "Examples of uses of a control file: debugger connection, loading programs/libraries, overriding model parameters, control of time precision, quantum size, finish times, verbosity and message control.";
z++;

secTitle[z] = "Using OVP models with OSCI SystemC TLM2.0 platforms to gain 200-500 MIPS performance";
secFile[z] = "OVPsim_Using_OVP_Models_in_SystemC_TLM2.0_Platforms.pdf";
secDescr[z] = "<b>Contents:</b><br/>Using OVPsim running with a SystemC TLM2.0 platform. <br/>Compiling the TLM2.0 examples with OVP models.<br/>Instancing fast OVP CPU models in a TLM2.0 platform.<br/>SystemC TLM2.0 platform construction, stack size, DMI, and simulation artifacts.<br/>Using OVP Peripheral models in TLM2.0 platforms.<br/>Detailed workthrough of example platform.<br/>Common problems.";
z++;

secTitle[z] = "Using OVP Fast Processor Models with OVPsim and other simulators";
secFile[z] = "OVP_Guide_To_Using_Processor_Models.pdf";
secDescr[z] = "Description of OVP Fast Processor Models and how to use them.<br/>Also see the model variant specific documentation for very detailed information.";
z++;

secTitle[z] = "Debugging Applications with GDB running on OVP platforms";
secFile[z] = "OVPsim_Debugging_Applications_with_GDB_User_Guide.pdf";
secDescr[z] = "How to use GDB with OVPsim.";
z++;

secTitle[z] = "Debugging Applications with Eclipse CDT running on OVP platforms";
secFile[z] = "OVPsim_Debugging_Applications_with_Eclipse_User_Guide.pdf";
secDescr[z] = "How to use Eclipse CDT with OVPsim.<br/>There is also a video walking through this guide - it shows installation, setup and use - <a href=http://www.ovpworld.org/download_demos.php#sectionDemoDebug>click here</a>.";
z++;

secTitle[z] = "Debugging Applications with ARM DS-5 running on OVP platforms";
secDescr[z] = "<a href=../imperas/Imperas_Debugging_with_ARM_DS-5.pdf> Imperas_Debugging_with_ARM_DS-5.pdf.</a> ";
secDescr[z] += "<br/><b>Contents:</b><br/>Using ARM DS-5 with OVP Virtual Platforms.<br/>How to setup ARM DS-5 for use with OVP Virtual Platforms.";
secDescr[z] += "<br/>Examples using DS-5 with OVP platforms of Cortex-A5UP and CortexA9MPx2 (SMP).";
z++;

secTitle[z] = "Debugging Applications with INSIGHT running on OVP platforms";
secFile[z] = "OVPsim_Debugging_with_INSIGHT_User_Guide.pdf";
secDescr[z] = "How to use INSIGHT with OVPsim.";
z++;

secTitle[z] = "Creating Behavioral (Peripheral) components using BHM/PPM APIs and adding them to Platforms";
secFile[z] = "OVP_Peripheral_Modeling_Guide.pdf";
secDescr[z] = "<b>Contents:</b><br/>How to write and use behavioral components.<br/>Overview of OVP simulation.<br/>BHM introduction - for behavior.<br/>PPM introduction - for peripheral platform interconnections.<br/>Function interception.<br/>A multithreaded DMA example.<br/>Interrupts and signals.";
z++;

secTitle[z] = "Function by function Reference Guide for BHM / PPM APIs.";
secFile[z] = "OVP_BHM_PPM_Function_Reference.pdf";
secDescr[z] = "Description of each BHM and PPM Function.";
z++;

secTitle[z] = "<a href=../api/peripheral/html/index.html> Doxygen BHM/PPM APIs : Function Reference from headers</a>";
secDescr[z] = " Browsable walk through the header files.";
z++;

secTitle[z] = "Creating Instruction Accurate Processor models using the VMI API";
secFile[z] = "OVP_Processor_Modeling_Guide.pdf";
secDescr[z] = "<b>Contents:</b><br/>How to write and use processor models using the Virtual Machine Interface (VMI API).<br/>Simulation overview. Introduction to Processor Modeling. Creating a processor outline.<br/>Endianness. Fetching Instructions. Attribute tables.<br/>Building a test platform. Creating an application testcase.<br/>Implementing the Instruction Decode. More complex decoders.<br/>Implementing an Instruction Disassembler. Implementing simple behavior.<br/>An introduction to Code Morphing.<br/>Processor flags and register dumping. Jump instructions.<br/>Memory access instructions. Fibonnacci example.<br/>Modeling Exceptions. Modeling mode-dependent behavior.<br/>Timers. Modeling interrupts. Debug Interface.<br/>Implementing Virtual Memory. Higher speed processor models.<br/>Semihosting. Implementing efficient Cache and memory subsystems.";
z++;

secTitle[z] = "VMI Morph Time (VMI MT) API Reference Guide";
secFile[z] = "OVP_VMI_Morph_Time_Function_Reference.pdf";
secDescr[z] = "Description of each VMI Morph Time Function";
z++;

secTitle[z] = "VMI Run Time (VMI RT) API Reference Guide";
secFile[z] = "OVP_VMI_Run_Time_Function_Reference.pdf";
secDescr[z] = "Description of each VMI Run Time Function";
z++;

secTitle[z] = "VMI Memory Modeled Component (VMI MMC) API Reference Guide";
secFile[z] = "OVP_VMI_Memory_Model_Component_Function_Reference.pdf";
secDescr[z] = "Description of each MMC Function (includes Cache Modeling).";
z++;

secTitle[z] = "VMI Operating System support (VMI OS) API Reference Guide";
secFile[z] = "OVP_VMI_OS_Support_Function_Reference.pdf";
secDescr[z] = "Description of each VMI OS Function.";
z++;

secTitle[z] = "VMI Programmers Views (VMI VIEW) API Reference Guide.";
secFile[z] = "OVP_VMI_View_Function_Reference.pdf";
secDescr[z] = "Description of each function of VMI View API for creating Programmers View objects and events in models.";
z++;

secTitle[z] = "Doxygen VMI API : Function Reference from headers";
secDescr[z] = "<a href=../api/vmi/html/index.html>Doxygen VMI API : Function Reference from headers</a>";
secDescr[z] += "<br/>Browsable walk through the header files.";
z++;

secTitle[z] = "Building Semihost Libraries (virtualizing host OS functions)";
secFile[z]  = "OVP_Processor_Modeling_Guide.pdf";
secDescr[z] = "Intercept libraries for semi-hosting are introduced in the OVP_Processor_Modeling_Guide.pdf document.";
secDescr[z] += "<br/>An example library for newlib is available as a template in the OVPsim download examples of processors, as 19.or1kSemiHosting.";
z++;

secTitle[z] = "<a href=../api/base/html/index.html> Doxygen simulator intercept API : Function Reference from headers.</a>";
secDescr[z] = "Browsable walk through the header files of the simple API which can be used by simulated applications to query and control the simulator.";
z++;
