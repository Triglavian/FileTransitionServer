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
	FileTransitionSession* session = dynamic_cast<FileTransitionSession*>(cSocket->GetSession());
	switch (session->GetState()) 
	{
		case WAIT:
			//recv state
			break;
		case RECVING:

			break;
		case RECVFIN:
			session->SetState(WAIT);
			break;
		default:
			//error handler
			break;
	}
}

void FileTransition::ReceivFileData(ClientSocket* cSocket)
{

}

void FileTransition::ReceiveFile(ClientSocket* cSocket)
{
	while (true) 
	{

	}
}

FileTransition::FileTransition(const FileTransition& trans)
{

}

