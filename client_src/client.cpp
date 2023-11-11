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

Cliente::Cliente(const std::string &hostname,
                 const std::string &servname) : hostname(hostname),
                                                servname(servname),
                                                protocolo(hostname, servname), queue_receiver(100),
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

void Cliente::mover(uint8_t movimiento) {
    this->queue_sender.push(movimiento);
}


Cliente::~Cliente() {
    lanzador.terminar();
    lanzador.join();
}