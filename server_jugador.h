#ifndef SERVER_JUGADOR_H_
#define SERVER_JUGADOR_H_

#include <vector>
#include <string>
#include <fstream>
#include "server_receiver.h"
#include "common_socket.h"
#include "server_sender.h"
#include "thread.h"

class ServerRecibidor;

class Jugador
{
private:
    ProtocoloServer *socket;
    ServerLanzador *lanzador;
    ServerRecibidor *recibidor;

public:
    
    Jugador(ProtocoloServer *socket, ServerLanzador *lanzador, ServerRecibidor *recibidor);

    void recibir_mensaje(Mensaje mensaje);

    bool sigo_conectado();

    ~Jugador();
};

#endif //  SERVERL_H_
