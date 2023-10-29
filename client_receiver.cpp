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
    ProtocoloCliente& protocolo, Queue<StateGame>& queue_receiver) : protocolo(protocolo), queue_receiver(queue_receiver) 
{
}

void ClienteRecibidor::run()
{
    bool en_conexion = true;
    int id = protocolo.recibir_id();
    std::cout << "soy " << id << std::endl;
    while (en_conexion && (!cliente_cerrado))
    {
        StateGame estado_juego;
        estado_juego = protocolo.procesar_mensaje();
        queue_receiver.push(estado_juego);
        en_conexion = protocolo.check_en_conexion();
    }
}

void ClienteRecibidor::terminar()
{
    cliente_cerrado = true;
}
