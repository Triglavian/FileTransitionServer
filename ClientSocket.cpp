#include "ClientSocket.h"
#include <WS2tcpip.h>

ClientSocket::ClientSocket(const SOCKET& _socket, const sockaddr_in& _clientAddr)
{
	this->_socket = _socket;
	this->packetHandler = new PacketHandler();
	this->mainState = MAIN;
	this->clientAddr = _clientAddr;
	this->protocol = P_INVALID;

	std::string addr = inet_ntoa(clientAddr.sin_addr);
	ServerLogger::PrintLog("Connected : Ip = " + addr + ", Port : " + Int(ntohs(clientAddr.sin_port)).ToString());
}

ClientSocket::~ClientSocket()
{
	if (packetHandler != nullptr) delete packetHandler;

	std::string addr = inet_ntoa(clientAddr.sin_addr);
	ServerLogger::PrintLog("Disconnected : Ip = " + addr + ", Port : " + Int(ntohs(clientAddr.sin_port)).ToString());
}

SOCKET ClientSocket::GetSocket()
{
	return _socket;
}

MainState ClientSocket::GetMainState()
{
	return mainState;
}
Protocol ClientSocket::GetProtocol()
{
	return protocol;
}

void ClientSocket::SetMainState(const MainState& _state)
{
	mainState = _state;
}
void ClientSocket::SetProtocol(const Protocol& _protocol)
{
	this->protocol = _protocol;
}

void ClientSocket::ModifyStateWithProtocol()
{
	if (packetHandler->RecvProtocolPacket(_socket, protocol) < 0) 
	{
		mainState = DISCON;
		return;
	}
	switch (protocol)
	{
		case P_TRANS:
			mainState = FILETRANS;
			break;
		case P_DISCON:
			mainState = DISCON;
			return;
		default:
			packetHandler->SendProtocolPacket(_socket, P_INVALID);
			mainState = MAIN;
			break;
	}
}

bool ClientSocket::ValidateProtocol(const Protocol& protocol)
{
	return this->protocol == protocol;
}


Int ClientSocket::SendProtocolPacket(const Protocol& protocol) const
{
	return packetHandler->SendProtocolPacket(_socket, protocol);
}

Int ClientSocket::SendProtocolPacket() const
{
	return packetHandler->SendProtocolPacket(_socket, this->protocol);;
}
 
Int ClientSocket::SendBoolPacket(const Protocol& protocol, const bool& flag) const
{
	return packetHandler->SendBoolPacket(_socket, protocol, flag);
}

Int ClientSocket::SendCharPacket(const Protocol& protocol, const Char& _char) const
{
	return packetHandler->SendCharPacket(_socket, protocol, _char.ToChar());
}

Int ClientSocket::SendIntPacket(const Protocol& protocol, const Int& _int) const
{
	return packetHandler->SendIntPacket(_socket, protocol, _int.ToInt());
}

Int ClientSocket::SendStrPacket(const Protocol& protocol, const std::string& str) const
{
	return packetHandler->SendStrPacket(_socket, protocol, str);
}

Int ClientSocket::SendCStrPacket(const Protocol& protocol, const Char data[], const Int& size)
{
	return packetHandler->SendCStrPacket(_socket, protocol, data, size);
}

Int ClientSocket::RecvProtocolPacket()
{
	return packetHandler->RecvProtocolPacket(_socket, protocol);
}

Int ClientSocket::RecvBoolPacket(bool& data)
{
	return packetHandler->RecvBoolPacket(_socket, protocol, data);
}

Int ClientSocket::RecvCharPacket(Char& data)
{
	return packetHandler->RecvCharPacket(_socket, protocol, data.ToCharRef());
}

Int ClientSocket::RecvIntPacket(Int& data)
{
	return packetHandler->RecvIntPacket(_socket, protocol, data.ToIntRef());
}

Int ClientSocket::RectStrPacket(std::string& data)
{
	return packetHandler->RecvStrPacket(_socket, protocol, data);
}

Int ClientSocket::RecvCStrPacket(Char* data, Int size)
{
	return packetHandler->RecvCStrPacket(_socket, protocol, data, size);
}