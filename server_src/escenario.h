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
#include <map>
#include <cmath>

const float_t FRAME_RATE = 4.0f / 60.0f;

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

    void agregar_gusano(int jugador_id);

    void colocar_viga(int x, int y, bool tipo, int inclinacion);

    void avisar_desconexion(int jugador);

    void mover_gusano_derecha(int gusano, int jugador);

    void mover_gusano_izquierda(int gusano, int jugador);

    void mover_gusano_arriba_adelante(int gusano, int jugador);

    void mover_gusano_arriba_atras(int gusano, int jugador);

    void equipar_arma(int gusano, int jugador, int arma);

    void usar_arma(int gusano, int jugador, Arma *arma);

    ~Escenario();

private:
    std::uint16_t x_size;
    std::uint16_t y_size;
    MonitorJugadores *monitor;
    Mundo *mundo;
    std::vector<PosicionViga> vigas;
    std::map<int, std::map<int, Gusano *>> gusanos;
    std::vector<Objeto *> *objetos;
    std::vector<std::pair<int, int>> spawns;
    int cantidad_jugadores = 0;

    void mandar_paquete();
    bool en_movimiento();
    void respawnear_gusano(int jugador_id);
};
#endif