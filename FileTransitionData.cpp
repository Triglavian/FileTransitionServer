#include "FileTransitionData.h"

FileTransitionData::FileTransitionData()
{
    state = WAIT;
    fileDirectory = "";
    fileName = "";
    file = nullptr;
    InitializeCriticalSection(&fileSection);
}

FileTransitionData::~FileTransitionData()
{
    DeleteCriticalSection(&fileSection);
}

std::string FileTransitionData::Serialize()
{
    return std::string();
}

FileTransSubState FileTransitionData::GetState()
{
    return state;
}

std::string& FileTransitionData::GetFileNameRef()
{
    return fileName;
}

std::string FileTransitionData::GetFileDirectory()
{
    return fileDirectory;
}

Int& FileTransitionData::GetFileSizeRef()
{
    return size;
}

Int FileTransitionData::GetFileSize()
{
    return size;
}

Char* FileTransitionData::GetFileBuffer()
{
    return buf;
}

void FileTransitionData::SetState(const FileTransSubState& _state)
{
    state = _state;
}

void FileTransitionData::SetFileDirectory()
{
    fileDirectory = defaultDirectory + fileName;
}



void FileTransitionData::SetFileDirectory(const std::string& directory)
{
    fileDirectory = directory;
}

void FileTransitionData::ClearFileDirectory()
{
    fileDirectory = defaultDirectory;
}

void FileTransitionData::EnterFileCritSec()
{
    EnterCriticalSection(&fileSection);
}

void FileTransitionData::LeaveFileCritSec()
{
    LeaveCriticalSection(&fileSection);
}
