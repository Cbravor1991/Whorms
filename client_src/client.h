

#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include <map>
#include <vector>
#include "../common_src/common_socket.h"
#include "client_protocol.h"
#include "client_sender.h"
#include "DTO/common_state_game.h"
#include <optional>

class Cliente
{
private:
    ProtocoloCliente& protocolo;
    bool conectado = true;
    uint8_t id;
    Queue<Action*> queue_sender;
    Queue<StateGame *> queue_receiver;
    ClienteLanzador lanzador;

public:
    Cliente(ProtocoloCliente&  protocolo);
    ~Cliente();

    void cargar_id_jugador(const uint8_t id);
    uint8_t obtener_id_jugador();
    void procesar_mensaje();

    bool esta_conectado();

    std::optional<StateGame *> obtener_estado();
    void autorizar_turno(bool permiso);

    void mandar_accion(Action* action);

    Cliente(const Cliente &) = delete;
    Cliente &operator=(const Cliente &) = delete;
};

#endif //  CLIENT_H_
