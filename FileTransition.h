#pragma once
#include "FileTransSubState.h"
#include "ClientSocket.h"
#include "FileTransitionData.h"
#include <io.h>

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
	//CRITICAL_SECTION fileSection;
	//service
	void RecvFileName(ClientSocket* cSocket, FileTransitionData* data);
	bool ValidateFileName(ClientSocket* cSocket, FileTransitionData& data);
	void ReceiveFile(ClientSocket* cSocket, FileTransitionData* data);
	bool GetReadFileSize(ClientSocket* cSocket, FileTransitionData* data);
	bool GetReadFile(ClientSocket* cSocket, FileTransitionData* data);
	FileTransition(const FileTransition& trans);
};

