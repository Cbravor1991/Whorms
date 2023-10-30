#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <netinet/in.h>
#include <cstring>
#include <mutex>
#include <string>
#include <vector>
#include "../common_src/common_socket.h"
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

    std::vector<int8_t> traducir_viga_a_enviar(bool tipo, int x, int y);

    std::vector<int8_t> traducir_jugador_a_enviar(int id, int x, int y);

    std::string traducir_mensaje_recibido(
        const std::vector<std::int8_t> &buffer, int longitud);

public:
    explicit ProtocoloServer(Socket socket);

    int leer_movimiento();

    void enviar_turno(int jugador_id);

    void enviar_id(int jugador_id);

    void enviar_jugador(int id, int x, int y);

    void enviar_viga(bool tipo, int x, int y);

    void enviar_cantidad_jugadores(int cantidad);

    bool check_en_conexion();

    void desconectar();
};

#endif
