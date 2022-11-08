#pragma once
#include "ISession.h"
#include <iostream>
#include "FileTransSubState.h"
#include <Windows.h>


class FileTransitionSession : public ISession
{
public:
	FileTransitionSession();
	~FileTransitionSession();
	Protocol GetProtocol();
	std::string Serialize();

	//getter
	FileTransSubState GetState();
	
	//setter
	void SetState(const FileTransSubState& _state);
	void SetFileDirectory(const std::string& directory);

	//service
	void EnterFileCriticalSection();
	void LeaveFileCriticalSection();
private:
	CRITICAL_SECTION fileSection;
	FILE* file;

	std::string fileDirectory;
	std::string fileName;

	FileTransSubState state;
};

