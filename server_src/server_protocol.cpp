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
#include "objeto/mortero.h"
#include "objeto/bazooka.h"
#include "objeto/dinamita.h"
#include "objeto/granada_santa.h"
#include "objeto/granada_roja.h"
#include "objeto/granada_verde.h"

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

void ProtocoloServer::enviar_ganador(int id_ganador)
{
    enviar_byte(GANADOR);
    enviar_int(id_ganador);
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
    int x, y, angulo, timer, potencia;
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
        // x = recibir_int_grande();
        // y = recibir_int_grande();
        direccion = static_cast<bool>(recibir_int());
        timer = recibir_int(); //
        arma = new Dinamita(direccion, timer);
        break;
    case BAZOOKA:
        angulo = recibir_int();
        direccion = static_cast<bool>(recibir_int());
        potencia = recibir_int();
        // arma = new Banana(direccion, angulo);
        arma = new Bazooka(direccion, angulo, potencia);
        break;
    case MORTAR:
        angulo = recibir_int();
        direccion = static_cast<bool>(recibir_int());
        potencia = recibir_int();
        arma = new Mortero(direccion, angulo, potencia);
        break;
    case GREEN_GRENADE:
        angulo = recibir_int();
        direccion = static_cast<bool>(recibir_int());
        potencia = recibir_int();
        timer = recibir_int();
        arma = new GranadaVerde(direccion, angulo, timer, potencia);
        break;
    case CLUSTER_GRENADE:
        angulo = recibir_int();
        direccion = static_cast<bool>(recibir_int());
        potencia = recibir_int();
        timer = recibir_int();
        arma = new GranadaRoja(direccion, angulo, timer, potencia);
        break;
    case HOLY_GRENADE:
        angulo = recibir_int();
        direccion = static_cast<bool>(recibir_int());
        potencia = recibir_int();
        timer = recibir_int();
        arma = new GranadaSanta(direccion, angulo, timer, potencia);
        break;
    case BANANA:
        angulo = recibir_int();
        direccion = static_cast<bool>(recibir_int());
        potencia = recibir_int();
        timer = recibir_int();
        arma = new Banana(direccion, angulo, timer, potencia);
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
    enviar_int_grande(angulo);
    enviar_int(explosion ? 1 : 0);
}

void ProtocoloServer::enviar_viento(int velocidad, bool direccion)
{
    enviar_byte(VIENTO);
    enviar_int(velocidad);
    enviar_int(direccion ? 1 : 0);
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

void ProtocoloServer::enviar_partidas(std::vector<int> partidas_ids)
{

    enviar_int(partidas_ids.size());
    for (const auto &par : partidas_ids)
    {
        enviar_int(par);
    }
}

void ProtocoloServer::enviar_escenarios(std::vector<int> escenarios_ids)
{
    enviar_int(escenarios_ids.size());
    for (const auto &par : escenarios_ids)
    {
        enviar_int(par);
    }
}

void ProtocoloServer::enviar_partida_creada(int partida)
{
    enviar_int(partida);
}

int ProtocoloServer::recibir_modo()
{
   
    return recibir_int();
}

int ProtocoloServer::recibir_escenario()
{
    return recibir_int();
}

int ProtocoloServer::recibir_partida()
{
    return recibir_int();
}

bool ProtocoloServer::recibir_jugar()
{

    bool modo = static_cast<bool>(recibir_int());
    return modo;
}

void ProtocoloServer::enviar_cantidad_jugadores_en_espera(int cantidad_jugadores)
{

    enviar_byte(CANTIDAD_JUGADORES);
    enviar_int(cantidad_jugadores);
}

void ProtocoloServer::enviar_comienzo_juego()
{

    enviar_byte(COMIENZO_JUEGO);
}

uint16_t ProtocoloServer::recibir_tamanio_mensaje() {

    bool was_closed = false;
    int cant_bytes_recibidos = 2;
    uint16_t datosRecibidos = 0;
    socket.recvall(&datosRecibidos, cant_bytes_recibidos, &was_closed);
    if (was_closed) {
         en_conexion = false;
    }
    return ntohs(datosRecibidos);
}

std::string ProtocoloServer::recibir_mensaje_chat(const int& tamanioString) {

    bool was_closed = false;
    std::vector<char> buffer_mensaje(tamanioString);
    socket.recvall(buffer_mensaje.data(), tamanioString, &was_closed);
    if (was_closed) {
          en_conexion = false;
    }
    std::string mensaje(buffer_mensaje.begin(), buffer_mensaje.end());
    return mensaje;
}

std::string ProtocoloServer::recibir_nombre_mapa() {

 int longitud_string = static_cast<int>(recibir_tamanio_mensaje());
 std::string mensaje = recibir_mensaje_chat(longitud_string);

 return mensaje;
 }