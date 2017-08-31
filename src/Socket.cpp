//
// Created by sean on 8/30/17.
//

#include <cstring>
#include <iostream>
#include <arpa/inet.h>
#include <fcntl.h>
#include "Socket.hpp"


const uint8_t Socket::MAX_CONNECTIONS = 5;
const uint32_t Socket::MAX_RECV_LEN = 2048;


Socket::Socket() : _sock(-1)
{
    memset(&_addr, 0, sizeof(_addr));
}

Socket::~Socket()
{
    if (is_valid()) { ::close(_sock); }
}

bool Socket::accept(Socket &s) const
{
    int addr_len = sizeof(_addr);
    s._sock = ::accept(_sock, (sockaddr*)&_addr, (socklen_t*)&addr_len);
    return s._sock > 0;
}

bool Socket::listen() const
{
    if (!is_valid()) { return false; }
    return ::listen(_sock, Socket::MAX_CONNECTIONS) >= 0;
}

bool Socket::bind(const uint16_t &port)
{
    if (!is_valid()) { return false; }

    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = INADDR_ANY;

    return ::bind(_sock, (sockaddr*)&_addr, sizeof(_addr)) >= 0;
}

bool Socket::create()
{
    _sock = socket(AF_INET, SOCK_STREAM, 0);

    if (!is_valid()) { return false; }

    int enable = 1;
    return setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) >= 0;
}

bool Socket::connect(const std::string &host, uint16_t port)
{
    if (!is_valid()) { return false; }

    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    // convert IPv4 and IPv6 addresses from text to binary form
    inet_pton(AF_INET, host.c_str(), &_addr.sin_addr);
    return errno != EAFNOSUPPORT && 0 == ::connect(_sock, (sockaddr*)&_addr, sizeof(_addr));
}

bool Socket::send(const std::string &s) const
{
    return static_cast<bool>(::send(_sock, s.c_str(), s.length(), MSG_NOSIGNAL));
}

ssize_t Socket::recv(std::string &s) const
{
    char buffer[Socket::MAX_RECV_LEN + 1];
    s.clear();
    memset(buffer, 0, Socket::MAX_RECV_LEN + 1);

    ssize_t num_bytes = ::recv(_sock, buffer, Socket::MAX_RECV_LEN, 0);

    switch (num_bytes)
    {
        case -1:
            std::cerr << "ERROR[errno " << errno << "]: recv failed in Socket::recv\n";
        case 0:
            return 0;
    }

    s = buffer;
    return num_bytes;
}

void Socket::set_non_blocking(bool b)
{
    int32_t opts = fcntl(_sock, F_GETFL);
    if (0 > opts) { return; }
    b ? (opts |= O_NONBLOCK) : (opts &= ~O_NONBLOCK);
    fcntl(_sock, F_SETFL, opts);
}

