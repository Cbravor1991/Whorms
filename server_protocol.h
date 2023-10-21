#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <netinet/in.h>
#include <cstring>
#include <queue>
#include <mutex>
#include <string>
#include <vector>
#include <condition_variable>
#include "common_socket.h"
#include <atomic>

struct Mensaje
{
    std::string cadena = "";
    // cppcheck-suppress unusedStructMember
    bool tipo_mensaje = false;
};

const std::int8_t CANT_JUGADORES = 0x06;
const std::int8_t CHAT = 0x09;
const int BYTES_CANT_JUGADORES = 2;
const int BYTES_LONGITUD = 3;

class ProtocoloServer
{
private:
    Socket socket;
    std::atomic<bool> en_conexion{true};

    int leer_longitud();

    std::vector<int8_t> traducir_cantidad_jugadores_a_enviar(int cantidad);

    std::vector<int8_t> traducir_mensaje_a_enviar(const std::string &chat);

    int traducir_tamanio_mensaje(const std::vector<std::int8_t> &buffer);

    std::string traducir_mensaje_recibido(
        const std::vector<std::int8_t> &buffer, int longitud);

public:
    explicit ProtocoloServer(Socket socket);

    int leer_movimiento();

    void enviar_mensaje(const std::string &chat);

    void enviar_cantidad_jugadores(int cantidad);

    bool check_en_conexion();

    void desconectar();
};

#endif
