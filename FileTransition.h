#pragma once
#include "FileTransSubState.h"
#include "ClientSocket.h"
#include "FileTransitionData.h"

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
	void RecvFileName(ClientSocket* cSocket, FileTransitionData* data);
	bool ValidateFileName(ClientSocket* cSocket, const FileTransitionData& data);
	void ReceiveFile(ClientSocket* cSocket, FileTransitionData* data);
	FileTransition(const FileTransition& trans);
};

