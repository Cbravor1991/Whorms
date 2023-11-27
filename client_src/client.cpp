#include <iostream>
#include <fstream>
#include <vector>
#include <netinet/in.h>
#include <sstream>
#include <algorithm>
#include "client_protocol.h"
#include "client.h"
#include <tuple>
#include <thread>

#include <chrono>
#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;

Cliente::Cliente(ProtocoloCliente & protocolo) :
                                                protocolo(protocolo), queue_sender(100), queue_receiver(100),
                                                lanzador(protocolo, queue_sender, queue_receiver)

{
    lanzador.start();
}


void Cliente::cargar_id_jugador(uint8_t id)
{
    id = id;
}
uint8_t Cliente::obtener_id_jugador()
{
    return id;
}

bool Cliente::esta_conectado() {
    return conectado and protocolo.check_en_conexion();
}

std::optional<StateGame*> Cliente::obtener_estado() {
    StateGame *estado;
    if (queue_receiver.try_pop(estado)) {
        return std::optional<StateGame*> (estado);
    }
    return std::optional<StateGame*> ();
}


void Cliente::autorizar_turno(bool permiso) {
    lanzador.autorizar_turno(permiso);
}

void Cliente::mandar_accion(Action* action) {
    this->queue_sender.push(action);
}


Cliente::~Cliente() {
    lanzador.terminar();
    lanzador.join();
}