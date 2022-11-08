#include "MainSession.h"

MainSession::MainSession()
{
}

MainSession::~MainSession()
{
}

Protocol MainSession::GetProtocol()
{
    return protocol;
}

std::string MainSession::Serialize()
{
    return std::string();
}
