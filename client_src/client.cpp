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

const int MOVIMIENTO_IZQUIERDA = 1;
const int MOVIMIENTO_DERECHA = 2;
const int MOVIMIENTO_ARRIBA_ADELANTE = 3;
const int MOVIMIENTO_ARRIBA_ATRAS = 4;

//#include "graphics/renderer.h"
#include <chrono>
//#include <vector>
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
};

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

void Cliente::mover_izquierda() {
    uint8_t mov = MOVIMIENTO_IZQUIERDA;
    this->queue_sender.push(mov);
}
void Cliente::mover_derecha() {
    uint8_t mov = MOVIMIENTO_DERECHA;
    this->queue_sender.push(mov);
}
void Cliente::saltar_hacia_delante() {
    uint8_t mov = MOVIMIENTO_ARRIBA_ADELANTE;
    this->queue_sender.push(mov);
}
void Cliente::saltar_hacia_atras() {
    uint8_t mov = MOVIMIENTO_ARRIBA_ATRAS;
    this->queue_sender.push(mov);
}




Cliente::~Cliente() {
    lanzador.terminar();
    lanzador.join();
}