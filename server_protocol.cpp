#include <utility>
#include <vector>
#include <algorithm>
#include "server_protocol.h"
#include <ostream>
#include <iostream>

ProtocoloServer::ProtocoloServer(
    Socket socket) : socket(std::move(socket))
{
}

void ProtocoloServer::enviar_id(int jugador_id)
{
    // Preparar el byte a enviar
    bool was_closed = false;
    uint8_t byte_a_enviar = static_cast<uint8_t>(jugador_id);

    // Enviar el byte a través del socket
    socket.sendall(&byte_a_enviar, 1, &was_closed);
    if (was_closed)
    {
        en_conexion = false;
    }
}

void ProtocoloServer::enviar_turno(int jugador_id)
{
    // Preparar los bytes a enviar
    bool was_closed = false;
    uint8_t bytes_a_enviar[2];
    bytes_a_enviar[0] = 0x00;
    bytes_a_enviar[1] = static_cast<uint8_t>(jugador_id);

    // Enviar los bytes a través del socket
    socket.sendall(bytes_a_enviar, 2, &was_closed);
    if (was_closed)
    {
        en_conexion = false;
    }
}

int ProtocoloServer::leer_movimiento()
{
    std::vector<std::int8_t> buffer(1);
    bool was_closed = false;
    try
    {
        socket.recvall(buffer.data(), 1, &was_closed);
        if (was_closed)
        {
            en_conexion = false;
        }
        return static_cast<int>(buffer[0] & 0xFF);
    }
    catch (const std::exception &err)
    {
        return -1;
    }
}

void ProtocoloServer::enviar_jugador(int id, int x, int y)
{
    std::vector<int8_t> buffer = traducir_jugador_a_enviar(id, x, y);
    bool was_closed = false;
    int tamanio = sizeof(int8_t) * buffer.size();
    socket.sendall(buffer.data(), tamanio, &was_closed);
    if (was_closed)
    {
        en_conexion = false;
    }
}

void ProtocoloServer::enviar_viga(bool tipo, int x, int y)
{
    std::vector<int8_t> buffer = traducir_viga_a_enviar(tipo, x, y);
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

std::vector<int8_t> ProtocoloServer::traducir_viga_a_enviar(bool tipo, int x, int y)
{

    std::vector<int8_t> mensaje_serializado(6);

    mensaje_serializado[0] = 0x09;

    mensaje_serializado[1] = tipo ? 0x01 : 0x00;

    // Serializar el valor de x (16 bits)
    mensaje_serializado[2] = static_cast<int8_t>((x >> 8) & 0xFF);
    mensaje_serializado[3] = static_cast<int8_t>(x & 0xFF);

    // Serializar el valor de y (16 bits)
    mensaje_serializado[4] = static_cast<int8_t>((y >> 8) & 0xFF);
    mensaje_serializado[5] = static_cast<int8_t>(y & 0xFF);

    return mensaje_serializado;
}

std::vector<int8_t> ProtocoloServer::traducir_jugador_a_enviar(int id, int x, int y)
{
    std::vector<int8_t> mensaje_serializado(7);

    mensaje_serializado[0] = 0x01; // Código inicial

    // Serializar el valor de id (16 bits)
    mensaje_serializado[1] = static_cast<int8_t>((id >> 8) & 0xFF);
    mensaje_serializado[2] = static_cast<int8_t>(id & 0xFF);

    // Serializar el valor de x (16 bits)
    mensaje_serializado[3] = static_cast<int8_t>((x >> 8) & 0xFF);
    mensaje_serializado[4] = static_cast<int8_t>(x & 0xFF);

    // Serializar el valor de y (16 bits)
    mensaje_serializado[5] = static_cast<int8_t>((y >> 8) & 0xFF);
    mensaje_serializado[6] = static_cast<int8_t>(y & 0xFF);

    return mensaje_serializado;
}
