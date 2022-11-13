#include "FileTransition.h"

FileTransition::FileTransition()
{

}

FileTransition::~FileTransition()
{
}

void FileTransition::StateSwitch(ClientSocket* cSocket)
{
	FileTransitionData* data = new FileTransitionData();
	cSocket->SendProtocolPacket(P_RDYTRANS);
	//cSocket->AddNewSession(session);
	bool flag = true;
	while (flag) 
	{
		switch (data->GetState())
		{
			case WAIT:
				RecvFileName(cSocket, data);
				cSocket->SendProtocolPacket(P_FINNAME);
				break;
			case RECVING:
				ReceiveFile(cSocket, data);
				break;
			case RECVFIN:	
				EndTransition(cSocket, data);
				break;
			case INVALID:
				SendErrorResult(cSocket, data);
				break;
			case QUIT:
				if (data != nullptr) delete data;
				flag = false;
				break;
		}
	}
}

bool FileTransition::RecvFileName(ClientSocket* cSocket, FileTransitionData* data)
{
	cSocket->RectStrPacket(data->GetFileNameRef());
	if (!cSocket->ValidateProtocol(P_FILENAME)) 
	{
		//error handler
		return false;
	}
	data->SetState(RECVING);
	return true;
}

void FileTransition::ReceiveFile(ClientSocket* cSocket, FileTransitionData* data)
{
	data->SetFileDirectory();
	GetReadFileSize(cSocket, data);
	if (!cSocket->ValidateProtocol(P_FSIZE)) //exception : invalid protocol or data
	{
		cSocket->SetProtocol(P_INVALID);
		data->SetState(INVALID);
		return;
	}
	Int existFileSize = GetExistFileSize(data);
	if (data->GetFileSize() == existFileSize) //exception : same file exist
	{
		cSocket->SetProtocol(P_SAME);
		data->SetState(INVALID);
		return;
	}
	cSocket->SendIntPacket(P_FSIZRES, existFileSize);
	data->file = fopen(data->GetFileDirectory().c_str(), "a+b");
	while (true) 
	{
		GetReadFileSize(cSocket, data);
		if (cSocket->ValidateProtocol(P_FINTRANS) && data->GetFileSize() == 0)
		{
			cSocket->SetProtocol(P_FINTRSRES);
			data->SetState(RECVFIN);
			break;
		}
		if (!cSocket->ValidateProtocol(P_FSIZE) || data->GetFileSize() < 0 || !GetReadFile(cSocket, data) || !WriteFile(data))
		{
			cSocket->SetProtocol(P_INVALID);
			data->SetState(INVALID);
			break;
		}
	}
	fclose(data->file);
}

void FileTransition::GetReadFileSize(ClientSocket* cSocket, FileTransitionData* data)
{
	cSocket->RecvIntPacket(data->GetFileSizeRef());
}

Int FileTransition::GetExistFileSize(FileTransitionData* data)
{
	data->file = fopen(data->GetFileDirectory().c_str(), "rb");	
	if (data->file == nullptr)
	{
		return 0;
	}
	fseek(data->file, 0, SEEK_END);
	Int size = ftell(data->file);
	fclose(data->file);
	return size;
}

bool FileTransition::GetReadFile(ClientSocket* cSocket, FileTransitionData* data)
{
	cSocket->RecvCStrPacket(data->GetFileBuffer(), BUFSIZE);
	return cSocket->ValidateProtocol(P_FREAD);
}

void FileTransition::SendErrorResult(ClientSocket* cSocket, FileTransitionData* data)
{
	ResetState(cSocket, data);
}

void FileTransition::EndTransition(ClientSocket* cSocket, FileTransitionData* data)
{
	ResetState(cSocket, data);
}

bool FileTransition::WriteFile(FileTransitionData* data)
{
	Int writeSize = fwrite(data->GetFileBuffer(), 1, data->GetFileSize().ToInt(), data->file);
	return writeSize.ToInt() > 0 && data->GetFileSize() == writeSize;
}

void FileTransition::ResetState(ClientSocket* cSocket, FileTransitionData* data)
{
	cSocket->SendProtocolPacket();
	data->SetState(WAIT);
}

FileTransition::FileTransition(const FileTransition& trans)
{

}

