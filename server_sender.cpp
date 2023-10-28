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
    ProtocoloServer *protocolo, Queue<std::string> *cola) : protocolo(protocolo), cola(cola)
{
}

void ServerLanzador::run()
{
    bool en_conexion = true;
    while (en_conexion)
    {
        std::string comando = cola->pop();
        procesar_comando(comando);
        en_conexion = protocolo->check_en_conexion();
    }
}

void ServerLanzador::procesar_comando(const std::string &comando)
{
    // Puedes usar un flujo de entrada (stringstream) para analizar el comando
    std::istringstream stream(comando);
    std::string accion;
    stream >> accion;

    if (accion == "jugador")
    {
        int id, x, y;
        stream >> id >> x >> y;
        protocolo->enviar_jugador(id, x, y);
    }
    else if (accion == "viga")
    {
        bool tipo;
        int x, y;
        stream >> tipo >> x >> y;
        protocolo->enviar_viga(tipo, x, y);
    }
    else if (accion == "cantidad")
    {
        int cantidad;
        stream >> cantidad;
        protocolo->enviar_cantidad_jugadores(cantidad);
    }
    else if (accion == "turno")
    {
        int jugador_id;
        stream >> jugador_id;
        protocolo->enviar_turno(jugador_id);
    }
    else
    {
        // Manejar comandos desconocidos o inválidos si es necesario
        // Puedes lanzar una excepción, mostrar un mensaje de error, etc.
    }
}
