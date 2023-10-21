#include <utility>
#include <vector>
#include <algorithm>
#include "server_protocol.h"

ProtocoloServer::ProtocoloServer(
    Socket socket) : socket(std::move(socket))
{
}

int ProtocoloServer::leer_movimiento()
{
    std::vector<std::int8_t> buffer(1);
    bool was_closed = false;
    socket.recvall(buffer.data(), 1, &was_closed);
    if (was_closed)
    {
        en_conexion = false;
    }
    return static_cast<int>(buffer[0] & 0xFF);
}

int ProtocoloServer::leer_longitud()
{
    std::vector<std::int8_t> buffer(BYTES_LONGITUD);
    bool was_closed = false;
    try
    {

        socket.recvall(buffer.data(), BYTES_LONGITUD, &was_closed);
        if (was_closed)
        {
            en_conexion = false;
        }
        int longitud = traducir_tamanio_mensaje(buffer);
        return longitud;
    }
    catch (const std::exception &err)
    {
        return 1;
    }
}

void ProtocoloServer::enviar_mensaje(const std::string &chat)
{
    std::vector<int8_t> buffer = traducir_mensaje_a_enviar(chat);
    bool was_closed = false;
    int tamanio = sizeof(int8_t) * buffer.size();
    socket.sendall(buffer.data(), tamanio, &was_closed);
    if (was_closed)
    {
        en_conexion = false;
    }
}

void ProtocoloServer::enviar_cantidad_jugadores(int cantidad)
{
    std::vector<int8_t> buffer = traducir_cantidad_jugadores_a_enviar(cantidad);
    bool was_closed = false;
    int tamanio = sizeof(int8_t) * buffer.size();
    socket.sendall(buffer.data(), tamanio, &was_closed);
    if (was_closed)
    {
        en_conexion = false;
    }
}

bool ProtocoloServer::check_en_conexion()
{
    return en_conexion;
}

void ProtocoloServer::desconectar()
{
    en_conexion = false;
    socket.shutdown(2);
    socket.close();
}

std::vector<int8_t> ProtocoloServer::traducir_cantidad_jugadores_a_enviar(int cantidad)
{
    std::vector<int8_t> mensaje_cantidad(BYTES_CANT_JUGADORES);

    mensaje_cantidad[0] = CANT_JUGADORES;

    mensaje_cantidad[1] = static_cast<int8_t>(cantidad);

    return mensaje_cantidad;
}

std::vector<int8_t> ProtocoloServer::traducir_mensaje_a_enviar(const std::string &chat)
{
    std::vector<int8_t> mensaje_serializado;

    uint16_t chat_msg_length = htons(static_cast<uint16_t>(chat.size()));

    mensaje_serializado.push_back(CHAT);

    // Agrega la longitud del mensaje en big-endian
    uint8_t *length_ptr = reinterpret_cast<uint8_t *>(&chat_msg_length);
    mensaje_serializado.push_back(length_ptr[0]);
    mensaje_serializado.push_back(length_ptr[1]);

    // Agrega el mensaje de chat
    std::copy(chat.begin(), chat.end(), std::back_inserter(mensaje_serializado));
    return mensaje_serializado;
}

int ProtocoloServer::traducir_tamanio_mensaje(const std::vector<std::int8_t> &buffer)
{
    uint16_t longitud;
    std::memcpy(&longitud, &buffer[1], sizeof(uint16_t));
    longitud = ntohs(longitud);
    return longitud;
}

std::string ProtocoloServer::traducir_mensaje_recibido(
    const std::vector<std::int8_t> &buffer, int longitud)
{
    std::string tipo(buffer.begin(), buffer.begin() + longitud);
    return tipo;
}
