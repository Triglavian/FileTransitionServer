#pragma once
#include "IDataType.h"
class Char : public IDataType
{
public:
	Char();
	Char(char _char);
	Char(const Char& _char);
	~Char();
	std::string ToString();
	Char operator=(const Char& _char);
	Char operator=(const char& _char);
private:
	char character;
};
