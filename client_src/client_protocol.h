

#ifndef CLIENT_PROTOCOL_H_
#define CLIENT_PROTOCOL_H_

#include <string>
#include <map>
#include <vector>
#include <tuple>
#include "../common_src/common_socket.h"
#include "DTO/common_state_game.h"
#include "DTO/common_vigaDTO.h"
#include "DTO/common_jugadorDTO.h"
#include "DTO/common_paqueteDTO.h"
#include "DTO/common_escenarioDTO.h"
#include "DTO/common_turnoDTO.h"
#include "DTO/common_segundosDTO.h"
#include <cstring>

const int TIPO_TURNO = 0;
const int TIPO_SEGUNDO = 1;
const int TIPO_PAQUETE = 2;
const int TIPO_ESCENARIO = 3;

struct Viga
{
    bool tipo;
    int x;
    int y;
};

const std::int8_t RECIBIR_SEGUNDO = 0x01;
const std::int8_t RECIBIR_TURNO = 0x00;
const std::int8_t RECIBIR_PAQUETE = 0x03;
const std::int8_t RECIBIR_ESCENARIO = 0x04;
const int RECIBO_BYTE = 1;
const int BYTES_ID = 2;
const int BYTES_X = 2;
const int BYTES_Y = 2;
const int BYTES_TIPO = 1;

class ProtocoloCliente
{
private:
    Socket socket;
    bool en_conexion = true;

    int recibir_byte();

    int recibir_mensaje();

    StateGame *recibir_turno(int jugador_id);

    StateGame *recibir_segundo();

    StateGame *recibir_paquete();

    StateGame *recibir_escenario();

    JugadorDTO recibir_jugador();

    VigaDTO recibir_viga();

    int traducir_tipo_mensaje(const uint8_t &buffer);

public:
    ProtocoloCliente(const std::string &hostname,
                     const std::string &servname);

    int recibir_id_jugador();

    void enviar_mensaje(const std::string &mensaje);

    StateGame *procesar_mensaje(const int &id_jugador);

    bool check_en_conexion();

    void desconectar();

    ProtocoloCliente(const ProtocoloCliente &) = delete;
    ProtocoloCliente &operator=(const ProtocoloCliente &) = delete;
};

#endif //  CLIENT_PROTOCOL_H_
