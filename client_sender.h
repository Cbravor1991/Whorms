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

static const char MOVE[] = "move";
static const char SALIR[] = "exit";

class ClienteLanzador : public Thread
{
private:
    ProtocoloCliente *protocolo;
    ClienteRecibidor cliente_recibidor;
    bool en_conexion = true;

    void ejecutar_accion(const std::string &linea);

public:
    explicit ClienteLanzador(ProtocoloCliente *protocolo);

    void run() override;

    void terminar();
};

#endif
