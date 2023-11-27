#ifndef PARTIDA_H_
#define PARTIDA_H_

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "../common_src/thread.h"
#include "../common_src/queue.h"
#include "escenario.h"
#include "accion/accion.h"
#include "server_jugador.h"
#include "monitor_jugador.h"

const int DURACION_TURNO = 30;

class Partida : public Thread
{
public:
    Partida(Escenario &escenario); // Constructor

    // Función para detener la partida
    void detener_partida();

    void agregar_jugador(Jugador *jugador);

    void run() override;

private:
    // Variables de control de la partida

    int id_turno = 1;
    bool en_ejecucion;
    MonitorJugadores *monitor_jugadores;
    Queue<Accion *> *cola;
    Escenario &escenario;
};

#endif