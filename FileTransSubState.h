#pragma once

enum FileTransSubState// : public SubState
{
/*
public:
	static const int E_WAIT = 0;
	static const int E_FILERECVING = 1;
	static const int E_RECVFIN = 2;
	static const int E_QUIT = 3;
*/
E_WAIT,
E_FILERECVING,
E_RECVFIN,
E_QUIT,

#define WAIT	FileTransSubState::E_WAIT
#define RECVING	FileTransSubState::E_FILERECVING
#define RECVFIN FileTransSubState::E_RECVFIN
#define QUIT	FileTransSubState::E_QUIT
};