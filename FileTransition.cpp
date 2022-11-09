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
	FileTransitionSession* session = new FileTransitionSession();
	cSocket->AddNewSession(session);
	bool flag = true;
	while (flag) 
	{
		switch (session->GetState())
		{
			case WAIT:
				RecvFileName(cSocket, session);
				break;
			case RECVING:

				break;
			case RECVFIN:
				session->SetState(WAIT);
				break;
			case QUIT:
				cSocket->DeleteCurrentSession();
				if (session != nullptr) delete session;
				flag = false;
				break;
			default:
				//error handler
				break;
		}
	}
}

void FileTransition::RecvFileName(ClientSocket* cSocket, FileTransitionSession* session)
{
	cSocket->RectStrPacket(session->GetProtocolRef(), session->GetFileNameRef());
}

bool FileTransition::ValidateFileName(ClientSocket* cSocket, FileTransitionSession* session)
{
	if()
	return true;
}

void FileTransition::ReceiveFile(ClientSocket* cSocket, FileTransitionSession* session)
{
	while (true) 
	{

	}
}

FileTransition::FileTransition(const FileTransition& trans)
{

}

