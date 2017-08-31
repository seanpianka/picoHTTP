//
// Created by sean on 8/30/17.
//

#ifndef SPHTTP_HTTPSERVER_H
#define SPHTTP_HTTPSERVER_H

#include "ServerSocket.hpp"
#include "SocketException.hpp"


class HTTPServer
{
public:
    HTTPServer(uint16_t port);
    ~HTTPServer();
    void run();
private:
    std::string make_response(const std::string& request);
    ServerSocket server;
};


#endif //SPHTTP_HTTPSERVER_H
