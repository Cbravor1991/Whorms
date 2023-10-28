#ifndef SERVER_ACCEPTOR_H_
#define SERVER_ACCEPTOR_H_

#include <vector>
#include <string>
#include <fstream>
#include "queue.h"
#include "thread.h"
#include "common_socket.h"
#include "lobby.h"
#include "server_lobby.h"

class ServerAceptador : public Thread
{
private:
    Socket socket;
    bool ejecutando = true;
    Lobby *lobby;
    bool primer_jugador = true;

    void lanzar_hilo_manejador(Socket skt_cliente);

public:
    ServerAceptador(const std::string &servname);

    void run() override;

    void terminar();
};

#endif
