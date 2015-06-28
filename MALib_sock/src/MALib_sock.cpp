#include "..\include\MALib_sock.h"

#ifdef _MA_SOCK_H_
_MALIB_BEGIN

typedef struct SOCKHANDLE
{
	SOCKHANDLE()
	{
		memset(this, 0, sizeof(SOCKHANDLE));
	}
	~SOCKHANDLE()
	{
		memset(this, 0, sizeof(SOCKHANDLE));
	}

	SOCKET socket;
	sockaddr_in address;

	int address_size;
	bool connected;
} SOCKHANDLE;

WSAData SOCK_SockInfo;
SOCKHANDLE* SOCK_MySock = 0;

ULONG SOCK_Address = 0;
USHORT SOCK_Port = 0;

SOCK_OnCommunicateCallback SOCK_OnSend = 0;
SOCK_OnCommunicateCallback SOCK_OnReceive = 0;

bool SOCK_IsServer = false;
bool SOCK_Initialized = false;
bool SOCK_Connected = false;
int SOCK_LastError = 0;

SOCKHANDLE* CreateSock()
{
	SOCKHANDLE* sock = new SOCKHANDLE;
	sock->socket = INVALID_SOCKET;
	return sock;
}
void DestroySock(SOCKHANDLE** sock)
{
	if (sock == 0 || *sock == 0) return;
	closesocket((*sock)->socket);
	delete *sock;
	*sock = 0;
}

ulong __stdcall SendThread(void* parameter)
{
	if (SOCK_OnSend == 0) return 0;
	while (true)
	{
		if (!SOCK_Connected) break;
		static char buffer[SOCK_BUFFERSIZE];
		memset(buffer, 0, sizeof(char) * SOCK_BUFFERSIZE);
		int result = SOCK_OnSend(buffer, SOCK_BUFFERSIZE);
		bool failed = !SOCK_Send(buffer, SOCK_BUFFERSIZE);
		if (result == 0) break;
		Sleep(result);
	}
	return 0;
}
ulong __stdcall ReceiveThread(void* parameter)
{
	if (SOCK_OnReceive == 0) return 0;
	while (true)
	{
		if (!SOCK_Connected) break;
		static char buffer[SOCK_BUFFERSIZE];
		memset(buffer, 0, sizeof(char) * SOCK_BUFFERSIZE);
		bool failed = !SOCK_Receive(buffer, SOCK_BUFFERSIZE);
		int result = SOCK_OnReceive(buffer, SOCK_BUFFERSIZE);
		if (result == 0) break;
		Sleep(result);
	}
	return 0;
}

MALIB_API bool SOCK_Initialize(bool isServer)
{
	if (SOCK_Initialized) return false;
	WSAStartup(0x202, &SOCK_SockInfo);
	SOCK_IsServer = isServer;

	SOCK_Initialized = true;
	return true;
}
MALIB_API bool SOCK_Uninitialize()
{
	if (!SOCK_Initialized) return false;

	if (SOCK_Connected) SOCK_Disconnect();

	WSACleanup();
	SOCK_Initialized = false;
	return true;
}

MALIB_API bool SOCK_Connect(uint port, const string ip, SOCK_OnCommunicateCallback send, SOCK_OnCommunicateCallback receive)
{
	if (!SOCK_Initialized) return false;
	if (SOCK_Connected) return false;
	if (ip == 0 || port == 0) return false;
	
	SOCK_Port = htons(port);
	if (SOCK_IsServer) SOCK_Address = INADDR_ANY;
	else SOCK_Address = inet_addr(ip);

	if (SOCK_Address == INADDR_NONE)
	{
		SOCK_LastError = WSAGetLastError();
		return false;
	}
	
	SOCK_MySock = CreateSock();
	SOCK_MySock->socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	SOCK_MySock->address.sin_family = AF_INET;
	SOCK_MySock->address.sin_port = SOCK_Port;
	SOCK_MySock->address.sin_addr.S_un.S_addr = SOCK_Address;
	SOCK_MySock->address_size = sizeof(SOCK_MySock->address);

	if (SOCK_MySock->socket == INVALID_SOCKET)
	{
		SOCK_LastError = WSAGetLastError();
		return false;
	}

	if (SOCK_IsServer)
	{
		int result = bind(SOCK_MySock->socket, (sockaddr*)&SOCK_MySock->address, SOCK_MySock->address_size);
		if (result != 0)
		{
			SOCK_Connected = false;
			result = WSAGetLastError();
			SOCK_LastError = result;
			return false;
		}
	}

	SOCK_MySock->connected = true;
	
	SOCK_OnSend = send;
	SOCK_OnReceive = receive;

	CreateThread(0, 0, SendThread, 0, 0, 0);
	CreateThread(0, 0, ReceiveThread, 0, 0, 0);
	
	SOCK_Connected = true;
	return true;
}

