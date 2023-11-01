#ifndef ESCENARIO_H_
#define ESCENARIO_H_
#include <random>
#include <vector>
#include <sstream>
#include "objeto.h"
#include "gusano.h"
#include "bloque.h"
#include "data/posicion_viga.h"
#include "data/posicion_jugador.h"
#include <map>

struct Viga
{
    bool tipo;
    int x;
    int y;
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

    ~Escenario();

private:
    std::uint16_t x_size;
    std::uint16_t y_size;
    MonitorJugadores *monitor;
    std::vector<std::vector<Objeto *>> map;
    std::vector<Viga> vigas;
    std::map<int, std::map<int, Gusano *>> gusanos;
    std::vector<std::pair<int, int>> spawns;
    int cantidad_jugadores = 0;

    std::vector<PosicionJugador> crear_paquete();

    void mover(int x, int y, int nuevo_x, int nuevo_y);

    bool mover_derecha(Objeto *objeto, int veces);

    bool mover_izquierda(Objeto *objeto, int veces);

    bool mover_arriba(Objeto *objeto, int veces);

    // actualizar_jugadores();

    void gravedad(Objeto *objeto);
};
#endif