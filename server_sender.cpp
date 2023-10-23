#include <iostream>
#include <sstream>
#include <valarray>
#include <vector>
#include <utility>
#include <netinet/in.h>
#include <fstream>
#include "server_sender.h"
#include "common_liberror.h"

ServerLanzador::ServerLanzador(
    ProtocoloServer *protocolo) : protocolo(protocolo)
{
}

void ServerLanzador::run()
{
    bool en_conexion = true;
    while (en_conexion)
    {
        en_conexion = protocolo->check_en_conexion();
    }
}

void ServerLanzador::enviar_viga(bool tipo, int x, int y)
{
    protocolo->enviar_viga(tipo, x, y);
}

void ServerLanzador::enviar_cantidad_jugadores(int cantidad)
{
    protocolo->enviar_cantidad_jugadores(cantidad);
}

void ServerLanzador::enviar_jugador(int id, int x, int y)
{
    protocolo->enviar_jugador(id, x, y);
}
