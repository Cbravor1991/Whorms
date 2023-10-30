#include <iostream>
#include <sstream>
#include <valarray>
#include <vector>
#include <utility>
#include <netinet/in.h>
#include <fstream>
#include "server_receiver.h"

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
    int movimiento = protocolo->leer_movimiento();
    Accion *accion;
    // Convierte el valor del movimiento a una representación de texto
    switch (movimiento)
    {
    case MOVIMIENTO_IZQUIERDA:
        accion = new MoverIzquierda(jugador);
        break;
    case MOVIMIENTO_DERECHA:
        accion = new MoverDerecha(jugador);
        break;
    case MOVIMIENTO_ARRIBA_ADELANTE:
        accion = new SaltarAdelante(jugador);
        break;
    case MOVIMIENTO_ARRIBA_ATRAS:
        accion = new SaltarAtras(jugador);
        break;
    default:
        // Manejo de un movimiento no válido, si es necesario
        return;
    }
    // Agrega el movimiento como una cadena a la cola
    cola->push(accion);
}

void ServerRecibidor::cerrar()
{
    server_cerrado = true;
}