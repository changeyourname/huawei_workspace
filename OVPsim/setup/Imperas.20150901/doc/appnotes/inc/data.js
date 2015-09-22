var dataExists = 1; // must exist and be set to 1

var pageTitle = "Imperas/OVP Application Notes";
var documentName = "Application Notes";
var headerGraphic = "doc_header.gif";

//var versionDate = "(October 10) 20101004.0"; 

var secTitle = new Array();
var secFile = new Array();
var secDescr = new Array();
var secExist = new Array();
var secDoxygen = new Array();

var z = 0;

secTitle[z]  = "ARM TrustZone Platform Modeling Application Note";
 secFile[z]  = "Imperas_ARM_TrustZone_Platform_Modeling_Application_Note.pdf";
secDescr[z]  = "The ARM TrustZone technology adds a secure mode to the ARM processor architecture and additional security signals to the AMBA bus, which are used by TrustZone-aware peripherals to prevent access to certain bus addresses when the processor (or other bus master) is not in secure mode.";
secDescr[z] += "<br/><br/>As ARM TrustZone features are used for embedded systems, it becomes important to be able to comprehensively test the software that makes use of the TrustZone features. Key to comprehensive testing is the performance, controllability and visibility that virtual platforms provide.";
secDescr[z] += "<br/><br/>This document focuses on best known methods for modeling TrustZone-aware peripherals in OVP to achieve optimal performance.";
z++;



/* add more sections if needed */