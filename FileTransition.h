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
	
	//service
	bool RecvFileName(ClientSocket* cSocket, FileTransitionData* data);
	void ReceiveFile(ClientSocket* cSocket, FileTransitionData* data);
	void GetReadFileSize(ClientSocket* cSocket, FileTransitionData* data);
	Int GetExistFileSize(FileTransitionData* data);
	bool GetReadFile(ClientSocket* cSocket, FileTransitionData* data);
	void SendErrorResult(ClientSocket* cSocket, FileTransitionData* data);
	void EndTransition(ClientSocket* cSocket, FileTransitionData* data);
	bool WriteFile(FileTransitionData* data);
	void ResetState(ClientSocket* cSocket, FileTransitionData* data);
	FileTransition(const FileTransition& trans);
};

