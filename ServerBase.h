#pragma once
//#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <process.h>

#include <functional>
#include <vector>	

#include "ListenSocket.h"
#include "ClientSocket.h"
#include "FileTransition.h"
#include "ServerLogger.h"

#include "Char.h"
#include "Int.h"
#include "Float.h"
#include "Double.h"

class ServerBase
{
public:
	ServerBase(Int port = 9000);
	~ServerBase();
	void Run();
private:
	//base data
	WSADATA wsa;
	Int port;
	Int result;
	ListenSocket* lSocket;
	SOCKET newSocket;
	sockaddr_in clientAddr;
	std::vector<HANDLE*>* threadHandles;
	std::vector<ClientSocket*>* cSockets;
	CRITICAL_SECTION handleSection;
	CRITICAL_SECTION cSocketSection;

	//base function
	bool InitializeServer();
	bool IsWSAStartFailed();
	void AcceptClients();

	//service
	//std::vector<std::function<void(ClientSocket*)>> services;
	static unsigned int __stdcall StateSwitch(void* obj);
	FileTransition* fileTransition;
};