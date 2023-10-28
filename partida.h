#ifndef PARTIDA_H_
#define PARTIDA_H_

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "thread.h"
#include "queue.h"
#include "escenario.h"

const int DURACION_TURNO = 30;

class Partida : public Thread
{
public:
    Partida(); // Constructor

    // Función para detener la partida
    void detener_partida();

    void agregar_jugador(Jugador *jugador);

    void run() override;

private:
    // Variables de control de la partida

    bool en_ejecucion;
    MonitorJugadores *monitor_jugadores;
    Queue<std::string> *cola;
    Escenario escenario;
};

#endif