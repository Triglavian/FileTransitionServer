#include "FileTransitionData.h"

FileTransitionData::FileTransitionData()
{
    state = WAIT;
    fileDirectory = "";
    fileName = "";
    file = nullptr;
}

FileTransitionData::~FileTransitionData()
{
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
