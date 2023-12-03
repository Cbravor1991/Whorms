#include <iostream>
#include <sstream>
#include <valarray>
#include <vector>
#include <utility>
#include <netinet/in.h>
#include <fstream>
#include "server_jugador.h"
#include "server_receiver.h"

Jugador::Jugador(ProtocoloServer *socket) : socket(socket), lanzador(nullptr), recibidor(nullptr), cola(new Queue<Data *>(100))
{
}

void Jugador::asignar_id(int jugador_id)
{
    id = jugador_id;
}

void Jugador::jugar(Queue<Accion *> *cola, int tipo_fondo)
{
    socket->enviar_comienzo_juego();
    socket->enviar_id(tipo_fondo);
    socket->enviar_id(id);
    recibidor = new ServerRecibidor(socket, cola, id);
    recibidor->start();
    lanzador = new ServerLanzador(socket, this->cola);
    lanzador->start();
}

void Jugador::enviar_cantidad_jugadores(int cantidad_jugadores)
{
    socket->enviar_cantidad_jugadores_en_espera(cantidad_jugadores);
}

void Jugador::recibir_comando(Data *comando)
{
    cola->push(comando);
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
    recibir_comando(new Data());
    lanzador->join();
    delete lanzador;
    lanzador = nullptr;
    recibidor->join();
    delete recibidor;
    recibidor = nullptr;
    delete socket;
    socket = nullptr;
    if (cola != nullptr)
    {
        Data *data;
        while (cola->try_pop(data))
        {
            delete data;
        }
        delete cola;
    }
}
