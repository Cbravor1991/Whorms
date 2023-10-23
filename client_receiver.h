#ifndef CLIENT_RECEIVER_H_
#define CLIENT_RECEIVER_H_

#include <vector>
#include <string>
#include <fstream>
#include "common_socket.h"
#include "client_protocol.h"
#include "thread.h"

const int TIPO_CANTIDAD_JUGADORES = 0;
const int TIPO_JUGADOR = 1;
const int TIPO_VIGA = 2;

class ClienteRecibidor : public Thread
{
private:
    ProtocoloCliente *protocolo;
    bool cliente_cerrado = false;
    int jugador;

    void recibir_mensaje();

public:
    explicit ClienteRecibidor(ProtocoloCliente *protocolo);

    void run() override;

    void terminar();
};

#endif
