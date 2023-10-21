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

    std::cout << numero << std::endl;

    int8_t byte = static_cast<int8_t>(numero);

    // Envía el byte
    socket.sendall(&byte, 1, &was_closed);

    if (was_closed)
    {
        en_conexion = false;
    }
}

bool ProtocoloCliente::recibir_mensaje()
{
    bool was_closed = false;
    uint8_t buffer;
    socket.recvall(&buffer, RECIBO_BYTE, &was_closed);
    if (was_closed)
    {
        en_conexion = false;
    }
    return traducir_tipo_mensaje(buffer);
}

std::string ProtocoloCliente::recibir_chat()
{
    bool was_closed = false;
    uint16_t buffer;
    socket.recvall(&buffer, BYTES_LONGITUD, &was_closed);
    if (was_closed)
    {
        en_conexion = false;
    }
    int tamanio = traducir_tamanio_mensaje(buffer);
    std::vector<std::int8_t> buffer_chat(tamanio);
    socket.recvall(buffer_chat.data(), tamanio, &was_closed);
    if (was_closed)
    {
        en_conexion = false;
    }
    return traducir_mensaje_chat(buffer_chat, tamanio);
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

bool ProtocoloCliente::traducir_tipo_mensaje(const uint8_t &buffer)
{
    bool tipo = true;
    if (buffer == CANT_JUGADORES)
    {
        tipo = true;
    }
    else if (buffer == RECIBIR_CHAT)
    {
        tipo = false;
    }
    return tipo;
}

std::vector<int8_t> ProtocoloCliente::traducir_mensaje_a_enviar(const std::string &linea)
{
    return serializar_acciones(linea);
}

int ProtocoloCliente::traducir_mensaje_cantidad(const uint8_t &buffer)
{
    return static_cast<int>(static_cast<unsigned char>(buffer));
}

std::string ProtocoloCliente::traducir_mensaje_chat(const std::vector<std::int8_t> &buffer,
                                                    int longitud)
{
    std::string chat;

    if (!buffer.empty())
    {
        chat.assign(buffer.begin(), buffer.begin() + longitud);
    }

    return chat;
}

int ProtocoloCliente::traducir_tamanio_mensaje(const uint16_t &buffer)
{
    uint16_t longitud;
    std::memcpy(&longitud, &buffer, sizeof(uint16_t));

    longitud = ntohs(longitud);
    return longitud;
}

std::vector<int8_t> ProtocoloCliente::serializar_acciones(
    const std::string &chat)
{
    std::vector<int8_t> mensaje_serializado;
    uint16_t chat_longitud = htons(static_cast<uint16_t>(chat.size()));

    // Agrega el código de acción (0x05)
    mensaje_serializado.push_back(ENVIAR_CHAT);

    // Agrega la longitud del mensaje en big-endian
    uint8_t *length_ptr = reinterpret_cast<uint8_t *>(&chat_longitud);
    mensaje_serializado.push_back(length_ptr[0]);
    mensaje_serializado.push_back(length_ptr[1]);

    // Agrega el mensaje de chat
    std::copy(chat.begin(), chat.end(), std::back_inserter(mensaje_serializado));

    return mensaje_serializado;
}

bool ProtocoloCliente::sigue_conectado()
{
    return en_conexion;
}
