#include <iostream>
#include <sstream>
#include <valarray>
#include <vector>
#include <utility>
#include <netinet/in.h>
#include <fstream>
#include "client_sender.h"
// #include "common_liberror.h"

ClienteLanzador::ClienteLanzador(
    ProtocoloCliente &protocolo, Queue<uint8_t> &queue_sender, Queue<StateGame *> &queue_receiver) : protocolo(protocolo), queue_sender(queue_sender), queue_receiver(queue_receiver), cliente_recibidor(protocolo, queue_receiver)
{
    cliente_recibidor.start();
}

void ClienteLanzador::autorizar_turno(bool turno)
{
    this->turno = turno;
}

void ClienteLanzador::run()
{
    while (en_conexion) {

        uint8_t movimiento = queue_sender.pop();
        if (this->turno) {
            protocolo.enviar_mensaje(movimiento);
        }
        en_conexion = protocolo.check_en_conexion();
    }
    
}

void ClienteLanzador::terminar()
{
    en_conexion = false;
    cliente_recibidor.terminar();
    protocolo.desconectar();
    cliente_recibidor.join();
}