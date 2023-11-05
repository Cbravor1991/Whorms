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

void ProtocoloServer::enviar_byte(const uint8_t &dato)
{
    bool was_closed = false;
    // Enviar el byte a través del socket
    socket.sendall(&dato, 1, &was_closed);
    if (was_closed)
    {
        en_conexion = false;
    }
}

void ProtocoloServer::enviar_int(int entero)
{
    uint8_t byte_a_enviar = static_cast<uint8_t>(entero);
    enviar_byte(byte_a_enviar);
}

void ProtocoloServer::enviar_id(int id)
{
    enviar_int(id);
}

void ProtocoloServer::enviar_turno(int turno_id)
{
    enviar_byte(CAMBIO_TURNO);
    enviar_int(turno_id);
}

void ProtocoloServer::enviar_segundos(int segundos)
{
    enviar_byte(SEGUNDOS);
    enviar_int(segundos);
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

void ProtocoloServer::enviar_jugador(int id, int x, int y, int angulo)
{
    enviar_int(id);
    enviar_int(x);
    enviar_int(y);
    enviar_int(angulo);
}

void ProtocoloServer::enviar_viga(bool tipo, int x, int y, int angulo)
{
    enviar_int(static_cast<int>(tipo));
    enviar_int(x);
    enviar_int(y);
    enviar_int(angulo);
}

void ProtocoloServer::enviar_informacion_escenario(int x, int y, int cantidad_vigas)
{
    enviar_byte(ESCENARIO);
    enviar_int(x);
    enviar_int(y);
    enviar_int(cantidad_vigas);
}

void ProtocoloServer::enviar_cantidad_jugadores(int cantidad)
{
    enviar_byte(PAQUETE);
    enviar_int(cantidad);
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
