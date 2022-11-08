#include "FileTransitionSession.h"

FileTransitionSession::FileTransitionSession()
{
    state = WAIT;
    fileDirectory = "";
    fileName = "";
    file = nullptr;
    InitializeCriticalSection(&fileSection);
}

FileTransitionSession::~FileTransitionSession()
{
    DeleteCriticalSection(&fileSection);
}

Protocol FileTransitionSession::GetProtocol()
{
    return protocol;
}

std::string FileTransitionSession::Serialize()
{
    return std::string();
}

FileTransSubState FileTransitionSession::GetState()
{
    return state;
}

void FileTransitionSession::SetState(const FileTransSubState& _state)
{
    state = _state;
}

void FileTransitionSession::SetFileDirectory(const std::string& directory)
{
    fileDirectory = directory;
}

void FileTransitionSession::EnterFileCriticalSection()
{
    EnterCriticalSection(&fileSection);
}

void FileTransitionSession::LeaveFileCriticalSection()
{
    LeaveCriticalSection(&fileSection);
}
