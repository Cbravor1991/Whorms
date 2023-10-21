#ifndef MONITOR_JUGADOR_H
#define MONITOR_JUGADOR_H

#include <mutex>
#include <string>
#include <vector>
#include <condition_variable>
#include "server_jugador.h"
#include "server_protocol.h"

class Jugador;

class MonitorJugadores
{
public:
    MonitorJugadores() {}

    void agregar_mensaje(const std::string &mensaje);

    void agregar_jugador(Jugador *jugador);

    void limpiar_desconectados();

    void avisar_desconexion();

    ~MonitorJugadores();

private:
    std::mutex mutex_;
    std::atomic<int> cantidad_jugadores = 0;
    std::vector<Jugador *> jugadores;
    std::vector<Jugador *> jugadores_desconectados;

    void actualizar_cantidad_jugadores(int cantidad);

    void actualizar_colas(const Mensaje& mensaje);

    void actualizar_jugadores(Mensaje mensaje);

    void eliminar_jugadores_desconectados();

    void print_mensaje(Mensaje mensaje);
};

#endif // MONITORJUGADOR_H
