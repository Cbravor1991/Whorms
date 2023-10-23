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

    void enviar_viga(bool tipo, int x, int y);

    void enviar_cantidad_jugadores(int cantidad);

    void enviar_jugador(int id, int x, int y);

    bool sigo_conectado();

    ~Jugador();
};

#endif //  SERVERL_H_
