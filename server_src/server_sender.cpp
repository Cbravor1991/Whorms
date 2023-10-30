#include <iostream>
#include <sstream>
#include <valarray>
#include <vector>
#include <utility>
#include <netinet/in.h>
#include <fstream>
#include "server_sender.h"

ServerLanzador::ServerLanzador(
    ProtocoloServer *protocolo, Queue<Data *> *cola) : protocolo(protocolo), cola(cola)
{
}

void ServerLanzador::run()
{
    bool en_conexion = true;
    while (en_conexion)
    {
        Data *comando = cola->pop();
        comando->enviar_data(protocolo);
        en_conexion = protocolo->check_en_conexion();
    }
}
