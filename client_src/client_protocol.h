

#ifndef CLIENT_PROTOCOL_H_
#define CLIENT_PROTOCOL_H_

#include <string>
#include <map>
#include <vector>
#include <tuple>
#include "../common_src/common_socket.h"

#include <cstring>

class StateGame;
class JugadorDTO;
class ObjetoDTO;
class VigaDTO;
class EscenarioDTO;
class PaqueteDTO;

struct Viga
{
    bool tipo;
    int x;
    int y;
};

const uint8_t ENVIAR_ARMA = 0x01;
const uint8_t ENVIAR_MOVIMIENTO = 0x00;
const uint8_t ENVIAR_USO_ARMA = 0x05;
const std::int8_t RECIBIR_SEGUNDO = 0x01;
const std::int8_t RECIBIR_TURNO = 0x00;
const std::int8_t RECIBIR_PAQUETE = 0x03;
const std::int8_t RECIBIR_ESCENARIO = 0x04;
const std::int8_t RECIBIR_ARMA = 0x05;
const std::int8_t RECIBIR_VIENTO = 0x06;
const std::int8_t RECIBIR_CANTIDAD_JUGADORES = 0x10;
const std::int8_t RECIBIR_JUGAR = 0x11;
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

    uint8_t recibir_byte();

    int recibir_int();

    int recibir_int_grande();

    int recibir_mensaje();

    StateGame *recibir_turno(int jugador_id);

    StateGame *recibir_segundo();

    StateGame *recibir_paquete();

    StateGame *recibir_escenario();

    JugadorDTO recibir_jugador();

    ObjetoDTO recibir_objeto();

    VigaDTO recibir_viga();

    StateGame *recibir_viento();

    StateGame *recibir_arma();

    int traducir_tipo_mensaje(const uint8_t &buffer);

public:
    ProtocoloCliente(const std::string &hostname,
                     const std::string &servname);

    int recibir_id_jugador();

    void enviar_movimiento(int tipo);

    void enviar_arma(int tipo);

    void enviar_disparo(int angulo, bool direccion);

    void enviar_disparo_timeado(int direccion, int timer);

    void enviar_disparo_potente(int angulo, int direccion, int potencia);

    void enviar_disparo_potente_timeado(int angulo, int direccion, int potencia, int timer);

    void enviar_posicion(int x, int y);

    void enviar_byte(const uint8_t &dato);

    void enviar_int(int entero);

    void enviar_int_grande(int entero);

    StateGame *procesar_mensaje(const int &id_jugador);

    bool check_en_conexion();

    void desconectar();

    std::vector<int> recibir_partidas();

    std::vector<int> recibir_escenarios();

    void enviar_partida(int partida);

    void enviar_escenario(int escenario);

    void enviar_modo(int modo);

    int recibir_cantidad_jugadores_en_espera();

    bool recibir_modo_partida();

    void enviar_comienzo_juego();

    ProtocoloCliente(const ProtocoloCliente &) = delete;
    ProtocoloCliente &operator=(const ProtocoloCliente &) = delete;
};

#endif //  CLIENT_PROTOCOL_H_
