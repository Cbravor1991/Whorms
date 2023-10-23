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
    Escenario *escenario,
    ProtocoloServer *protocolo) : escenario(escenario),
                                  protocolo(protocolo)
{
}

void ServerRecibidor::run()
{
    jugador = escenario->agregar_gusano();
    bool en_conexion = true;
    while (en_conexion && (!server_cerrado))
    {
        recibir_movimiento();
        en_conexion = protocolo->check_en_conexion();
    }
    if (!server_cerrado)
    {
        escenario->avisar_desconexion(jugador);
    }
}

void ServerRecibidor::recibir_movimiento()
{
    int movimiento = protocolo->leer_movimiento();
    // Utiliza un switch para determinar el movimiento a realizar
    switch (movimiento)
    {
    case MOVIMIENTO_DERECHA:
        escenario->mover_gusano_derecha(1, jugador);
        break;
    case MOVIMIENTO_IZQUIERDA:
        escenario->mover_gusano_izquierda(1, jugador);
        break;
    case MOVIMIENTO_ARRIBA_ADELANTE:
        escenario->mover_gusano_arriba_adelante(1, jugador);
        break;
    case MOVIMIENTO_ARRIBA_ATRAS:
        escenario->mover_gusano_arriba_atras(1, jugador);
        break;
    default:
        // Manejo de un movimiento no válido, si es necesario
        break;
    }
}

void ServerRecibidor::cerrar()
{
    server_cerrado = true;
}