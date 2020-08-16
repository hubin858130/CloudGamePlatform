
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the FHNNETPORT_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// FHNNETPORT_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef FHNNETPORT_EXPORTS
#define FHNNETPORT_API __declspec(dllexport)
#else
#define FHNNETPORT_API __declspec(dllimport)
#endif

/************************************************************************
function:fhnnetport_getsocket
author: lllei 20080305
param:  remoteip: remote ip address
        remoteport: remote port
		sockettype: udp or tcp
		packettype: rtp or ts
		pvalue:a point to the return value, if packettype is rtp, its a point
		        to rtppacketport struct;
process: allocate port
return: 0:success
************************************************************************/
FHNNETPORT_API UINT fhnnetport_getsocket(char* remoteip, UINT remoteport,UINT sockettype,
						  UINT packettype, void* pvalue);
/************************************************************************
function:fhnnetport_releasesocket
author: lllei 20080305
param: 	ackettype: rtp or ts
		pvalue: a point to the return value of getsocket
		this function will not release this point
process: initial the dll,create msg module
return: 0:success; else :error
************************************************************************/
FHNNETPORT_API UINT fhnnetport_releasesocket(UINT packettype, void* pvalue);
