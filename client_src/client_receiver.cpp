#include <iostream>
#include <sstream>
#include <valarray>
#include <vector>
#include <utility>
#include <netinet/in.h>
#include <fstream>
#include "client_receiver.h"

ClienteRecibidor::ClienteRecibidor(
    ProtocoloCliente &protocolo, Queue<StateGame *> &queue_receiver) : protocolo(protocolo), queue_receiver(queue_receiver)
{
}

void ClienteRecibidor::run()
{
    bool en_conexion = true;
    int id_jugador = protocolo.recibir_id_jugador();
    while (en_conexion && (!cliente_cerrado))
    {
        StateGame *estado_juego = protocolo.procesar_mensaje(id_jugador);
        queue_receiver.push(estado_juego);
        en_conexion = protocolo.check_en_conexion();
    }
}

void ClienteRecibidor::terminar()
{
    cliente_cerrado = true;
}
