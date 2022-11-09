#include "ServerBase.h"

ServerBase::ServerBase(Int port)
{
	result = WSAStartup(MAKEWORD(2, 2), &wsa);
	this->port = port;
	threadHandles = new std::vector<HANDLE*>();
	lSocket = new ListenSocket(this->port);
	newSocket = 0;
	cSockets = new std::vector<ClientSocket*>();
	fileTransition = new FileTransition();
}

ServerBase::~ServerBase()
{
	if (threadHandles != nullptr) 
	{
		for (auto obj : *threadHandles)
		{
			CloseHandle(obj);
		}
		delete threadHandles;
	}
	if (cSockets != nullptr) 
	{
		for (auto* obj : *cSockets) 
		{
			delete obj;
		}
		delete cSockets;
	}
	if (lSocket != nullptr) delete lSocket;
}

void ServerBase::Run()
{
	if (InitializeServer())
	{
		//error handler
		return;
	}
	AcceptClients();
}

bool ServerBase::InitializeServer()
{
	if (IsWSAStartFailed()) 
	{
		//error handler
		return false;
	}
	if (lSocket->IsInvalidSock()) 
	{
		//error handler
		return false;
	}
	if (lSocket->IsUnbindedSocket()) 
	{
		//error handler
		return false;
	}
	if (lSocket->IsListeningFailed())
	{
		//error handler
		return false;
	}
	return true;
}

bool ServerBase::IsWSAStartFailed()
{
	return result != 0;
}

void ServerBase::AcceptClients()
{
	sockaddr_in clientAddr;
	int addrLen = sizeof(clientAddr);
	HANDLE threadHandle;
 	while (true) 
	{
		newSocket = accept(lSocket->GetSocket(), (sockaddr*)&clientAddr, &addrLen);
		threadHandles->emplace_back(&threadHandle);
		threadHandle = (HANDLE)_beginthreadex(0, 0, ServerBase::StateSwitch, this, 0, 0);
		threadHandles->erase(std::find(threadHandles->begin(), threadHandles->end(), &threadHandle));
		CloseHandle(threadHandle);
	}
}

unsigned int __stdcall ServerBase::StateSwitch(void* obj)
{
	ServerBase* server = static_cast<ServerBase*>(obj);
	ClientSocket* cSocket = new ClientSocket(server->newSocket);
	server->cSockets->emplace_back(cSocket);
	while (true)
	{
		switch (cSocket->GetMainState()) 
		{
			case MAIN:
				cSocket->ModifyStateWithProtocol();
				break;
			case FILETRANS:
				server->fileTransition->StateSwitch(cSocket);
				break;
			default:
				//error handler
				break;
		}
	}
	server->cSockets->erase(std::find(server->cSockets->begin(), server->cSockets->end(), cSocket));
	delete cSocket;
	return 0;
}
