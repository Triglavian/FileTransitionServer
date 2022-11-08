#include "Char.h"

Char::Char()
{
	character = 0;
}

Char::Char(char _char)
{
	character = _char;
}

Char::Char(const Char& _char)
{
	character = _char.character;
}

Char::~Char()
{

}

std::string Char::ToString()
{
	return std::to_string(character);
}

Char Char::operator=(const Char& _char)
{
	return _char;
}

Char Char::operator=(const char& _char)
{
	return Char(_char);
}
