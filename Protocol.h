#pragma once

enum class Protocol
{
	P_DISCONNECTION = 0,	//disconnection protocol, recivec if opps socket is closed
	P_INVALIDPROT,
	P_FILETRANSITION = 10,
	P_RDYTRANSITION,
	P_RECVFILENAME,
	P_FINFILENAME,	
	P_FILESIZE,	
	P_SAMEFILE,
	P_FILESIZERES,
	P_FILEREAD,
	P_ONTRANSITION,
	P_FINTRANSITION,
	P_FINTRANSITIONRES,
	P_QUITTRANSITION,

#define P_DISCON	Protocol::P_DISCONNECTION
#define P_INVALID	Protocol::P_INVALIDPROT
#define P_TRANS		Protocol::P_FILETRANSITION
#define P_RDYTRANS	Protocol::P_RDYTRANSITION
#define P_FILENAME	Protocol::P_RECVFILENAME
#define P_FINNAME	Protocol::P_FINFILENAME
#define P_FSIZE		Protocol::P_FILESIZE
#define P_FSIZRES	Protocol::P_FILESIZERES
#define P_SAME		Protocol::P_SAMEFILE
#define P_FREAD		Protocol::P_FILEREAD
#define P_ONTRANS	Protocol::P_ONTRANSITION
#define P_FINTRANS	Protocol::P_FINTRANSITION
#define P_FINTRSRES	Protocol::P_FINTRANSITIONRES
#define P_QUITTRANS	Protocol::P_QUITTRANSITION
};