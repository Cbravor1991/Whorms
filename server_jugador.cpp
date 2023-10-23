#include <iostream>
#include <sstream>
#include <valarray>
#include <vector>
#include <utility>
#include <netinet/in.h>
#include <fstream>
#include "server_jugador.h"
#include "server_receiver.h"

Jugador::Jugador(ProtocoloServer *socket, ServerLanzador *lanzador, ServerRecibidor *recibidor) : socket(socket),
                                                                                                  lanzador(lanzador),
                                                                                                  recibidor(recibidor)
{
    lanzador->start();
    recibidor->start();
}

void Jugador::enviar_viga(bool tipo, int x, int y)
{
    lanzador->enviar_viga(tipo, x, y);
}

void Jugador::enviar_cantidad_jugadores(int cantidad)
{
    lanzador->enviar_cantidad_jugadores(cantidad);
}

void Jugador::enviar_jugador(int id, int x, int y)
{
    lanzador->enviar_jugador(id, x, y);
}

bool Jugador::sigo_conectado()
{
    return socket->check_en_conexion();
}

Jugador::~Jugador()
{
    // Liberar memoria de los punteros
    recibidor->cerrar();
    if (socket->check_en_conexion())
    {
        socket->desconectar();
    }
    lanzador->join();
    delete lanzador;
    lanzador = nullptr;
    recibidor->join();
    delete recibidor;
    recibidor = nullptr;
    delete socket;
    socket = nullptr;
}
