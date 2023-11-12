#include <iostream>
#include <fstream>
#include <vector>
#include <netinet/in.h>
#include <sstream>
#include <algorithm>
#include "client_protocol.h"
#include "DTO/common_state_game.h"
#include <tuple>

ProtocoloCliente::ProtocoloCliente(const std::string &hostname,
                                   const std::string &servname) : socket(hostname.c_str(), servname.c_str())
{
}

int ProtocoloCliente::recibir_byte()
{
    try
    {
        bool was_closed = false;
        uint8_t buffer;
        socket.recvall(&buffer, RECIBO_BYTE, &was_closed);
        if (was_closed)
        {
            en_conexion = false;
        }
        int valor_entero = static_cast<int>(buffer);

        return valor_entero;
    }
    catch (const std::exception &err)
    {
        return -1;
    }
}

int ProtocoloCliente::recibir_id_jugador()
{
    return recibir_byte();
}

StateGame *ProtocoloCliente::recibir_turno(int jugador_id)
{
    int turno_id = recibir_byte();
    bool permiso = (turno_id == jugador_id);
    StateGame *estado_juego = new TurnoDTO(turno_id, permiso);
    return estado_juego;
}

StateGame *ProtocoloCliente::recibir_segundo()
{
    int segundo = recibir_byte();
    StateGame *estado_juego = new SegundosDTO(segundo);
    return estado_juego;
}

void ProtocoloCliente::enviar_mensaje(const uint8_t &byte)
{
    bool was_closed = false;

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
        return -1;
    }
}

StateGame *ProtocoloCliente::recibir_paquete()
{
    std::vector<JugadorDTO> jugadores;
    int cantidad_jugadores = recibir_byte();

    for (int i = 0; i < cantidad_jugadores; i++)
    {
        JugadorDTO jugador = recibir_jugador();
        jugadores.push_back(jugador);
    }

    StateGame *estado_juego = new PaqueteDTO(jugadores);
    return estado_juego;
}

StateGame *ProtocoloCliente::recibir_escenario()
{
    std::vector<VigaDTO> vigas;
    int x = recibir_byte();

    int y = recibir_byte();

    int cantidad_vigas = recibir_byte();

    for (int i = 0; i < cantidad_vigas; i++)
    {
        VigaDTO viga = recibir_viga();
        vigas.push_back(viga);
    }

    StateGame *estado_juego = new EscenarioDTO(x, y, vigas);
    return estado_juego;
}

JugadorDTO ProtocoloCliente::recibir_jugador()
{
    int id = recibir_byte();
    int x = recibir_byte();
    int y = recibir_byte();
    bool direccion = static_cast<bool>(recibir_byte());
    int angulo = recibir_byte();
    JugadorDTO jugador(id, x, y, direccion, angulo - 45);
    return jugador;
}

VigaDTO ProtocoloCliente::recibir_viga()
{
    int tipo = recibir_byte();

    int x = recibir_byte();

    int y = recibir_byte();

    int angulo = recibir_byte();
    VigaDTO viga(tipo, x, y, angulo - 45);//
    return viga;
}

int ProtocoloCliente::traducir_tipo_mensaje(const uint8_t &buffer)
{
    int tipo = -1;
    if (buffer == RECIBIR_TURNO)
    {
        tipo = 0;
    }
    else if (buffer == RECIBIR_SEGUNDO)
    {
        tipo = 1;
    }
    else if (buffer == RECIBIR_PAQUETE)
    {
        tipo = 2;
    }
    else if (buffer == RECIBIR_ESCENARIO)
    {
        tipo = 3;
    }
    return tipo;
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

StateGame *ProtocoloCliente::procesar_mensaje(const int &id_jugador)
{
    StateGame *estado;
    int tipo_mensaje = recibir_mensaje();
    bool conectado = check_en_conexion();
    switch (tipo_mensaje)
    {
    case TIPO_TURNO:
        if (conectado)
        {
            estado = recibir_turno(id_jugador);
            estado->type = TIPO_TURNO;
        }
        break;

    case TIPO_SEGUNDO:
        if (conectado)
        {
            estado = recibir_segundo();
            estado->type = TIPO_SEGUNDO;
        }
        break;
    case TIPO_PAQUETE:
        if (conectado)
        {
            estado = recibir_paquete();
            estado->type = TIPO_PAQUETE;
        }
        break;

    case TIPO_ESCENARIO:
        if (conectado)
        {
            estado = recibir_escenario();
            estado->type = TIPO_ESCENARIO;
        }
        break;
    }
    return estado;
}
