#include <iostream>
#include "HTTPServer.hpp"


int main()
{
    HTTPServer server(8000);
    server.run();
    return EXIT_SUCCESS;
}
