#pragma once
#include <WinSock2.h>
#include "PacketHandler.h"
#include "Sessions.h"
#include "MainState.h"

class ClientSocket
{
public:
	ClientSocket(const SOCKET& _socket = INVALID_SOCKET);
	~ClientSocket();

	//getter
	SOCKET GetSocket();
	MainState GetMainState();
	ISession* GetSession();	//can't dynamic cast if const return

	//setter
	void SetMainState(const MainState& _state);

private:
	//client socket base data
	SOCKET _socket;
	sockaddr_in clientAddr;
	PacketHandler* packetHandler;
	Int result;
	MainState mainState;
	ISession* session;
	ClientSocket(const ClientSocket& clientSocket);
};

