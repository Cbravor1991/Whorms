#include <iostream>
#include <sstream>
#include <valarray>
#include <vector>
#include <utility>
#include <netinet/in.h>
#include <fstream>
#include "server.h"
#include "common_liberror.h"

Server::Server(
    const std::string &servname) : servname(servname)
{
}

void Server::run()
{
    ServerAceptador server_aceptador(servname);
    server_aceptador.start();
    while (std::cin.get() != SALIR)
    {
    }
    server_aceptador.terminar();
    server_aceptador.join();
}
