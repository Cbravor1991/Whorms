#include <iostream>
#include <sstream>
#include <valarray>
#include <vector>
#include <utility>
#include <netinet/in.h>
#include <fstream>
#include "../common_src/common_liberror.h"
#include "server_acceptor.h"

ServerAceptador::ServerAceptador(
    const std::string &servname) : socket(servname.c_str())
{
    lobby = new Lobby();
}

void ServerAceptador::run()
{
    try
    {
        while (ejecutando)
        {
            Socket aceptado = socket.accept();
            lanzar_hilo_manejador(std::move(aceptado));
        }
    }
    catch (const std::exception &err)
    {
    }
}

void ServerAceptador::lanzar_hilo_manejador(
    Socket skt_cliente)
{

    ProtocoloServer *protocolo = new ProtocoloServer(std::move(skt_cliente));

    ServerLobby *server_lobby = new ServerLobby(protocolo, lobby);

    server_lobby->start();

    servidores_lobby.push_back(server_lobby);
}

void ServerAceptador::terminar()
{
    socket.shutdown(2);
    socket.close();
    ejecutando = false;
}

ServerAceptador::~ServerAceptador()
{

    for (ServerLobby *servidor : servidores_lobby)
    {
        servidor->join();
        delete servidor;
    }

    delete lobby;
}