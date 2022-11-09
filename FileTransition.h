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
	void RecvFileName(ClientSocket* cSocket, FileTransitionSession* session);
	bool ValidateFileName(ClientSocket* cSocket, FileTransitionSession* session);
	void ReceiveFile(ClientSocket* cSocket, FileTransitionSession* session);
	FileTransition(const FileTransition& trans);
};

