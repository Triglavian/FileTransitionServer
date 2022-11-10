#include "FileTransition.h"

FileTransition::FileTransition()
{
	state = WAIT;
}

FileTransition::~FileTransition()
{
}

void FileTransition::StateSwitch(ClientSocket* cSocket)
{
	FileTransitionData* data = new FileTransitionData();
	//cSocket->AddNewSession(session);
	bool flag = true;
	while (flag) 
	{
		switch (state)
		{
			case WAIT:
				RecvFileName(cSocket, data);
				cSocket->SendProtocolPacket(P_FINNAME);
				break;
			case RECVING:
				ReceiveFile(cSocket, data);
				break;
			case RECVFIN:
				break;
			case QUIT:
				if (data != nullptr) delete data;
				flag = false;
				break;
			default:
				//error handler
				break;
		}
	}
}

void FileTransition::RecvFileName(ClientSocket* cSocket, FileTransitionData* data)
{
	cSocket->RectStrPacket(data->GetFileNameRef());
	if (!cSocket->ValidateProtocol(P_RECVNAME)) 
	{
		//error handler
		return;
	}
	if (!ValidateFileName(cSocket, *data)) 
	{
		data->ClearFileDirectory();
		return;
	}
	state = RECVING;
}

bool FileTransition::ValidateFileName(ClientSocket* cSocket, FileTransitionData& data)
{	
	data.SetFileDirectory();
	if (access(data.GetFileDirectory().c_str(), 6) != 0) return false;
	return true;
}

void FileTransition::ReceiveFile(ClientSocket* cSocket, FileTransitionData* data)
{
	data->file = fopen(data->GetFileDirectory().c_str(), "wb");
	while (true) 
	{
		
	}
}

bool FileTransition::GetReadFileSize(ClientSocket* cSocket, FileTransitionData* data)
{
	cSocket->RecvIntPacket(data->GetFileSizeRef());
	return cSocket->ValidateProtocol(P_FSIZE);
}

bool FileTransition::GetReadFile(ClientSocket* cSocket, FileTransitionData* data)
{
	cSocket->RecvCStrPacket()
}

FileTransition::FileTransition(const FileTransition& trans)
{

}

