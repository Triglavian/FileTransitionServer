#include "PacketHandler.h"

PacketHandler::PacketHandler()
{

}

PacketHandler::~PacketHandler()
{

}

int PacketHandler::SendProtocolPacket(const SOCKET& socket, const Protocol& protocol)
{
	ClearPacket();
	char* ptr = packet.buf + sizeof(int);
	int packetSize = 0;

	memcpy(ptr, &protocol, sizeof(protocol));
	ptr = packet.buf;
	packetSize += sizeof(protocol);

	memcpy(ptr, &packetSize, sizeof(packetSize));
	packetSize += sizeof(packetSize);
	return send(socket, packet.buf, packetSize, 0);
}

int PacketHandler::SendBoolPacket(SOCKET socket, Protocol protocol, bool data)
{
	return SendPacket(socket, protocol, data);
}

int PacketHandler::SendIntPacket(SOCKET socket, Protocol protocol, int data)
{
	return SendPacket(socket, protocol, data);
}

int PacketHandler::SendStrPacket(SOCKET socket, Protocol protocol, std::string data)
{
	return SendPacket(socket, protocol, data);
}

int PacketHandler::RecvProtocolPacket(const SOCKET& socket, Protocol& protocol)
{
	ClearPacket();
	int retval = 0;
	int packetSize = 0;
	retval = recv(socket, (char*)&packetSize, sizeof(int), MSG_WAITALL);
	if (retval == SOCKET_ERROR) {
		std::cout << "recv() error" << std::endl;
		exit(0);
	}
	retval = recv(socket, packet.buf, packetSize, MSG_WAITALL);
	if (retval == SOCKET_ERROR) {
		std::cout << "recv() error" << std::endl;
		exit(0);
	}
	memcpy(&protocol, packet.buf, sizeof(protocol));
	return retval;
}

int PacketHandler::RecvBoolPacket(SOCKET socket, Protocol& protocol, bool* data)
{
	return RecvPacket(socket, protocol, data);
}

int PacketHandler::RecvIntPacket(SOCKET socket, Protocol& protocol, int* data)
{
	return RecvPacket(socket, protocol, data);
}

int PacketHandler::RecvStrPacket(SOCKET socket, Protocol& protocol, std::string* data)
{
	return RecvPacket(socket, protocol, data);
}

void PacketHandler::ClearPacket()
{
	ZeroMemory(packet.buf, BUFSIZE);
}
