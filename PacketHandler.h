#pragma once
#include "Protocol.h"
#include "Packet.h"
#include <winsock2.h>
#include "Char.h"
#include "Int.h"

class PacketHandler
{
public:
	PacketHandler();
	~PacketHandler();
	
	//send packet
	int SendProtocolPacket(const SOCKET& socket, const Protocol& protocol);
	int SendBoolPacket(SOCKET socket, Protocol protocol, bool data);
	int SendIntPacket(SOCKET socket, Protocol protocol, int data);
	int SendStrPacket(SOCKET socket, Protocol protocol, std::string data);

	//receive packet
	int RecvProtocolPacket(const SOCKET& socket, Protocol& protocol);
	int RecvBoolPacket(SOCKET socket, Protocol& protocol, bool* data);
	int RecvIntPacket(SOCKET socket, Protocol& protocol, int* data);
	int RecvStrPacket(SOCKET socket, Protocol& protocol, std::string* data);
private:
	Packet packet;
	void ClearPacket();
	template <class Data>
	int SendPacket(SOCKET socket, Protocol protocol, Data data);
	template <class Data>
	int RecvPacket(SOCKET socket, Protocol& protocol, Data* data);
};

template<class Data>
inline int PacketHandler::SendPacket(SOCKET socket, Protocol protocol, Data data)
{
	char* ptr = packet.buf + sizeof(int);
	int packetSize = 0;
	int dataSize = sizeof(data);

	memcpy(ptr, &protocol, sizeof(protocol));
	ptr += sizeof(protocol);
	packetSize += sizeof(protocol);

	memcpy(ptr, &dataSize, sizeof(dataSize));
	ptr += sizeof(dataSize);
	packetSize += sizeof(dataSize);

	memcpy(ptr, &data, dataSize);
	packetSize += dataSize;

	ptr = packet.buf;
	packet.packetSize = packetSize;
	memcpy(ptr, &packetSize, sizeof(packetSize));

	return send(socket, packet.buf, packet.packetSize + sizeof(int), 0);

}

template<class Data>
inline int PacketHandler::RecvPacket(SOCKET socket, Protocol& protocol, Data* data)
{
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
	char* ptr = packet.buf;

	memset(data, 0, sizeof(*data));
	memcpy(&protocol, ptr, sizeof(protocol));
	ptr += sizeof(protocol);

	int dataSize = 0;
	memcpy(&dataSize, ptr, sizeof(dataSize));
	ptr += sizeof(dataSize);

	memcpy(data, ptr, dataSize);
	return retval;
}