//
// Created by sean on 8/30/17.
//

#include <iostream>
#include "HTTPServer.hpp"

HTTPServer::HTTPServer(uint16_t port) : server(port){}
HTTPServer::~HTTPServer(){}

void HTTPServer::run()
{
    for (;;)
    {
        ServerSocket client;
        server.accept(client);

        try
        {
            std::string request;
            client >> request;

            std::string response = make_response(request);
            client << response;
        }
        catch (SocketException& e)
        {
            std::cerr << "Exception: " << e.what() << "\n";
        }
    }
}

std::string HTTPServer::make_response(const std::string &request)
{
    return "HTTP/1.1 200 OK\r\n\n<html><body><p>It works!</p></body></html>\r\n\n";
}
