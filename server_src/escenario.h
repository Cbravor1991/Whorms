#ifndef ESCENARIO_H_
#define ESCENARIO_H_
#include <random>
#include <vector>
#include <sstream>
#include <ctime>
#include "objeto/gusano.h"
#include "objeto/mundo.h"
#include "objeto/arma.h"
#include "objeto/provision.h"
#include "data/posicion_viga.h"
#include "data/posicion_lanzable.h"
#include "data/posicion_jugador.h"
#include "turno_gusano.h"
#include <map>
#include <cmath>
#include <random>
#include <cstdlib>
#include "../../server_src/configuracion_mapa.h"
#include "data/posicion_spawn.h"

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
    Escenario(ConfiguracionMapa mapa, MonitorJugadores *monitor);

    int cambiar_turno(int id);

    void agregar_jugadores();

    void agregar_jugador(int jugador_id);

    void agregar_spawns(std::vector<PosicionSpawn> spawns_editor);

    void colocar_viga(int x, int y, bool tipo, int inclinacion);

    void colocar_provision();

    void avisar_desconexion(int jugador);

    void mover_gusano_derecha(int jugador);

    void mover_gusano_izquierda(int jugador);

    void mover_gusano_arriba_adelante(int jugador);

    void mover_gusano_arriba_atras(int jugador);

    void equipar_arma(int jugador, int arma);

    void usar_arma(int jugador, Arma *arma);

    void explotar_bombas_regresivas(int jugador);

    ~Escenario();

private:
    std::uint16_t x_size = 200;
    std::uint16_t y_size = 200;
    MonitorJugadores *monitor;
    Mundo *mundo;
    std::vector<PosicionViga> vigas;
    std::map<int, TurnoGusano> gusanos;
    std::vector<std::pair<int, int>> spawns;

    int cantidad_gusanos_por_jugador = 0;

    void movimiento(Gusano *gusano, int jugador);
    Gusano *recibir_gusano(int id);
    Gusano *agregar_gusano(int jugador_id, int gusano_id);
    void mandar_paquete();
    bool en_movimiento();
    void respawnear_gusano(int jugador_id);
};
#endif