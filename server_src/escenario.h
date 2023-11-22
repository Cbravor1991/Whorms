#ifndef ESCENARIO_H_
#define ESCENARIO_H_
#include <random>
#include <vector>
#include <sstream>
#include "objeto/gusano.h"
#include "objeto/mundo.h"
#include "objeto/arma.h"
#include "data/posicion_viga.h"
#include "data/posicion_lanzable.h"
#include "data/posicion_jugador.h"
#include "turno_gusano.h"
#include <map>
#include <cmath>

const float_t FRAME_RATE = 4.0f / 35.0f;
const int VELOCITY_ITERATION = 6;
const int POSITION_ITERATION = 2;

struct Viga
{
    bool tipo;
    int x;
    int y;
    int angulo;
};

class MonitorJugadores;

class Escenario
{
public:
    Escenario(std::uint16_t x_size, std::uint16_t y_size, MonitorJugadores *monitor);

    int cambiar_turno(int id);

    void agregar_jugador(int jugador_id);

    void colocar_viga(int x, int y, bool tipo, int inclinacion);

    void avisar_desconexion(int jugador);

    void mover_gusano_derecha(int jugador);

    void mover_gusano_izquierda(int jugador);

    void mover_gusano_arriba_adelante(int jugador);

    void mover_gusano_arriba_atras(int jugador);

    void equipar_arma(int jugador, int arma);

    void usar_arma(int jugador, Arma *arma);

    ~Escenario();

private:
    std::uint16_t x_size;
    std::uint16_t y_size;
    MonitorJugadores *monitor;
    Mundo *mundo;
    std::vector<PosicionViga> vigas;
    std::map<int, TurnoGusano> gusanos;
    std::vector<Objeto *> *objetos;
    std::vector<std::pair<int, int>> spawns;
    int cantidad_jugadores = 0;

    Gusano *agregar_gusano(int jugador_id, int gusano_id);
    void mandar_paquete();
    bool en_movimiento();
    void respawnear_gusano(int jugador_id);
};
#endif