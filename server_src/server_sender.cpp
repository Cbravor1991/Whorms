#include <iostream>
#include <sstream>
#include <valarray>
#include <vector>
#include <utility>
#include <netinet/in.h>
#include <thread>
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
        Data *data = cola->pop();
        data->enviar_data(protocolo);
        delete data;
        en_conexion = protocolo->check_en_conexion();
    }
}
