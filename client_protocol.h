

#ifndef CLIENT_PROTOCOL_H_
#define CLIENT_PROTOCOL_H_

#include <string>
#include <map>
#include <vector>
#include <tuple>
#include "common_socket.h"
#include <cstring>

const std::int8_t CANT_JUGADORES = 0x06;
const std::int8_t RECIBIR_CHAT = 0x09;
const std::int8_t ENVIAR_CHAT = 0x05;
const int RECIBO_BYTE = 1;
const int BYTES_LONGITUD = 2;

class ProtocoloCliente
{
private:
    Socket socket;
    bool en_conexion = true;

    std::vector<std::int8_t> serializar_acciones(const std::string &chat);

    int traducir_mensaje_cantidad(const uint8_t &buffer);

    std::string traducir_mensaje_chat(const std::vector<std::int8_t> &buffer, int longitud);

    int traducir_tamanio_mensaje(const uint16_t &buffer);

    std::vector<int8_t> traducir_mensaje_a_enviar(const std::string &linea);

    bool traducir_tipo_mensaje(const uint8_t &buffer);

public:
    ProtocoloCliente(const std::string &hostname,
                     const std::string &servname);

    bool sigue_conectado();

    void enviar_mensaje(const std::string& mensaje);

    bool recibir_mensaje();

    int recibir_cantidad_jugadores();

    std::string recibir_chat();

    ProtocoloCliente(const ProtocoloCliente &) = delete;
    ProtocoloCliente &operator=(const ProtocoloCliente &) = delete;
};

#endif //  CLIENT_PROTOCOL_H_
