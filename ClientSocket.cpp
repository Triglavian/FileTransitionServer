#include "ClientSocket.h"

ClientSocket::ClientSocket(const SOCKET& _socket)
{
	this->_socket = _socket;
	packetHandler = new PacketHandler();
	//sessions = new std::stack<ISession*>();
	//sessions->push(new MainSession());
	mainState = MAIN;
}

ClientSocket::~ClientSocket()
{
	/*
	if (sessions != nullptr) 
	{
		for (; !sessions->empty(); sessions->pop())
		{
			delete sessions->top();
		}
		delete sessions;
	}
	*/
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
Protocol ClientSocket::GetProtocol()
{
	return protocol;
}
/*
ISession* ClientSocket::GetSession()
{
	return sessions->top();
}
*/
void ClientSocket::SetMainState(const MainState& _state)
{
	mainState = _state;
}
/*
void ClientSocket::AddNewSession(ISession* session)
{
	sessions->push(session);
}
void ClientSocket::DeleteCurrentSession()
{
	if (sessions->size() < 1) return;
	delete sessions->top();
	sessions->pop();
}
*/

void ClientSocket::ModifyStateWithProtocol()
{
	packetHandler->RecvProtocolPacket(_socket, protocol);
	switch (protocol)
	{
		case P_TRANS:
			mainState = FILETRANS;
			break;
		default:
			packetHandler->SendProtocolPacket(_socket, P_INVALID);
			mainState = MAIN;
			break;
	}
}	

Int ClientSocket::SendProtocolPacket(const Protocol& protocol) const
{
	return packetHandler->SendProtocolPacket(_socket, protocol);
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

ClientSocket::ClientSocket(const ClientSocket& clientSocket)
{

}
