#pragma once

#include <iostream>
#include <Windows.h>

#include "FileTransSubState.h"
#include "Packet.h"

#include "Int.h"
#include "Char.h"

class FileTransitionData
{
public:
	FileTransitionData();
	~FileTransitionData();
	std::string Serialize();

	//getter
	FileTransSubState GetState();
	std::string& GetFileNameRef();
	std::string GetFileDirectory();
	Int& GetFileSizeRef();
	Int GetFileSize();
	Char* GetFileBuffer();

	//setter
	void SetState(const FileTransSubState& _state);
	void SetFileDirectory();
	void SetFileDirectory(const std::string& directory);
	void ClearFileDirectory();
	void EnterFileCritSec();
	void LeaveFileCritSec();
	FILE* file;
private:
	const std::string defaultDirectory = "C:\\Users\\Admin\\Desktop\\";
	std::string fileDirectory;
	std::string fileName;
	Int size;
	Char buf[BUFSIZE];
	FileTransSubState state;
	CRITICAL_SECTION fileSection;
};