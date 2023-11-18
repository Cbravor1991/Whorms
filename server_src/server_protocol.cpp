#include <utility>
#include <vector>
#include <algorithm>
#include "server_protocol.h"
#include <ostream>
#include <iostream>
#include "accion/mover_izquierda.h"
#include "accion/mover_derecha.h"
#include "accion/saltar_adelante.h"
#include "accion/saltar_atras.h"
#include "accion/ataque_aereo.h"

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

void ProtocoloServer::enviar_arma(int id, int arma)
{
    enviar_byte(ARMA);
    enviar_int(id);
    enviar_int(arma);
}

void ProtocoloServer::enviar_segundos(int segundos)
{
    enviar_byte(SEGUNDOS);
    enviar_int(segundos);
}

Accion *ProtocoloServer::leer_movimiento(int jugador)
{
    int tipo_movimiento = recibir_byte();
    Accion *accion;
    switch (tipo_movimiento)
    {
    case MOVIMIENTO_IZQUIERDA:
        accion = new MoverIzquierda(jugador);
        break;
    case MOVIMIENTO_DERECHA:
        accion = new MoverDerecha(jugador);
        break;
    case MOVIMIENTO_ARRIBA_ADELANTE:
        accion = new SaltarAdelante(jugador);
        break;
    case MOVIMIENTO_ARRIBA_ATRAS:
        accion = new SaltarAtras(jugador);
        break;
    default:
        // Manejo de un movimiento no válido, si es necesario
        break;
    }
    return accion;
}

Accion *ProtocoloServer::leer_arma(int jugador)
{
    int tipo_arma = recibir_byte();
    Accion *accion;
    switch (tipo_arma)
    {
    case 1:
        accion = new AtaqueAereo(jugador);
        break;
    default:
        // Manejo de un movimiento no válido, si es necesario
        break;
    }
    return accion;
}

Accion *ProtocoloServer::leer_accion(int jugador)
{
    int tipo_accion = recibir_tipo_accion();
    Accion *accion;
    switch (tipo_accion)
    {
    case MOVIMIENTO:
        accion = leer_movimiento(jugador);
        break;
    case SELECCION_ARMA:
        accion = leer_arma(jugador);
        break;
    case TELEDIRIGIDO:
        //
        break;
    default:
        break;
    }
    return accion;

    // Agrega el movimiento como una cadena a la cola
}

int ProtocoloServer::recibir_byte()
{
    try
    {
        bool was_closed = false;
        uint8_t buffer;
        socket.recvall(&buffer, RECIBIR_BYTE, &was_closed);
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

int ProtocoloServer::recibir_tipo_accion()
{
    bool was_closed = false;
    uint8_t buffer;
    try
    {

        socket.recvall(&buffer, RECIBIR_BYTE, &was_closed);
        if (was_closed)
        {
            en_conexion = false;
        }
        if (buffer == ACCION_MOVIMIENTO)
        {
            return MOVIMIENTO;
        }
        else
        {
            return SELECCION_ARMA;
        }
    }
    catch (const std::exception &err)
    {
        return -1;
    }
}

void ProtocoloServer::enviar_jugador(int id, int x, int y, int direccion, int angulo)
{
    enviar_int(id);
    enviar_int(x);
    enviar_int(y);
    enviar_int(direccion);
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
