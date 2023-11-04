#include <fstream>
#include <string>
#include <iostream>
#include <exception>
//#include "client.h"
#include "game.h"

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "Uso: " << argv[0] << " <ip/hostname server> <puerto/servicename>\n";
            return 1;
        }
        const std::string hostname = std::string(argv[1]);
        const std::string servname = std::string(argv[2]);

        // Cliente cliente(hostname, servname);
        // cliente.run();
        Game juego(hostname, servname);
        juego.run();

        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
