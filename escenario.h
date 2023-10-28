#ifndef ESCENARIO_H_
#define ESCENARIO_H_
#include <random>
#include <vector>
#include "monitor_jugador.h"
#include "objeto.h"
#include "gusano.h"
#include "bloque.h"
#include <map>

class Escenario
{
public:
    Escenario(std::uint16_t x_size, std::uint16_t y_size, MonitorJugadores *monitor);

    void procesar(const std::string &comando);

    void agregar_gusano(int jugador_id);

    void colocar_viga(int x, int y, bool tipo, int inclinacion);

    void avisar_desconexion(int jugador);

    ~Escenario();

private:
    std::uint16_t x_size;
    std::uint16_t y_size;
    MonitorJugadores *monitor;
    std::vector<std::vector<Objeto *>> map; // objeto puede ser bloque, gusano, arma o botiquin
    std::map<int, std::map<int, Gusano *>> gusanos;
    std::vector<std::pair<int, int>> spawns;
    int cantidad_jugadores = 0;

    void mover_gusano_derecha(int gusano, int jugador);

    void mover_gusano_izquierda(int gusano, int jugador);

    void mover_gusano_arriba_adelante(int gusano, int jugador);

    void mover_gusano_arriba_atras(int gusano, int jugador);

    void mover(int x, int y, int nuevo_x, int nuevo_y);

    bool mover_derecha(Objeto *objeto, int veces);

    bool mover_izquierda(Objeto *objeto, int veces);

    bool mover_arriba(Objeto *objeto, int veces);

    // actualizar_jugadores();

    void gravedad(Objeto *objeto);
};
#endif