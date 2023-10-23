#include <iostream>
#include <fstream>
#include <vector>
#include <netinet/in.h>
#include <sstream>
#include <algorithm>
#include "client_protocol.h"
#include "common_liberror.h"
#include <tuple>

ProtocoloCliente::ProtocoloCliente(const std::string &hostname,
                                   const std::string &servname) : socket(hostname.c_str(), servname.c_str())
{
}

void ProtocoloCliente::enviar_mensaje(const std::string &mensaje)
{
    bool was_closed = false;

    // Convierte la cadena a un número entero
    int numero = std::stoi(mensaje);

    int8_t byte = static_cast<int8_t>(numero);

    // Envía el byte
    socket.sendall(&byte, 1, &was_closed);

    if (was_closed)
    {
        en_conexion = false;
    }
}

int ProtocoloCliente::recibir_mensaje()
{
    bool was_closed = false;
    uint8_t buffer;
    try
    {

        socket.recvall(&buffer, RECIBO_BYTE, &was_closed);
        if (was_closed)
        {
            en_conexion = false;
        }
        return traducir_tipo_mensaje(buffer);
    }
    catch (const std::exception &err)
    {
        return 1;
    }
}

Jugador ProtocoloCliente::recibir_jugador()
{
    bool was_closed = false;
    Jugador jugador;

    // Recibir el ID del jugador
    socket.recvall(&(jugador.id), BYTES_ID, &was_closed);
    jugador.id = ntohs(jugador.id);

    if (was_closed)
    {
        en_conexion = false;
        return jugador; // Devuelve el objeto jugador con ID vacío
    }

    // Recibir la coordenada X
    socket.recvall(&(jugador.x), BYTES_X, &was_closed);
    jugador.x = ntohs(jugador.x);

    if (was_closed)
    {
        en_conexion = false;
        return jugador; // Devuelve el objeto jugador con X vacío
    }

    // Recibir la coordenada Y
    socket.recvall(&(jugador.y), BYTES_Y, &was_closed);
    jugador.y = ntohs(jugador.y);

    if (was_closed)
    {
        en_conexion = false;
        return jugador; // Devuelve el objeto jugador con Y vacío
    }

    return jugador; // Devuelve el objeto jugador con ID, X e Y
}

Viga ProtocoloCliente::recibir_viga()
{
    bool was_closed = false;
    Viga viga;

    // Recibir el tipo de viga
    socket.recvall(&(viga.tipo), BYTES_TIPO, &was_closed);

    if (was_closed)
    {
        en_conexion = false;
        return viga;
    }

    // Recibir la coordenada X
    socket.recvall(&(viga.x), BYTES_X, &was_closed);
    viga.x = ntohs(viga.x);

    if (was_closed)
    {
        en_conexion = false;
        return viga;
    }

    // Recibir la coordenada Y
    socket.recvall(&(viga.y), BYTES_Y, &was_closed);
    viga.y = ntohs(viga.y);

    if (was_closed)
    {
        en_conexion = false;
        return viga;
    }

    return viga;
}

int ProtocoloCliente::recibir_cantidad_jugadores()
{
    bool was_closed = false;
    uint8_t buffer;
    socket.recvall(&buffer, RECIBO_BYTE, &was_closed);
    if (was_closed)
    {
        en_conexion = false;
    }
    int cantidad = traducir_mensaje_cantidad(buffer);
    return cantidad;
}

int ProtocoloCliente::traducir_tipo_mensaje(const uint8_t &buffer)
{
    int tipo;
    if (buffer == CANT_JUGADORES)
    {
        tipo = 0;
    }
    else if (buffer == RECIBIR_JUGADOR)
    {
        tipo = 1;
    }
    else if (buffer == RECIBIR_VIGA)
    {
        tipo = 2;
    }
    return tipo;
}

int ProtocoloCliente::traducir_mensaje_cantidad(const uint8_t &buffer)
{
    return static_cast<int>(static_cast<unsigned char>(buffer));
}

void ProtocoloCliente::desconectar()
{
    en_conexion = false;
    socket.shutdown(2);
    socket.close();
}

bool ProtocoloCliente::check_en_conexion()
{
    return en_conexion;
}
