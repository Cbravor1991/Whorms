#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <netinet/in.h>
#include <cstring>
#include <mutex>
#include <string>
#include <vector>
#include "../common_src/common_socket.h"
#include <atomic>

class Accion;

struct Mensaje
{
    std::string cadena = "";
    // cppcheck-suppress unusedStructMember
    bool tipo_mensaje = false;
};

const int MOVIMIENTO = 0;     
const int SELECCION_ARMA = 1;
const int TELEDIRIGIDO = 5;
const uint8_t ACCION_MOVIMIENTO = 0x00;
const uint8_t ACCION_ARMA = 0x01;
const uint8_t ACCION_TELEDIRIGIDO = 0x05;
const int MOVIMIENTO_IZQUIERDA = 1;
const int MOVIMIENTO_DERECHA = 2;
const int MOVIMIENTO_ARRIBA_ADELANTE = 3;
const int MOVIMIENTO_ARRIBA_ATRAS = 4;
const uint8_t CAMBIO_TURNO = 0x00;
const uint8_t SEGUNDOS = 0x01;
const uint8_t PAQUETE = 0x03;
const uint8_t ESCENARIO = 0x04;
const uint8_t ARMA = 0x05;
const int BYTES_CANT_JUGADORES = 2;
const int RECIBIR_BYTE = 1;

class ProtocoloServer
{
private:
    Socket socket;
    std::atomic<bool> en_conexion{true};

    int leer_longitud();

    void enviar_int(int entero);

    void enviar_byte(const uint8_t &dato);

    Accion* leer_movimiento(int jugador);

    Accion* leer_arma(int jugador);

    int recibir_byte();
   
    int recibir_tipo_accion();


public:
    explicit ProtocoloServer(Socket socket);

    Accion* leer_accion(int jugador);

    void enviar_id(int jugador_id);

    void enviar_informacion_escenario(int x, int y, int cantidad_vigas);

    void enviar_cantidad_jugadores(int cantidad);

    void enviar_turno(int jugador_id);

    void enviar_segundos(int segundo);

    void enviar_arma(int id, int arma);

    void enviar_jugador(int id, int x, int y, int direccion, int angulo);

    void enviar_viga(bool tipo, int x, int y, int angulo);

    bool check_en_conexion();

    void desconectar();
};

#endif
