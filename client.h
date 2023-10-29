

#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include <map>
#include <vector>
#include "common_socket.h"
#include "client_protocol.h"
#include "client_sender.h"
#include "common_state_game.h"

class Cliente
{
private:
    const std::string hostname;
    const std::string servname;
    ProtocoloCliente protocolo;
    bool conectado = true;
    uint8_t id;
    Queue<uint8_t> queue_sender;
    Queue<StateGame> queue_receiver;
    std::atomic<bool> turno_activo{false};

public:
    Cliente(const std::string &hostname, const std::string &servname);

    void run();

    void cargar_id_jugador(const uint8_t id);
    uint8_t obtener_id_jugador();




    Cliente(const Cliente &) = delete;
    Cliente &operator=(const Cliente &) = delete;
};

#endif //  CLIENT_H_
