//
// Created by sean on 8/30/17.
//

#ifndef SPHTTP_SERVER_H
#define SPHTTP_SERVER_H

#include <cstdint>
#include <string>
#include "Socket.hpp"


class ServerSocket : private Socket
{
public:
    ServerSocket();
    ServerSocket(int32_t);
    ServerSocket(uint16_t);
    virtual ~ServerSocket();
    const ServerSocket& operator<<(const std::string&) const;
    const ServerSocket& operator>>(std::string&) const;
    void accept(ServerSocket&);
    void init(uint16_t);
};


#endif //SPHTTP_SERVER_H
