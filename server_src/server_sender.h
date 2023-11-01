#ifndef SERVER_SENDER_H_
#define SERVER_SENDER_H_

#include <vector>
#include <string>
#include <fstream>
#include "server_protocol.h"
#include "../common_src/queue.h"
#include "../common_src/thread.h"
#include "data/data_DTO.h"

class ServerLanzador : public Thread
{
private:
    ProtocoloServer *protocolo;
    Queue<Data *> *cola;

public:
    ServerLanzador(ProtocoloServer *protocolo, Queue<Data *> *cola);

    void run() override;
};

#endif
