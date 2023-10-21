#ifndef SERVER_SENDER_H_
#define SERVER_SENDER_H_

#include <vector>
#include <string>
#include <fstream>
#include "common_socket.h"
#include "server_protocol.h"
#include "queue.h"
#include "thread.h"

class ServerLanzador : public Thread
{
private:
    ProtocoloServer *protocolo;
    Queue<Mensaje> mensajes;

    void
    enviar_mensaje();

public:
    explicit ServerLanzador(ProtocoloServer *protocolo);

    void run() override;

    void recibir_mensaje(Mensaje mensaje);
};

#endif
