#include <iostream>
#include <sstream>
#include <valarray>
#include <vector>
#include <utility>
#include <netinet/in.h>
#include <fstream>
#include "client_receiver.h"
#include "common_liberror.h"
#include <thread>

ClienteRecibidor::ClienteRecibidor(
    ProtocoloCliente *protocolo) : protocolo(protocolo)
{
}

void ClienteRecibidor::run()
{
    bool en_conexion = true;
    while (en_conexion && (!cliente_cerrado))
    {
        recibir_mensaje();
        en_conexion = protocolo->check_en_conexion();
    }
}

void ClienteRecibidor::terminar()
{
    cliente_cerrado = true;
}

void ClienteRecibidor::recibir_mensaje()
{
    int tipo_mensaje = protocolo->recibir_mensaje();
    bool conectado = protocolo->check_en_conexion();

    switch (tipo_mensaje)
    {
    case TIPO_CANTIDAD_JUGADORES:
        if (conectado)
        {
            int cantidad_jugadores = protocolo->recibir_cantidad_jugadores();
            conectado = protocolo->check_en_conexion();
            std::cout << "Jugadores " << cantidad_jugadores
                      << ", esperando al resto de tus amigos…" << std::endl;
        }
        break;

    case TIPO_JUGADOR:
        if (conectado)
        {
            Jugador jugador = protocolo->recibir_jugador();
            conectado = protocolo->check_en_conexion();
            std::cout << "Jugador " << jugador.id << " en coordenadas"
                      << " X: " << jugador.x << " Y: " << jugador.y << std::endl;
        }
        break;
    case TIPO_VIGA:
        if (conectado)
        {
            Viga viga = protocolo->recibir_viga();
            conectado = protocolo->check_en_conexion();
            std::cout << "Viga " << viga.tipo << " en coordenadas"
                      << " X: " << viga.x << " Y: " << viga.y << std::endl;
        }
        break;
    }
}
