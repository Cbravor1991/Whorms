#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <netinet/in.h>
#include <cstring>
#include <mutex>
#include <string>
#include <vector>
#include "../common_src/common_socket.h"
#include <atomic>

struct Mensaje
{
    std::string cadena = "";
    // cppcheck-suppress unusedStructMember
    bool tipo_mensaje = false;
};

const uint8_t CAMBIO_TURNO = 0x00;
const uint8_t SEGUNDOS = 0x01;
const uint8_t PAQUETE = 0x03;
const uint8_t ESCENARIO = 0x04;
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

public:
    explicit ProtocoloServer(Socket socket);

    int leer_movimiento();

    void enviar_id(int jugador_id);

    void enviar_informacion_escenario(int x, int y, int cantidad_vigas);

    void enviar_cantidad_jugadores(int cantidad);

    void enviar_turno(int jugador_id);

    void enviar_segundos(int segundo);

    void enviar_jugador(int id, int x, int y, int angulo);

    void enviar_viga(bool tipo, int x, int y, int angulo);

    bool check_en_conexion();

    void desconectar();
};

#endif
