

#ifndef CLIENT_PROTOCOL_H_
#define CLIENT_PROTOCOL_H_

#include <string>
#include <map>
#include <vector>
#include <tuple>
#include "common_socket.h"
#include "common_state_game.h"
#include <cstring>


const int TIPO_CANTIDAD_JUGADORES = 0;
const int TIPO_JUGADOR = 1;
const int TIPO_VIGA = 2;
const int TIPO_TURNO = 3;

struct Viga
{
    bool tipo;
    int x;
    int y;
};

const std::int8_t CANT_JUGADORES = 0x06;
const std::int8_t RECIBIR_TURNO = 0x00;
const std::int8_t RECIBIR_JUGADOR = 0x01;
const std::int8_t RECIBIR_VIGA = 0x09;
const std::int8_t ENVIAR_CHAT = 0x05;
const int RECIBO_BYTE = 1;
const int BYTES_ID = 2;
const int BYTES_X = 2;
const int BYTES_Y = 2;
const int BYTES_TIPO = 1;

class ProtocoloCliente
{
private:
    Socket socket;
    bool en_conexion = true;

    int traducir_mensaje_cantidad(const uint8_t &buffer);

    int traducir_tipo_mensaje(const uint8_t &buffer);

public:
    ProtocoloCliente(const std::string &hostname,
                     const std::string &servname);

    int recibir_id();

    void enviar_mensaje(const std::string &mensaje);

    int recibir_mensaje();

    int recibir_cantidad_jugadores();

    JugadorDTO recibir_jugador();

    Viga recibir_viga();

    StateGame procesar_mensaje();

    bool check_en_conexion();

    void desconectar();

    ProtocoloCliente(const ProtocoloCliente &) = delete;
    ProtocoloCliente &operator=(const ProtocoloCliente &) = delete;
};

#endif //  CLIENT_PROTOCOL_H_
