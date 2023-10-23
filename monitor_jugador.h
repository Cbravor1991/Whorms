#ifndef MONITOR_JUGADOR_H
#define MONITOR_JUGADOR_H

#include <mutex>
#include <string>
#include <vector>
#include <condition_variable>
#include "server_jugador.h"
#include "server_protocol.h"

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

    void actualizar_jugadores_cantidad(int cantidad);

    void actualizar_jugadores_jugador(int id, int x, int y);

    void actualizar_jugadores_viga(bool tipo, int x, int y);

    void agregar_jugador(Jugador *jugador);

    void limpiar_desconectados();

    void avisar_desconexion();

    void agregar_viga(bool tipo, int x, int y);

    ~MonitorJugadores();

private:
    std::mutex mutex_;
    std::atomic<int> cantidad_jugadores = 0;
    std::vector<Jugador *> jugadores;
    std::vector<Jugador *> jugadores_desconectados;
    std::vector<Viga> vigas;

    void cargar_mapa(Jugador *jugador);

    void actualizar_cantidad_jugadores(int cantidad);

    void eliminar_jugadores_desconectados();
};

#endif // MONITORJUGADOR_H
