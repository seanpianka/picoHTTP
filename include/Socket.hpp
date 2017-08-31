//
// Created by sean on 8/30/17.
//

#ifndef SPHTTP_SOCKET_H
#define SPHTTP_SOCKET_H

#include <cstdint>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>


class Socket
{
public:
    Socket();
    virtual ~Socket();

    // server initialization
    bool create();
    bool bind(const uint16_t&);
    bool listen() const;
    bool accept(Socket&) const;

    // client initialization
    bool connect(const std::string&, uint16_t);

    // transmission
    bool send(const std::string&) const;
    ssize_t recv(std::string&) const;

    void set_non_blocking(bool);
    bool is_valid() const { return _sock != -1; }

protected:
    int32_t _sock;
    sockaddr_in _addr;
    const static uint8_t MAX_CONNECTIONS;
    const static uint32_t MAX_RECV_LEN;

};


#endif //SPHTTP_SOCKET_H
