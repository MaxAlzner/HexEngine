#pragma once

#include <MALib.h>

#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "Ws2_32.lib")

#ifndef _MA_SOCK_H_
#define _MA_SOCK_H_
_MALIB_BEGIN

struct MALIB_API SOCKHANDLE;
typedef struct MALIB_API SOCKHANDLE SOCKHANDLE;

#define SOCK_BUFFERSIZE 4096

typedef int (*SOCK_OnCommunicateCallback)(char* buffer, uint bytes);

MALIB_API bool SOCK_Initialize(bool isServer = false);
MALIB_API bool SOCK_Uninitialize();

MALIB_API bool SOCK_Connect(uint port, const string ip, SOCK_OnCommunicateCallback send, SOCK_OnCommunicateCallback receive);
MALIB_API bool SOCK_Disconnect();

MALIB_API string SOCK_GetMyIP();
MALIB_API ulong SOCK_GetAddressHandle();
MALIB_API ushort SOCK_GetPortHandle();
MALIB_API bool SOCK_CheckConnection();
MALIB_API int SOCK_CheckError();

MALIB_API bool SOCK_Send(string buffer, uint size);
MALIB_API bool SOCK_Receive(string buffer, uint size);

_MALIB_END
#endif