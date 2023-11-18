#ifndef SERVER_RECEIVER_H_
#define SERVER_RECEIVER_H_

#include <vector>
#include <string>
#include <fstream>

#include "server_protocol.h"
#include "../common_src/thread.h"
#include "../common_src/queue.h"

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
