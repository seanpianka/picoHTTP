//
// Created by sean on 8/30/17.
//

#include <iostream>
#include "ServerSocket.hpp"


ServerSocket::ServerSocket()
{
}

ServerSocket::ServerSocket(int32_t port)
{
    init((port < 65536 && port > 0) ? static_cast<uint16_t>(port) : static_cast<uint16_t>(8001));
}

ServerSocket::ServerSocket(uint16_t port)
{
    init(port);
}

void ServerSocket::init(uint16_t port)
{
    if (!create())
    {
        throw std::runtime_error("Failed to create ServerSocket.");
    }
    if (!bind(port))
    {
        throw std::runtime_error("Failed to bind ServerSocket to port.\n");
    }
    if (!listen())
    {
        throw std::runtime_error("Failed to listen with ServerSocket.\n");
    }
}


const ServerSocket &ServerSocket::operator<<(const std::string &s) const
{
    if (!Socket::send(s))
    {
        throw std::runtime_error("Failed to send with ServerSocket in ServerSocket::operator<<.");
    }
    return *this;
}

const ServerSocket &ServerSocket::operator>>(std::string &s) const
{
    if (!Socket::recv(s))
    {
        throw std::runtime_error("Failed to recv with ServerSocket in ServerSocket::operator>>.");
    }
    return *this;
}

ServerSocket::~ServerSocket()
{

}

void ServerSocket::accept(ServerSocket &s)
{
    if (!Socket::accept(s))
    {
        throw std::runtime_error("Failed to accept with ServerSocket in ServerSocket::accept.");
    }
}
