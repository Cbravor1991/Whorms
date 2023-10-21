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

void ServerLanzador::enviar_mensaje()
{
    Mensaje mensaje;
    if (mensajes.try_pop(mensaje))
    {
        if (mensaje.tipo_mensaje)
        {
            protocolo->enviar_mensaje(mensaje.cadena);
        }else{
            int cantidad = std::stoi(mensaje.cadena);
            protocolo->enviar_cantidad_jugadores(cantidad);
        }
    }
}

void ServerLanzador::recibir_mensaje(Mensaje mensaje)
{
    mensajes.push(mensaje);
    enviar_mensaje();
}
