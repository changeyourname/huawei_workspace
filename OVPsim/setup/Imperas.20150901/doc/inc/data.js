var dataExists = 1; // must exist and be set to 1

var pageTitle = "Imperas/OVP Documentation";
var documentName = "Imperas / OVP Main Documentation Page";
var headerGraphic = "doc_header.gif";
//var webSite = "www.mine.com"; // optional

//var versionDate = "For Product v20101004.0 created Wed Oct  6 15:18:24 2010";

// internal variables
if(typeof dDir == "undefined") {
	var dDir = "../"; // or ./ if in main dir
}
if(typeof docDir == "undefined") {
	var docDir = "./"; // or ./doc if in main dir
}

var secTitle = new Array();
var secFile = new Array();
var secDescr = new Array();
var secExist = new Array();
var secDoxygen = new Array();

var z = 0;

secTitle[z]  = "Getting Started with Imperas and OVP";
secDescr[z]  = "When you download different packages from Imperas and OVPworld you get the documentation populated.";
secDescr[z] += "<br/><br/>An installation of the Imperas Developer product does include the OVP documentation.";
secDescr[z] += "<br/><br/>An installation of the Imperas SDK product does include the OVP and Imperas Developer documentation.";
secDescr[z] += "<br/><br/>An installation of OVP does not include any of the Imperas software or documentation.";
z++;

secTitle[z]  = "OVP: Open Virtual Platforms Documentation";
secDescr[z]  = "For documentation on the <a href='"+docDir+"/ovp/index.html'>Open Virtual Platforms (OVP) Products click here</a>.";
secExist[z]  = "ovpExists";
var ovpExists;
z++;

secTitle[z]  = "OVP: Open Virtual Platforms CHANGELOG";
secDescr[z]  = "For news on the latest changes in the <a href='"+dDir+"/CHANGELOG.OVP.TXT'>Open Virtual Platforms (OVP) Products click here</a>.";
secExist[z]  = "ovpExists";
var ovpExists;
z++;

secTitle[z]  = "Imperas Developer Documentation";
secDescr[z]  = "For documentation on the <a href='"+docDir+"/imperas/index.html'>Imperas Developer Products click here</a>."; // changed
secExist[z]  = "imperasDEVExists";
var imperasDEVExists;
z++;

secTitle[z]  = "Imperas SDK Documentation";
secDescr[z]  = "For documentation on the <a href='"+docDir+"/imperas/index.html'>Imperas SDK Products click here</a>."; // changed
secExist[z]  = "imperasSDKExists";
var imperasSDKExists;
z++;

secTitle[z]  = "CHANGELOG Imperas SDK";
secDescr[z]  = "For news on the latest changes in the <a href='"+dDir+"/CHANGELOG.SDK.txt'>Imperas SDK Products click here</a>.";
secExist[z]  = "imperasSDKExists";
var imperasSDKExists;
z++;

secTitle[z]  = "CHANGELOG Imperas iGen"; 
secDescr[z]  = "For news on the latest changes in the <a href='"+dDir+"CHANGELOG.iGen.txt'>Imperas iGen click here</a>.";
secExist[z]  = "imperasDEVExists";
var imperasDEVExists;
z++;

secTitle[z]  = "CHANGELOG Imperas CpuManager Simulator"; // new
secDescr[z]  = "For news on the latest changes in the <a href='"+dDir+"CHANGELOG.CpuManager.txt'>Imperas CpuManager Simulator click here</a>.";
secExist[z]  = "imperasDEVExists";
var imperasDEVExists;
z++;

secTitle[z]  = "OVPsimMIPS: Instruction Accurate Simulation from MIPS Technologies Inc.";
secDescr[z]  = "For documentation on the <a href='"+docDir+"/MIPS/index.html'>MIPS IASim products</a>.";
secExist[z]  = "MIPSExists";
var MIPSExists;
z++;

secTitle[z]  = "OVPsimMIPS: CHANGELOG";
secDescr[z]  = "For news on the latest changes in the <a href='"+dDir+"/CHANGELOG.OEM.MIPS.TXT'>OVPsimMIPS Products click here</a>.";
secExist[z]  = "MIPSExists";
var MIPSExists;
z++;

secTitle[z]  = "Cadence: Documentation related to Cadence use of OVP / Imperas products.";
secDescr[z]  = "For documentation on the <a href='"+docDir+"/Cadence/index.html'>Cadence use of OVP/Imperas products</a>.";
secExist[z]  = "CadenceExists";
var CadenceExists;
z++;

/* add more sections if needed */