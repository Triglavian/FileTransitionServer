#pragma once
#include <iostream>
#include "Protocol.h"

class ISession 
{
public:
	virtual Protocol GetProtocol() = 0;
	virtual std::string Serialize() = 0;
protected:
	Protocol protocol;
};