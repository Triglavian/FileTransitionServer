#pragma once

#include "ISession.h"
#include <iostream>
#include "FileTransSubState.h"
#include <Windows.h>

#include "Int.h"

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

	//setter
	void SetState(const FileTransSubState& _state);
	void SetFileDirectory();
	void SetFileDirectory(const std::string& directory);
	void ClearFileDirectory();
	FILE* file;
private:
	const std::string defaultDirectory = "\\Received\\";
	std::string fileDirectory;
	std::string fileName;
	Int size;
	Char buf[BUFSIZE];
	FileTransSubState state;
};