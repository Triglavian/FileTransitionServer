#pragma once
#include "ISession.h"

class MainSession : public ISession
{
public:
	MainSession();
	~MainSession();
	Protocol GetProtocol();
private:
	std::string Serialize();
};

