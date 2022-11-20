#include "ServerBase.h"

int main(int argc, char* argv[])
{
	ServerBase* server = new ServerBase();
	server->Run();
	if (server != nullptr) delete server;
}