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
    Queue<std::string> *cola;

    void procesar_comando(const std::string &comando);

public:
    ServerLanzador(ProtocoloServer *protocolo, Queue<std::string> *cola);

    void run() override;
};

#endif
