#ifndef SERVER_RECEIVER_H_
#define SERVER_RECEIVER_H_

#include <vector>
#include <string>
#include <fstream>
#include "common_socket.h"
#include "server_protocol.h"
#include "thread.h"

const int MOVIMIENTO_IZQUIERDA = 1;
const int MOVIMIENTO_DERECHA = 2;
const int MOVIMIENTO_ARRIBA_ADELANTE = 3;
const int MOVIMIENTO_ARRIBA_ATRAS = 4;

class ServerRecibidor : public Thread
{
private:
    ProtocoloServer *protocolo;
    Queue<std::string> *cola;
    int jugador;
    bool server_cerrado = false;

    void recibir_movimiento();

public:
    ServerRecibidor(ProtocoloServer *protocolo, Queue<std::string> *cola, int jugador);

    void run() override;

    void cerrar();
};

#endif
