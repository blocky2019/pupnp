///////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2000-2003 Intel Corporation 
// All rights reserved. 
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met: 
//
// * Redistributions of source code must retain the above copyright notice, 
// this list of conditions and the following disclaimer. 
// * Redistributions in binary form must reproduce the above copyright notice, 
// this list of conditions and the following disclaimer in the documentation 
// and/or other materials provided with the distribution. 
// * Neither name of Intel Corporation nor the names of its contributors 
// may be used to endorse or promote products derived from this software 
// without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL INTEL OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY 
// OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
///////////////////////////////////////////////////////////////////////////


#ifndef UPNPAPI_H
#define UPNPAPI_H


#include "client_table.h"
#include "upnp.h"
//#include "../ssdp/ssdplib.h"
#include "VirtualDir.h"		/* for struct VirtualDirCallbacks */


#define MAX_INTERFACES 256

#define DEFAULT_INTERFACE 1

#define DEV_LIMIT 200

#define NUM_HANDLE 200

#define DEFAULT_MX 5

#define DEFAULT_MAXAGE 1800

#define DEFAULT_SOAP_CONTENT_LENGTH 16000
#define MAX_SOAP_CONTENT_LENGTH 32000

extern size_t g_maxContentLength;

// 30-second timeout
#define UPNP_TIMEOUT	30

typedef enum {HND_INVALID=-1,HND_CLIENT,HND_DEVICE} Upnp_Handle_Type;

// Data to be stored in handle table for
struct Handle_Info
{
    Upnp_Handle_Type HType;
    Upnp_FunPtr  Callback; // Callback function pointer.
    char * Cookie;

    // Device Only
#ifdef INCLUDE_DEVICE_APIS
    char  DescURL[LINE_SIZE];   // URL for the use of SSDP
    char  DescXML[LINE_SIZE];   // XML file path for device 
                                //description

    int MaxAge;                 // Advertisement timeout
    IXML_Document *DescDocument;// Description parsed in 
                                //terms of DOM document 
    IXML_NodeList *DeviceList;  // List of devices in the 
                                //description document
    IXML_NodeList *ServiceList; // List of services in the 
                                // description document
    service_table ServiceTable; //table holding subscriptions and 
                                //URL information
    int MaxSubscriptions;
    int MaxSubscriptionTimeOut;
    int DeviceAf;               // Address family: AF_INET or AF_INET6
#endif
     
    // Client only
#ifdef INCLUDE_CLIENT_APIS
    ClientSubscription *ClientSubList; // client subscription list
    LinkedList SsdpSearchList; // active ssdp searches   
#endif
    int   aliasInstalled;       // 0 = not installed; otherwise installed
};

extern ithread_rwlock_t GlobalHndRWLock;
Upnp_Handle_Type GetHandleInfo(int Hnd, struct Handle_Info **HndInfo); 

#define HandleLock() HandleWriteLock()

#define HandleWriteLock()  \
	UpnpPrintf(UPNP_INFO, API, __FILE__, __LINE__, "Trying a write lock"); \
	ithread_rwlock_wrlock(&GlobalHndRWLock); \
	UpnpPrintf(UPNP_INFO, API, __FILE__, __LINE__, "Write lock acquired");

#define HandleReadLock()  \
	UpnpPrintf(UPNP_INFO, API, __FILE__, __LINE__, "Trying a read lock"); \
	ithread_rwlock_rdlock(&GlobalHndRWLock); \
	UpnpPrintf(UPNP_INFO, API, __FILE__, __LINE__, "Read lock acquired");

#define HandleUnlock() \
	UpnpPrintf(UPNP_INFO, API,__FILE__, __LINE__, "Trying Unlock"); \
	ithread_rwlock_unlock(&GlobalHndRWLock); \
	UpnpPrintf(UPNP_INFO, API, __FILE__, __LINE__, "Unlocked rwlock");

Upnp_Handle_Type GetClientHandleInfo(int *client_handle_out, 
                                     struct Handle_Info **HndInfo);
Upnp_Handle_Type GetDeviceHandleInfo( const int AddressFamily,
                                      int *device_handle_out, 
                                      struct Handle_Info **HndInfo);


extern char gIF_NAME[LINE_SIZE];
extern char gIF_IPV4[22];        // INET_ADDRSTRLEN
extern char gIF_IPV6[65];        // INET6_ADDRSTRLEN
extern int  gIF_INDEX;

extern unsigned short LOCAL_PORT_V4;
extern unsigned short LOCAL_PORT_V6;

extern Upnp_SID gUpnpSdkNLSuuid;     // NLS uuid.

extern TimerThread gTimerThread;
extern ThreadPool gRecvThreadPool;
extern ThreadPool gSendThreadPool;
extern ThreadPool gMiniServerThreadPool;

typedef enum {
    SUBSCRIBE,
    UNSUBSCRIBE,
    DK_NOTIFY,
    QUERY,
    ACTION,
    STATUS,
    DEVDESCRIPTION,
    SERVDESCRIPTION,
    MINI,
    RENEW} UpnpFunName;

struct  UpnpNonblockParam 
{ 
    UpnpFunName  FunName;
    int   Handle;
    int   TimeOut;
    char  VarName[NAME_SIZE];
    char  NewVal[NAME_SIZE];
    char  DevType[NAME_SIZE];
    char  DevId[NAME_SIZE];
    char  ServiceType[NAME_SIZE];
    char  ServiceVer[NAME_SIZE];
    char  Url[NAME_SIZE];
    Upnp_SID   SubsId;
    char  *Cookie;
    Upnp_FunPtr Fun;
	IXML_Document *Header;
    IXML_Document *Act;
    struct DevDesc *Devdesc;
};


extern virtualDirList *pVirtualDirList;
extern struct VirtualDirCallbacks virtualDirCallback;


typedef enum { WEB_SERVER_DISABLED, WEB_SERVER_ENABLED } WebServerState;

#define E_HTTP_SYNTAX -6

#ifdef WIN32
int WinsockInit();
#endif
int UpnpInitPreamble();
int UpnpInitMutexes();
int UpnpInitThreadPools();
int UpnpInitStartServers(unsigned short DestPort); 
int UpnpGetIfInfo(const char *IfName);
void InitHandleList();
int GetFreeHandle();
int FreeHandle(int Handle);
void UpnpThreadDistribution(struct UpnpNonblockParam * Param);


void AutoAdvertise(void *input); 
int getlocalhostname(char *out, const int out_len);

extern WebServerState bWebServerState;


#endif /* UPNPAPI_H */

