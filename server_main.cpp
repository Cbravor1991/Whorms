#include <iostream>
#include <exception>
#include "common_socket.h"
#include "server.cpp"
#include <cstring>
#include <fstream>

int main(int argc, char *argv[])
{
    try
    {
        std::string servname = std::string(argv[1]);
        Server server(servname);
        server.run();
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
