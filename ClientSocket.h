#pragma once
#include <WinSock2.h>
#include "PacketHandler.h"
#include "Sessions.h"
#include "MainState.h"
#include "ServerLogger.h"

class ClientSocket
{
public:
	ClientSocket(const SOCKET& _socket, const sockaddr_in& _clientAddr);
	ClientSocket() = delete;
	ClientSocket(const ClientSocket& clientSocket) = delete;
	~ClientSocket();

	//getter
	SOCKET GetSocket();
	MainState GetMainState();
	Protocol GetProtocol();
	
	//setter
	void SetMainState(const MainState& _state);
	void SetProtocol(const Protocol& _protocol);
	//service
	void ModifyStateWithProtocol();
	bool ValidateProtocol(const Protocol& protocol);

	//packet sender
	Int SendProtocolPacket(const Protocol& protocol) const;
	Int SendProtocolPacket() const;
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
	Int RecvStrPacket(std::string& data);
	Int RecvCStrPacket(Char* data, Int size);

private:
	//client socket base data
	SOCKET _socket;
	sockaddr_in clientAddr;
	PacketHandler* packetHandler;
	Int result;
	MainState mainState;
	Protocol protocol;

};

