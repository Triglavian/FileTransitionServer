#include "ISession.h"

Protocol ISession::GetProtocol()
{
	return protocol;
}

Protocol& ISession::GetProtocolRef()
{
	return protocol;
}
