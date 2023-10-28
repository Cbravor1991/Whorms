#include <iostream>
#include <sstream>
#include <valarray>
#include <vector>
#include <utility>
#include <netinet/in.h>
#include <fstream>
#include "server_receiver.h"
#include "escenario.cpp"
#include "common_liberror.h"
#include <thread>

ServerRecibidor::ServerRecibidor(
    ProtocoloServer *protocolo, Queue<std::string> *cola, int jugador) : protocolo(protocolo), cola(cola), jugador(jugador)
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
        cola->push("DESCONEXION " + std::to_string(jugador));
    }
}

void ServerRecibidor::recibir_movimiento()
{
    int movimiento = protocolo->leer_movimiento();
    std::string movimiento_str;
    // Convierte el valor del movimiento a una representación de texto
    switch (movimiento)
    {
    case MOVIMIENTO_IZQUIERDA:
        movimiento_str = "IZQUIERDA";
        break;
    case MOVIMIENTO_DERECHA:
        movimiento_str = "DERECHA";
        break;
    case MOVIMIENTO_ARRIBA_ADELANTE:
        movimiento_str = "ARRIBA_ADELANTE";
        break;
    case MOVIMIENTO_ARRIBA_ATRAS:
        movimiento_str = "ARRIBA_ATRAS";
        break;
    default:
        // Manejo de un movimiento no válido, si es necesario
        return;
    }

    // Concatenar el ID del jugador a la cadena del movimiento
    movimiento_str += " " + std::to_string(jugador);

    // Agrega el movimiento como una cadena a la cola
    cola->push(movimiento_str);
}

void ServerRecibidor::cerrar()
{
    server_cerrado = true;
}