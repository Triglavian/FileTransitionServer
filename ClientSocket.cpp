#include "ClientSocket.h"

ClientSocket::ClientSocket(const SOCKET& _socket)
{
	this->_socket = _socket;
	packetHandler = new PacketHandler();
	session = new MainSession();
	mainState = MAIN;
}

ClientSocket::~ClientSocket()
{
	if (session != nullptr) delete session;
	if (packetHandler != nullptr) delete packetHandler;
}

SOCKET ClientSocket::GetSocket()
{
	return _socket;
}

MainState ClientSocket::GetMainState()
{
	return mainState;
}

ISession* ClientSocket::GetSession()
{
	return session;
}

void ClientSocket::SetMainState(const MainState& _state)
{
	mainState = _state;
}

ClientSocket::ClientSocket(const ClientSocket& clientSocket)
{

}
