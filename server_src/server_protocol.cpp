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
#include "accion/uso_arma.h"
#include "accion/cambio_arma.h"
#include "objeto/ataque_aereo.h"
#include "objeto/teletransportacion.h"
#include "objeto/banana.h"
#include "objeto/bate.h"

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

void ProtocoloServer::enviar_int_grande(int entero)
{
    // Dividir el int en dos bytes
    uint8_t byte_msb = static_cast<uint8_t>((entero >> 8) & 0xFF); // byte más significativo
    uint8_t byte_lsb = static_cast<uint8_t>(entero & 0xFF);        // byte menos significativo

    // Enviar los dos bytes a través del socket
    enviar_byte(byte_msb);
    enviar_byte(byte_lsb);
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

void ProtocoloServer::enviar_turno(int turno_id, int id_gusano)
{
    tipo_arma = 0;
    enviar_byte(CAMBIO_TURNO);
    enviar_int(turno_id);
    enviar_int(id_gusano);
}

void ProtocoloServer::enviar_arma(int id, int id_gusano, int arma, int ammo)
{
    enviar_byte(ARMA);
    enviar_int(id);
    enviar_int(id_gusano);
    enviar_int(arma);
    enviar_int(ammo);
}

void ProtocoloServer::enviar_segundos(int segundos)
{
    enviar_byte(SEGUNDOS);
    enviar_int(segundos);
}

Accion *ProtocoloServer::leer_movimiento(int jugador)
{
    int tipo_movimiento = recibir_int();
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
        accion = new CambioArma(jugador, -1);
        break;
    }
    return accion;
}

Accion *ProtocoloServer::leer_arma(int jugador)
{
    tipo_arma = recibir_int();
    Accion *accion;
    accion = new CambioArma(jugador, tipo_arma);
    return accion;
}

Accion *ProtocoloServer::leer_uso_arma(int jugador)
{
    int x, y, angulo;
    bool direccion;
    Arma *arma = nullptr;
    switch (tipo_arma)
    {
    case TELEPORT:
        x = recibir_int_grande();
        y = recibir_int_grande();
        arma = new Teletransportacion(x, y);
        break;
    case AIR_STRIKE:
        x = recibir_int_grande();
        y = recibir_int_grande();
        arma = new AtaqueAereo(x, y);
        break;
    case BAT:
        angulo = recibir_int();
        direccion = static_cast<bool>(recibir_int());
        arma = new Bate(direccion, angulo);
        break;
    case DYNAMITE:
        x = recibir_int_grande();
        y = recibir_int_grande();
        arma = new AtaqueAereo(x, y);
        break;
    case BAZOOKA:
        angulo = recibir_int();
        direccion = static_cast<bool>(recibir_int());
        arma = new Banana(direccion, angulo);
        break;
    case MORTAR:
        angulo = recibir_int();
        direccion = static_cast<bool>(recibir_int());
        arma = new Banana(direccion, angulo);
        break;
    case GREEN_GRENADE:
        angulo = recibir_int();
        direccion = static_cast<bool>(recibir_int());
        arma = new Banana(direccion, angulo);
        break;
    case CLUSTER_GRENADE:
        angulo = recibir_int();
        direccion = static_cast<bool>(recibir_int());
        arma = new Banana(direccion, angulo);
        break;
    case HOLY_GRENADE:
        angulo = recibir_int();
        direccion = static_cast<bool>(recibir_int());
        arma = new Banana(direccion, angulo);
        break;
    case BANANA:
        angulo = recibir_int();
        direccion = static_cast<bool>(recibir_int());
        arma = new Banana(direccion, angulo);
        break;
    default:
        x = recibir_int_grande();
        y = recibir_int_grande();
        arma = new Teletransportacion(x, y);
        break;
    }
    Accion *accion;
    accion = new UsoArma(jugador, arma);
    tipo_arma = 0;
    return accion;
}

Accion *ProtocoloServer::leer_accion(int jugador)
{
    int tipo_accion = recibir_tipo_accion();
    Accion *accion;
    switch (tipo_accion)
    {
    case MOVIMIENTO:
        // delete accion;
        accion = leer_movimiento(jugador);
        break;
    case SELECCION_ARMA:
        // delete accion;
        accion = leer_arma(jugador);
        break;
    case USO_ARMA:
        // delete accion;
        accion = leer_uso_arma(jugador);
        break;
    default:
        accion = new CambioArma(jugador, -1);
        break;
    }
    return accion;
}

uint8_t ProtocoloServer::recibir_byte()
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
        return buffer;
    }
    catch (const std::exception &err)
    {
        return -1;
    }
}

int ProtocoloServer::recibir_int()
{
    uint8_t byte = recibir_byte();
    int entero = static_cast<int>(byte);
    return entero;
}

int ProtocoloServer::recibir_int_grande()
{
    uint8_t byte_msb = recibir_byte();
    uint8_t byte_lsb = recibir_byte();
    int entero = (static_cast<int>(byte_msb) << 8) | static_cast<int>(byte_lsb);
    return entero;
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
        else if (buffer == ACCION_ARMA)
        {
            return SELECCION_ARMA;
        }
        else if (buffer == ACCION_USO_ARMA)
        {
            return USO_ARMA;
        }
        else
        {
            return 100;
        }
    }
    catch (const std::exception &err)
    {
        return -1;
    }
}

void ProtocoloServer::enviar_jugador(int id, int id_gusano, int x, int y, int direccion, int angulo, int vida, bool en_movimiento)
{
    enviar_int(id);
    enviar_int(id_gusano);
    enviar_int_grande(x);
    enviar_int_grande(y);
    enviar_int(direccion);
    enviar_int(angulo);
    enviar_int(vida);
    enviar_int(en_movimiento ? 1 : 0);
}

void ProtocoloServer::enviar_lanzable(int tipo, int x, int y, int direccion, int angulo, bool explosion)
{
    enviar_int(tipo);
    enviar_int_grande(x);
    enviar_int_grande(y);
    enviar_int(direccion);
    enviar_int(angulo);
    enviar_int(explosion ? 1 : 0);
}

void ProtocoloServer::enviar_viga(bool tipo, int x, int y, int angulo)
{
    enviar_int(static_cast<int>(tipo));
    enviar_int_grande(x);
    enviar_int_grande(y);
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
    enviar_byte(PAQUETE_JUGADORES);
    enviar_int(cantidad);
}

void ProtocoloServer::enviar_cantidad_objetos(int cantidad)
{
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

 void ProtocoloServer::enviar_partidas (std::vector<int> partidas_ids){

        enviar_int(partidas_ids.size());
        for (const auto& par : partidas_ids) {
            enviar_int(par);
    }

}


 void ProtocoloServer::enviar_escenarios (std::vector<int> escenarios_ids){
        enviar_int(escenarios_ids.size());
        for (const auto& par : escenarios_ids) {
            enviar_int(par);
    }

}


    bool ProtocoloServer::recibir_modo(){
        bool modo = static_cast<bool>(recibir_int());
        return modo;
        }

    int ProtocoloServer::recibir_escenario(){
        return recibir_int();
    }

    int ProtocoloServer::recibir_partida(){
            return recibir_int();
    }
