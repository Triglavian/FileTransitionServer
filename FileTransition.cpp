#include "FileTransition.h"

FileTransition::FileTransition()
{

}

FileTransition::~FileTransition()
{
}

bool FileTransition::StateSwitch(ClientSocket* cSocket)
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
				if (RecvFileName(cSocket, data) == false) break;
				cSocket->SendProtocolPacket(P_FINNAME);
				break;
			case RECVING:
				ReceiveFile(cSocket, data);
				break;
			case RECVFIN:	
				EndTransition(cSocket, data);
				return true;
			case INVALID:
				SendErrorResult(cSocket, data);
				return false;
			case _DISCON:
				if (data != nullptr) delete data;
				return false;
			case QUIT:
				if (data != nullptr) delete data;
				return true;
		}
	}
	return false;
}

bool FileTransition::RecvFileName(ClientSocket* cSocket, FileTransitionData* data)
{
	if (cSocket->RecvStrPacket(data->GetFileNameRef()) == SOCKET_ERROR) 
	{
		data->SetState(_DISCON);
		return false;
	}
	if (!cSocket->ValidateProtocol(P_FILENAME)) 
	{
		//error handler
		return false;
	}
	data->SetState(RECVING);
	return true;
}

bool FileTransition::ReceiveFile(ClientSocket* cSocket, FileTransitionData* data)
{
	if (EventHandles::GetInstance()->WaitRdyTransEvent())
	{
		data->SetState(_DISCON);
		return false;
	}
	if (!GetFileData(cSocket, data))
	{
		return false;
	}
	//data->EnterFileCritSec();
	data->file = fopen(data->GetFileDirectory().c_str(), "a+b");
	while (true) 
	{
		//packet size receiver
		if (!GetReadFileSize(cSocket, data)) {
			data->SetState(_DISCON);
			fclose(data->file);
			//data->LeaveFileCritSec();
			return false;
		}
		if (cSocket->ValidateProtocol(P_FINTRANS) && data->GetFileSize() == 0)
		{
			cSocket->SetProtocol(P_FINTRSRES);
			data->SetState(RECVFIN);
			break;
		}	
		if (!cSocket->ValidateProtocol(P_FSIZE) || data->GetFileSize() < 0)
		{
			cSocket->SetProtocol(P_INVALID);
			data->SetState(INVALID);
			fclose(data->file);
			//data->LeaveFileCritSec();
			return false;
		}
		//file data receiver
		if (!GetReadFile(cSocket, data)) {
			data->SetState(_DISCON);
			fclose(data->file);
			//data->LeaveFileCritSec();
			return false;
		}
		if (!cSocket->ValidateProtocol(P_FREAD) || !WriteFile(data))
		{
			cSocket->SetProtocol(P_INVALID);
			data->SetState(INVALID);
			fclose(data->file);
			//data->LeaveFileCritSec();
			return false;
		}
	}
	fclose(data->file);
	//data->LeaveFileCritSec();
	EventHandles::GetInstance()->SetRdyTransEvent();
	return true;
}

bool FileTransition::GetFileData(ClientSocket* cSocket, FileTransitionData* data)
{
	data->SetFileDirectory();
	if (!GetReadFileSize(cSocket, data)) {
		data->SetState(_DISCON);
		return false;
	}
	if (!cSocket->ValidateProtocol(P_FSIZE)) //exception : invalid protocol or data
	{
		cSocket->SetProtocol(P_INVALID);
		data->SetState(INVALID);
		return false;
	}
	Int existFileSize = GetExistFileSize(data);
	if (data->GetFileSize() == existFileSize) //exception : same file exist
	{
		cSocket->SendProtocolPacket(P_SAME);
		data->SetState(WAIT);
		return false;
	}
	cSocket->SendIntPacket(P_FSIZRES, existFileSize);
	return true;
}

bool FileTransition::GetReadFileSize(ClientSocket* cSocket, FileTransitionData* data)
{
	return cSocket->RecvIntPacket(data->GetFileSizeRef()) != SOCKET_ERROR;
}

Int FileTransition::GetExistFileSize(FileTransitionData* data)
{
	//data->EnterFileCritSec();
	data->file = fopen(data->GetFileDirectory().c_str(), "rb");	
	if (data->file == nullptr)
	{
		//data->LeaveFileCritSec();
		return 0;
	}
	fseek(data->file, 0, SEEK_END);
	Int size = ftell(data->file);
	fclose(data->file);
	//data->LeaveFileCritSec();
	return size;
}

bool FileTransition::GetReadFile(ClientSocket* cSocket, FileTransitionData* data)
{
	return cSocket->RecvCStrPacket(data->GetFileBuffer(), BUFSIZE) != SOCKET_ERROR;
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

