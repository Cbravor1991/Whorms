

#ifndef CLIENT_PROTOCOL_H_
#define CLIENT_PROTOCOL_H_

#include <string>
#include <map>
#include <vector>
#include <tuple>
#include "common_socket.h"
#include <cstring>

struct Jugador
{
    int id;
    int x;
    int y;
};

struct Viga
{
    bool tipo;
    int x;
    int y;
};

const std::int8_t CANT_JUGADORES = 0x06;
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

    void enviar_mensaje(const std::string &mensaje);

    int recibir_mensaje();

    int recibir_cantidad_jugadores();

    Jugador recibir_jugador();

    Viga recibir_viga();

    bool check_en_conexion();

    void desconectar();

    ProtocoloCliente(const ProtocoloCliente &) = delete;
    ProtocoloCliente &operator=(const ProtocoloCliente &) = delete;
};

#endif //  CLIENT_PROTOCOL_H_
