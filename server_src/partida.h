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
#include "../../server_src/configuracion.h"

#define configuracion Configuracion::obtener_configuracion()

const int DURACION_TURNO = configuracion.getTiempoTurnoGusano();

class Partida : public Thread
{
public:
    Partida(ConfiguracionMapa mapa); // Constructor

    // Función para detener la partida
    void detener_partida();

    void agregar_jugador(Jugador *jugador);

    void run() override;

private:
    // Variables de control de la partida

    int tipo_fondo;
    int id_turno = 1;
    bool en_ejecucion;
    MonitorJugadores *monitor_jugadores;
    Queue<Accion *> *cola;
    Escenario escenario;
};

#endif