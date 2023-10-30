#ifndef SERVER_JUGADOR_H_
#define SERVER_JUGADOR_H_

#include <vector>
#include <string>
#include <fstream>
#include "server_receiver.h"
#include "../common_src/common_socket.h"
#include "server_sender.h"
#include "../common_src/thread.h"

class Jugador
{
private:
    ProtocoloServer *socket;
    ServerLanzador *lanzador;
    ServerRecibidor *recibidor;
    Queue<Data *> *cola;

public:
    Jugador(ProtocoloServer *socket);

    void jugar(Queue<Accion *> *cola, int jugador_id);

    void recibir_comando(Data *comando);

    bool sigo_conectado();

    ~Jugador();
};

#endif //  SERVERL_H_
