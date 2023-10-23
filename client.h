

#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include <map>
#include <vector>
#include "common_socket.h"
#include "client_protocol.h"
#include "client_sender.h"

class Cliente
{
private:
    const std::string hostname;
    const std::string servname;
    ProtocoloCliente *protocolo;
    bool conectado = true;

public:
    Cliente(const std::string &hostname, const std::string &servname);

    void run();

    Cliente(const Cliente &) = delete;
    Cliente &operator=(const Cliente &) = delete;
};

#endif //  CLIENT_H_
