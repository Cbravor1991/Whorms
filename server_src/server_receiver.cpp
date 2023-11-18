#include <iostream>
#include <sstream>
#include <valarray>
#include <vector>
#include <utility>
#include <netinet/in.h>
#include <fstream>
#include "server_receiver.h"
#include "accion/desconexion.h"

ServerRecibidor::ServerRecibidor(
    ProtocoloServer *protocolo, Queue<Accion *> *cola, int jugador) : protocolo(protocolo), cola(cola), jugador(jugador)
{
}

void ServerRecibidor::run()
{
    bool en_conexion = true;
    while (en_conexion && (!server_cerrado))
    {
        recibir_movimiento();
        en_conexion = protocolo->check_en_conexion();
    }
    if (!server_cerrado)
    {
        Accion *accion = new Desconexion(jugador);
        cola->push(accion);
    }
}

void ServerRecibidor::recibir_movimiento()
{

    Accion *accion = protocolo->leer_accion(jugador);
    cola->push(accion);
}

void ServerRecibidor::cerrar()
{
    server_cerrado = true;
}