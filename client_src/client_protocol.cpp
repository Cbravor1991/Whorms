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

int ProtocoloCliente::recibir_int()
{
    uint8_t byte = recibir_byte();
    int entero = static_cast<int>(byte);
    return entero;
}

int ProtocoloCliente::recibir_int_grande()
{
    uint8_t byte_msb = recibir_byte();
    uint8_t byte_lsb = recibir_byte();
    int entero = (static_cast<int>(byte_msb) << 8) | static_cast<int>(byte_lsb);
    return entero;
}

void ProtocoloCliente::enviar_int_grande(int entero)
{
    // Dividir el int en dos bytes
    uint8_t byte_msb = static_cast<uint8_t>((entero >> 8) & 0xFF); // byte más significativo
    uint8_t byte_lsb = static_cast<uint8_t>(entero & 0xFF);        // byte menos significativo

    // Enviar los dos bytes a través del socket
    enviar_byte(byte_msb);
    enviar_byte(byte_lsb);
}

uint8_t ProtocoloCliente::recibir_byte()
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
        return buffer;
    }
    catch (const std::exception &err)
    {
        return -1;
    }
}

int ProtocoloCliente::recibir_id_jugador()
{
    return recibir_int();
}

StateGame *ProtocoloCliente::recibir_turno(int jugador_id)
{
    int turno_id = recibir_int();
    bool permiso = (turno_id == jugador_id);
    StateGame *estado_juego = new TurnoDTO(turno_id, permiso);
    return estado_juego;
}

StateGame *ProtocoloCliente::recibir_segundo()
{
    int segundo = recibir_int();
    StateGame *estado_juego = new SegundosDTO(segundo);
    return estado_juego;
}

void ProtocoloCliente::enviar_movimiento(int tipo)
{
    enviar_byte(ENVIAR_MOVIMIENTO);
    enviar_int(tipo);
}

void ProtocoloCliente::enviar_arma(int tipo)
{
    enviar_byte(ENVIAR_ARMA);
    enviar_int(tipo);
}

void ProtocoloCliente::enviar_posicion(int x, int y)
{
    enviar_byte(ENVIAR_TELEDIRIGIDO);
    enviar_int_grande(x);
    enviar_int_grande(y);
}

void ProtocoloCliente::enviar_byte(const uint8_t &dato)
{
    bool was_closed = false;
    // Enviar el byte a través del socket
    socket.sendall(&dato, 1, &was_closed);
    if (was_closed)
    {
        en_conexion = false;
    }
}

void ProtocoloCliente::enviar_int(int entero)
{
    uint8_t byte_a_enviar = static_cast<uint8_t>(entero);
    enviar_byte(byte_a_enviar);
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
    std::vector<ObjetoDTO> objetos;
    int cantidad_jugadores = recibir_int();

    for (int i = 0; i < cantidad_jugadores; i++)
    {
        JugadorDTO jugador = recibir_jugador();
        jugadores.push_back(jugador);
    }

    int cantidad_objetos = recibir_int();
    for (int i = 0; i < cantidad_objetos; i++)
    {
        ObjetoDTO objeto = recibir_objeto();
        objetos.push_back(objeto);
    }
    StateGame *estado_juego = new PaqueteDTO(jugadores, objetos);
    return estado_juego;
}

StateGame *ProtocoloCliente::recibir_escenario()
{
    std::vector<VigaDTO> vigas;
    int x = recibir_int();

    int y = recibir_int();

    int cantidad_vigas = recibir_byte();

    for (int i = 0; i < cantidad_vigas; i++)
    {
        VigaDTO viga = recibir_viga();
        vigas.push_back(viga);
    }

    StateGame *estado_juego = new EscenarioDTO(x, y, vigas);
    return estado_juego;
}

ObjetoDTO ProtocoloCliente::recibir_objeto()
{

    int tipo = recibir_int();
    int x = recibir_int_grande();
    int y = recibir_int_grande();
    bool direccion = static_cast<bool>(recibir_int());
    int angulo = recibir_int();
    bool explosion = (recibir_byte() != 0);
    ObjetoDTO objeto(tipo, x, y, direccion, angulo - 45, explosion);
    return objeto;
}

JugadorDTO ProtocoloCliente::recibir_jugador()
{

    int id = recibir_int();
    int id_cliente = recibir_int();
    int x = recibir_int_grande();
    int y = recibir_int_grande();
    bool direccion = static_cast<bool>(recibir_int());
    int angulo = recibir_int();
    int vida = recibir_int();
    bool en_movimiento = static_cast<bool>(recibir_int());
    JugadorDTO jugador(id, x, y, direccion, angulo - 45, vida, en_movimiento, id_cliente);
    return jugador;
}

StateGame *ProtocoloCliente::recibir_arma()
{
    int id = recibir_int();
    int id_cliente = recibir_int();
    int arma = recibir_int();
    int ammo = recibir_int();
    StateGame *estado = new ArmaDTO(id, id_cliente, arma, ammo);
    return estado;
}

VigaDTO ProtocoloCliente::recibir_viga()
{
    int tipo = recibir_int();
    int x = recibir_int_grande();
    int y = recibir_int_grande();
    int angulo = recibir_int();
    VigaDTO viga(tipo, x, y, angulo - 45); //
    return viga;
}

int ProtocoloCliente::traducir_tipo_mensaje(const uint8_t &buffer)
{
    int tipo = -1;
    if (buffer == RECIBIR_TURNO)
    {
        tipo = TIPO_TURNO;
    }
    else if (buffer == RECIBIR_SEGUNDO)
    {
        tipo = TIPO_SEGUNDO;
    }
    else if (buffer == RECIBIR_PAQUETE)
    {
        tipo = TIPO_PAQUETE;
    }
    else if (buffer == RECIBIR_ESCENARIO)
    {
        tipo = TIPO_ESCENARIO;
    }
    else if (buffer == RECIBIR_ARMA)
    {
        tipo = TIPO_ARMA;
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
        }
        break;

    case TIPO_SEGUNDO:
        if (conectado)
        {

            estado = recibir_segundo();
        }
        break;
    case TIPO_PAQUETE:
        if (conectado)
        {
            estado = recibir_paquete();
        }
        break;

    case TIPO_ESCENARIO:
        if (conectado)
        {

            estado = recibir_escenario();
        }
        break;
    case TIPO_ARMA:
        if (conectado)
        {

            estado = recibir_arma();
        }
        break;
        // case TIPO_PAQUETE_OBJETOS:if (conectado) {estado = recibir_paquete();estado->type = TIPO_PAQUETE_OBJ;}break;
    }

    return estado;
}
