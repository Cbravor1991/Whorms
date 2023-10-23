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

public:
    explicit ServerLanzador(ProtocoloServer *protocolo);

    void run() override;

    void enviar_viga(bool tipo, int x, int y);

    void enviar_cantidad_jugadores(int cantidad);

    void enviar_jugador(int id, int x, int y);
};

#endif
