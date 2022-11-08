#pragma once

enum class Protocol
{
	p_DISCONNECTION = 0,	//disconnection protocol, recivec if opps socket is closed
	
	p_REGISTRAION = 10,	//registration protocol, client to server
	p_REGISTRATIONREADY,	//registration ready protocol, server to client
	p_REGISTRATIONSUCCESS,//registration result protocol, server to client
	p_REGISTRAIONFAIL,	//registration result protocol, server to client
	
	p_LOGIN,				//login protocol, client to server
	p_LOGINREADY,			//login ready protocol, server to client
	p_LOGINSUCCESS,		//login result protocol, server to client
	p_LOGINFAIL,			//login result protocol, server to client
	P_LOGOUT,
	P_LOGOUTRESPONSE,
	P_EXIT,

	E_NONE,
	E_RECEIVENUMBER,
	E_CALCULATESCORE,
	E_SENDRESULT,
	E_ENDGAME,
	MAX,

#define P_DISCON	Protocol::p_DISCONNECTION
#define P_REG		Protocol::p_REGISTRAION
#define P_REGRDY	Protocol::p_REGISTRATIONREADY
#define P_REGSUC	Protocol::p_REGISTRATIONSUCCESS
#define P_REGFAIL	Protocol::p_REGISTRAIONFAIL
#define P_LIN		Protocol::p_LOGIN
#define P_LINRDY	Protocol::p_LOGINREADY
#define P_LINSUC	Protocol::p_LOGINSUCCESS
#define P_LINFAIL	Protocol::p_LOGINFAIL
#define P_LOUT		Protocol::P_LOGOUT
#define P_LOUTRES	Protocol::P_LOGOUTRESPONSE
#define P_EXIT		Protocol::P_EXIT
#define E_NONE		Protocol::E_NONE
#define E_RECVNUM	Protocol::E_RECEIVENUMBER
#define E_CALC		Protocol::E_CALCULATESCORE
#define E_SENDRES	Protocol::E_SENDRESULT
#define E_END		Protocol::E_ENDGAME
};