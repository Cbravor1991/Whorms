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

void Jugador::jugar(Queue<Accion *> *cola, int jugador_id)
{
    socket->enviar_id(jugador_id);
    recibidor = new ServerRecibidor(socket, cola, jugador_id);
    recibidor->start();
    lanzador = new ServerLanzador(socket, this->cola);
    lanzador->start();
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
