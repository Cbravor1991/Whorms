#include <iostream>
#include <sstream>
#include <valarray>
#include <vector>
#include <utility>
#include <netinet/in.h>
#include <fstream>
#include "client_receiver.h"
// #include "common_liberror.h"

ClienteRecibidor::ClienteRecibidor(
    ProtocoloCliente &protocolo, Queue<StateGame> &queue_receiver) : protocolo(protocolo), queue_receiver(queue_receiver)
{
}

void ClienteRecibidor::run()
{
    bool en_conexion = true;
    int id_jugador = protocolo.recibir_id_jugador();
    std::cout << "soy " << id_jugador << std::endl;
    while (en_conexion && (!cliente_cerrado))
    {
        StateGame estado_juego;
        estado_juego = protocolo.procesar_mensaje(id_jugador);

        EscenarioDTO escenario_dto = estado_juego.obtener_escenario();

        queue_receiver.push(estado_juego);
        en_conexion = protocolo.check_en_conexion();
    }
}

void ClienteRecibidor::terminar()
{
    cliente_cerrado = true;
}
