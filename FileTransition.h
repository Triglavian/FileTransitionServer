#pragma once
#include "FileTransSubState.h"
#include "ClientSocket.h"

class FileTransition
{
public:
	FileTransition();
	~FileTransition();
	//getter

	//setter

	//service
	void StateSwitch(ClientSocket* cSocket);
private:
	//base data
	FileTransSubState state;

	//service
	void ReceivFileData(ClientSocket* cSocket);
	void ReceiveFile(ClientSocket* cSocket);
	FileTransition(const FileTransition& trans);
};

