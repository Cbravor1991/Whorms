#ifndef SERVER_RECEIVER_H_
#define SERVER_RECEIVER_H_

#include <vector>
#include <string>
#include <fstream>

#include "server_protocol.h"
#include "../common_src/thread.h"
#include "../common_src/queue.h"
#include "accion/mover_izquierda.h"
#include "accion/mover_derecha.h"
#include "accion/saltar_adelante.h"
#include "accion/saltar_atras.h"
#include "accion/desconexion.h"

const int MOVIMIENTO_IZQUIERDA = 1;
const int MOVIMIENTO_DERECHA = 2;
const int MOVIMIENTO_ARRIBA_ADELANTE = 3;
const int MOVIMIENTO_ARRIBA_ATRAS = 4;

class ServerRecibidor : public Thread
{
private:
    ProtocoloServer *protocolo;
    Queue<Accion *> *cola;
    int jugador;
    bool server_cerrado = false;

    void recibir_movimiento();

public:
    ServerRecibidor(ProtocoloServer *protocolo, Queue<Accion *> *cola, int jugador);

    void run() override;

    void cerrar();
};

#endif
