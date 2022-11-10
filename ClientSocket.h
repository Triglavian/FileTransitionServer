#pragma once
#include <WinSock2.h>
#include "PacketHandler.h"
#include "Sessions.h"
#include "MainState.h"
#include <stack>

class ClientSocket
{
public:
	ClientSocket(const SOCKET& _socket = INVALID_SOCKET);
	~ClientSocket();

	//getter
	SOCKET GetSocket();
	MainState GetMainState();
	Protocol GetProtocol();
	//ISession* GetSession();	//can't dynamic cast if const return
	
	//setter
	void SetMainState(const MainState& _state);
	//service
	void ModifyStateWithProtocol();
	bool ValidateProtocol(const Protocol& protocol);
	//void AddNewSession(ISession* session);
	//void DeleteCurrentSession();

	//packet sender
	Int SendProtocolPacket(const Protocol& protocol) const;
	Int SendBoolPacket(const Protocol& protocol, const bool& flag) const;
	Int SendCharPacket(const Protocol& protocol, const Char& _char) const;
	Int SendIntPacket(const Protocol& protocol, const Int& _int) const;
	Int SendStrPacket(const Protocol& protocol, const std::string& str) const;
	Int SendCStrPacket(const Protocol& protocol, const Char data[], const Int& size);

	//packet receiver
	Int RecvProtocolPacket();
	Int RecvBoolPacket(bool& data);
	Int RecvCharPacket(Char& data);
	Int RecvIntPacket(Int& data);
	Int RectStrPacket(std::string& data);
	Int RecvCStrPacket(Char* data, Int size);

private:
	//client socket base data
	SOCKET _socket;
	sockaddr_in clientAddr;
	PacketHandler* packetHandler;
	Int result;
	MainState mainState;
	Protocol protocol;
	//std::stack<ISession*>* sessions;

	//

	ClientSocket(const ClientSocket& clientSocket);
};

