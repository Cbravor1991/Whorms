#ifndef CLIENT_SENDER_H_
#define CLIENT_SENDER_H_

#include <vector>
#include <string>
#include <fstream>
#include "common_socket.h"
#include "client_protocol.h"
#include "client_receiver.h"
#include "queue.h"
#include "thread.h"
#include "common_state_game.h"

static const char MOVE[] = "move";
static const char SALIR[] = "exit";

class ClienteLanzador : public Thread
{
private:
    ProtocoloCliente& protocolo;
    bool en_conexion = true;

    void ejecutar_accion(const std::string &linea);
    Queue<uint8_t>& queue_sender;
    Queue<StateGame>& queue_receiver;
    ClienteRecibidor cliente_recibidor;

public:
    ClienteLanzador(ProtocoloCliente& protocolo, Queue<uint8_t>& queue_sender, Queue<StateGame>& queue_receiver);

    void run() override;

    void terminar();
};

#endif
