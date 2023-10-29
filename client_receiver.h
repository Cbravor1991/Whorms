#ifndef CLIENT_RECEIVER_H_
#define CLIENT_RECEIVER_H_

#include <vector>
#include <string>
#include <fstream>
#include "common_socket.h"
#include "thread.h"
#include "queue.h"
#include "common_state_game.h"
#include "client_protocol.h"

class ClienteRecibidor : public Thread
{
private:
    ProtocoloCliente& protocolo;
    bool cliente_cerrado = false;
    int jugador;
    Queue<StateGame>& queue_receiver;

public:
    ClienteRecibidor(ProtocoloCliente& protocolo, Queue<StateGame>& queue_receiver);

    void run() override;

    void terminar();
};

#endif
