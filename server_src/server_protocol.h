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

const int NO_WEAPON = 0;
const int AIR_STRIKE = 1;
const int TELEPORT = 2;
const int BAT = 3;
const int DYNAMITE = 4;
const int BAZOOKA = 5;
const int MORTAR = 6;
const int GREEN_GRENADE = 7;
const int CLUSTER_GRENADE = 8;
const int HOLY_GRENADE = 9;
const int BANANA = 10;

const int MOVIMIENTO = 0;
const int SELECCION_ARMA = 1;
const int USO_ARMA = 5;

const uint8_t ACCION_MOVIMIENTO = 0x00;
const uint8_t ACCION_ARMA = 0x01;
const uint8_t ACCION_USO_ARMA = 0x05;

const int MOVIMIENTO_IZQUIERDA = 1;
const int MOVIMIENTO_DERECHA = 2;
const int MOVIMIENTO_ARRIBA_ADELANTE = 3;
const int MOVIMIENTO_ARRIBA_ATRAS = 4;

const uint8_t CAMBIO_TURNO = 0x00;
const uint8_t SEGUNDOS = 0x01;
const uint8_t PAQUETE_JUGADORES = 0x03;
const uint8_t PAQUETE_OBJETOS = 0x07;
const uint8_t ESCENARIO = 0x04;
const uint8_t ARMA = 0x05;
const uint8_t PARTIDAS = 0x10;


const int BYTES_CANT_JUGADORES = 2;
const int RECIBIR_BYTE = 1;

class ProtocoloServer
{
private:
    int tipo_arma;
    Socket socket;
    std::atomic<bool> en_conexion{true};

    int leer_longitud();

    void enviar_int(int entero);

    void enviar_byte(const uint8_t &dato);

    void enviar_int_grande(int entero);

    Accion *leer_movimiento(int jugador);

    Accion *leer_arma(int jugador);

    Accion *leer_uso_arma(int jugador);

    uint8_t recibir_byte();

    int recibir_int();

    int recibir_int_grande();

    int recibir_tipo_accion();

public:
    explicit ProtocoloServer(Socket socket);

    Accion *leer_accion(int jugador);

    void enviar_id(int jugador_id);

    void enviar_informacion_escenario(int x, int y, int cantidad_vigas);

    void enviar_cantidad_jugadores(int cantidad);

    void enviar_cantidad_objetos(int cantidad);

    void enviar_turno(int jugador_id, int id_gusano);

    void enviar_segundos(int segundo);

    void enviar_arma(int id, int id_gusano, int arma, int ammo);

    void enviar_jugador(int id, int id_gusano, int x, int y, int direccion, int angulo, int vida, bool en_movimiento);

    void enviar_lanzable(int tipo, int x, int y, int direccion, int angulo, bool explosion);

    void enviar_viga(bool tipo, int x, int y, int angulo);

    bool check_en_conexion();

    void desconectar();

    void enviar_partidas (std::vector<int> partidas_ids);

    void enviar_escenarios (std::vector<int> escenarios_ids);

    
    bool recibir_modo();

    int recibir_escenario();

    int recibir_partida();




   
     };

#endif
