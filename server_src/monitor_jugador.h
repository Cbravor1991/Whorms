#ifndef MONITOR_JUGADOR_H
#define MONITOR_JUGADOR_H

#include <mutex>
#include <string>
#include <vector>
#include <map>
#include <condition_variable>
#include "server_jugador.h"
#include "turno.h"
#include "data/cambio_turno.h"
#include "data/posicion_jugador.h"
#include "data/posicion_viga.h"

struct Viga
{
    bool tipo;
    int x;
    int y;
};

class Jugador;

class MonitorJugadores
{
public:
    MonitorJugadores() {}

    int cambiar_turno();

    void cargar_mapa(Jugador *jugador);

    void notificar_segundos(int segundos);

    void actualizar_jugadores_cantidad(int cantidad);

    void actualizar_jugadores_jugador(int id, int x, int y);

    int agregar_jugador(Jugador *jugador);

    void limpiar_desconectados();

    void avisar_desconexion();

    void agregar_viga(bool tipo, int x, int y);

    ~MonitorJugadores();

private:
    std::mutex mutex_;
    std::atomic<int> cantidad_jugadores = 0;
    std::map<int, Jugador *> jugadores;
    std::vector<Jugador *> jugadores_desconectados;
    std::vector<Viga> vigas;
    Turno turno;

    int encontrar_siguiente_id_disponible() const;

    void actualizar_cantidad_jugadores(int cantidad);

    void eliminar_jugadores_desconectados();
};

#endif // MONITORJUGADOR_H
