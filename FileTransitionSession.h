#pragma once
#include "ISession.h"
#include <iostream>
#include "FileTransSubState.h"
#include <Windows.h>

#include <concrt.h>

class FileTransitionSession : public ISession
{
public:
	FileTransitionSession();
	~FileTransitionSession();
	Protocol GetProtocol();
	std::string Serialize();

	//getter
	FileTransSubState GetState();
	std::string& GetFileNameRef();
	//setter
	void SetState(const FileTransSubState& _state);
	void SetFileDirectory(const std::string& directory);

	//critical section
	void EnterFileCriticalSection();
	void LeaveFileCriticalSection();
private:
	CRITICAL_SECTION fileSection;
	FILE* file;
	
	const std::string defaultDirectory = "\\Received\\";
	std::string fileDirectory;
	std::string fileName;

	FileTransSubState state;
};

