#ifndef MONITOR_JUGADOR_H
#define MONITOR_JUGADOR_H

#include <mutex>
#include <string>
#include <vector>
#include <map>
#include <condition_variable>
#include "server_jugador.h"
#include "turno.h"
#include "data/cambio_turno_DTO.h"
#include "data/paquete_gusanos_DTO.h"
#include "data/paquete_objetos_DTO.h"
#include "data/escenario_DTO.h"
#include "data/segundo_DTO.h"
#include "data/arma_DTO.h"

class Jugador;

class MonitorJugadores
{
public:
    MonitorJugadores() {}

    int cambiar_turno();

    void mandar_paquete_gusanos(std::vector<PosicionJugador> jugadores);

    void mandar_paquete_objetos(std::vector<PosicionLanzable> objetos);

    void mandar_escenario(int x, int y, std::vector<PosicionViga> vigas, int id);

    void mandar_segundos(int segundos);

    void mandar_arma(int jugador, int arma, int ammo);

    void actualizar_jugadores_cantidad(int cantidad);

    void actualizar_jugadores_jugador(int id, int x, int y);

    int agregar_jugador(Jugador *jugador);

    void limpiar_desconectados();

    void avisar_desconexion();

    ~MonitorJugadores();

private:
    std::mutex mutex_;
    std::atomic<int> cantidad_jugadores = 0;
    std::map<int, Jugador *> jugadores;
    std::vector<Jugador *> jugadores_desconectados;
    Turno turno;

    int encontrar_siguiente_id_disponible() const;

    void actualizar_cantidad_jugadores(int cantidad);

    void eliminar_jugadores_desconectados();
};

#endif // MONITORJUGADOR_H
