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
				break;
			case RECVING:

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
	if (!ValidateFileName(cSocket, *data)) return;
	state = RECVING;
}

bool FileTransition::ValidateFileName(ClientSocket* cSocket, const FileTransitionData& data)
{
	if()
	return true;
}

void FileTransition::ReceiveFile(ClientSocket* cSocket, FileTransitionData* data)
{
	while (true) 
	{

	}
}

FileTransition::FileTransition(const FileTransition& trans)
{

}

