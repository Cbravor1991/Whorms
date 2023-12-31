#ifndef CLIENT_SENDER_H_
#define CLIENT_SENDER_H_

#include <vector>
#include <string>
#include <fstream>
#include "../common_src/common_socket.h"
#include "client_protocol.h"
#include "client_receiver.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "DTO/common_state_game.h"
#include "actions/action.h"


static const char MOVE[] = "move";
static const char SALIR[] = "exit";

class ClienteLanzador : public Thread
{
private:
    ProtocoloCliente &protocolo;
    bool en_conexion = true;
    bool turno = false;

    Queue<Action*> &queue_sender;
    Queue<StateGame *> &queue_receiver;
    ClienteRecibidor cliente_recibidor;

public:
    ClienteLanzador(ProtocoloCliente &protocolo, Queue<Action*> &queue_sender, Queue<StateGame *> &queue_receiver);

    void run() override;

    void terminar();

    void autorizar_turno(bool turno);
};

#endif