MALIB_API bool SOCK_Disconnect()
{
	if (!SOCK_Initialized) return false;
	if (!SOCK_Connected) return false;
	
	if (SOCK_MySock != 0) DestroySock(&SOCK_MySock);

	TerminateThread(SendThread, 0);
	TerminateThread(ReceiveThread, 0);
	
	SOCK_Connected = false;
	return true;
}

MALIB_API string SOCK_GetMyIP()
{
	if (!SOCK_Initialized) return false;
	
	string ip = 0;
	char* hostname = new char[64];
	gethostname(hostname, 64);

	addrinfo* result = 0;
	int retreival = getaddrinfo(hostname, 0, 0, &result);
	addrinfo* link = 0;
	for (link = result; link != 0; link = link->ai_next)
	{
		if (link->ai_addr->sa_family == AF_INET)
		{
			SOCKADDR_IN* sockaddr = (SOCKADDR_IN*)link->ai_addr;
			ip = inet_ntoa(sockaddr->sin_addr);
		}
	}
	delete [] hostname;
	return ip;
}
MALIB_API ulong SOCK_GetAddressHandle()
{
	return SOCK_Address;
}
MALIB_API ushort SOCK_GetPortHandle()
{
	return SOCK_Port;
}
MALIB_API bool SOCK_CheckConnection()
{
	return SOCK_Connected;
}
MALIB_API int SOCK_CheckError()
{
	return SOCK_LastError;
}

void FormatBuffer(__int32* dest, uint size, char* src, uint bytes)
{
	if (dest == 0 || size < 1 || src == 0 || bytes < 1) return;

	uint stride = sizeof(__int32);
	uint remainder = bytes % stride;
	char* scratch = 0;
	if (remainder != 0)
	{
		scratch = new char[bytes + remainder];
		memset(scratch, 0, bytes + remainder);
		memcpy(scratch, src, bytes);
	}
	else scratch = src;

	uint read = 0;
	for (uint i = 0; i < bytes; i += 4)
	{
		if (read >= size) break;
		__int32 v = *((__int32*)(scratch + i));
		v = htonl(v);
		dest[read] = v;
		read++;
	}
	if (remainder != 0) delete [] scratch;
}
void UnformatBuffer(void* dest, uint size, char* src, uint bytes)
{
	if (dest == 0 || size < 1 || src == 0 || bytes < 1) return;
	
	char* out = (char*)dest;
	for (uint i = 0; i < bytes; i += 4)
	{
		__int32 v = *((__int32*)(src + i));
		v = ntohl(v);
		*((__int32*)(out + i)) = v;
	}
}

MALIB_API bool SOCK_Send(string buffer, uint bytes)
{
	if (!SOCK_Connected || !SOCK_Initialized || SOCK_MySock == 0 || !SOCK_MySock->connected || buffer == 0 || bytes < 1) return false;

	int result = sendto(SOCK_MySock->socket, buffer, bytes, 0, (sockaddr*)&SOCK_MySock->address, SOCK_MySock->address_size);
	if (result != 0)
	{
		result = WSAGetLastError();
		SOCK_LastError = result;
		return false;
	}

	return true;
}
MALIB_API bool SOCK_Receive(string buffer, uint bytes)
{
	if (!SOCK_Connected || !SOCK_Initialized || SOCK_MySock == 0 || !SOCK_MySock->connected || buffer == 0 || bytes < 1) return false;

	int result = recvfrom(SOCK_MySock->socket, buffer, bytes, 0, (sockaddr*)&SOCK_MySock->address, &SOCK_MySock->address_size);
	if (result != 0)
	{
		result = WSAGetLastError();
		SOCK_LastError = result;
		return false;
	}

	return true;
}

_MALIB_END
#endif

void __stdcall DllMain()
{
	return;
}