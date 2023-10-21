#ifndef SERVER_ACCEPTOR_H_
#define SERVER_ACCEPTOR_H_

#include <vector>
#include <string>
#include <fstream>
#include "queue.h"
#include "thread.h"
#include "common_socket.h"
#include "escenario.h"

class ServerAceptador : public Thread
{
private:
    Socket socket;
    MonitorJugadores *monitor;
    bool ejecutando = true;
    Escenario *escenario;

    void lanzar_hilo_manejador(Socket skt_cliente);

public:
    ServerAceptador(const std::string &servname, MonitorJugadores *monitor);

    void run() override;

    void terminar();
};

#endif
