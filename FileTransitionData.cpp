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

void FileTransitionData::SetState(const FileTransSubState& _state)
{
    state = _state;
}

void FileTransitionData::SetFileDirectory(const std::string& directory)
{
    fileDirectory = directory;
}

void FileTransitionData::EnterFileCriticalSection()
{
    EnterCriticalSection(&fileSection);
}

void FileTransitionData::LeaveFileCriticalSection()
{
    LeaveCriticalSection(&fileSection);
}
