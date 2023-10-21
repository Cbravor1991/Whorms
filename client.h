

#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include <map>
#include <vector>
#include "common_socket.h"
#include "client_protocol.h"

static const char READ[] = "Read";
static const char EXIT[] = "Exit";
static const char CHAT[] = "Chat";

class Cliente
{
private:
    const std::string hostname;
    const std::string servname;
    ProtocoloCliente protocolo;
    bool conectado = true;

    void recibir_mensaje(int cantidad);

   
    void ejecutar_accion(const std::string &linea);

public:
  
    Cliente(const std::string &hostname, const std::string &servname);

    bool run();

    Cliente(const Cliente &) = delete;
    Cliente &operator=(const Cliente &) = delete;
};

#endif //  CLIENT_H_
