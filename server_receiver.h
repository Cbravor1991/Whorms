#ifndef SERVER_RECEIVER_H_
#define SERVER_RECEIVER_H_

#include <vector>
#include <string>
#include <fstream>
#include "escenario.h"
#include "common_socket.h"
#include "server_protocol.h"
#include "thread.h"

const int MOVIMIENTO_DERECHA = 0;
const int MOVIMIENTO_IZQUIERDA = 1;
const int MOVIMIENTO_ARRIBA_ADELANTE = 2;
const int MOVIMIENTO_ARRIBA_ATRAS = 3;

class Escenario;

class ServerRecibidor : public Thread
{
private:
    Escenario *escenario;
    ProtocoloServer *protocolo;
    bool server_cerrado = false;
    int jugador;

    void recibir_movimiento();

public:
    ServerRecibidor(Escenario *escenario, ProtocoloServer *protocolo);

    void run() override;

    void cerrar();
};

#endif
