#include "partida.h"
#include <iostream>
#include <chrono>
#include <cmath>

Partida::Partida() : en_ejecucion(false), monitor_jugadores(new MonitorJugadores()), cola(new Queue<Accion *>(100)), escenario(200, 200, monitor_jugadores)
{
    escenario.colocar_viga(50, 70, 0, 0);
    escenario.colocar_viga(70, 100, 1, 0);
    escenario.colocar_viga(150, 80, 1, 0);
    escenario.colocar_viga(80, 110, 0, 0);
    escenario.colocar_viga(90, 140, 1, 0);
    escenario.colocar_viga(100, 180, 0, 0);
    escenario.colocar_viga(115, 200, 1, 0);
    escenario.colocar_viga(220, 195, 0, 0);
   
}

void Partida::agregar_jugador(Jugador *jugador)
{
    int jugador_id = monitor_jugadores->agregar_jugador(jugador);
    jugador->jugar(cola, jugador_id);
    escenario.agregar_gusano(jugador_id);
    if (!en_ejecucion)
    {
        en_ejecucion = true;
        monitor_jugadores->cambiar_turno();
        start();
    }
}

void Partida::detener_partida()
{
    en_ejecucion = false;
}

void Partida::run()
{
    int id_desconectado = -1;
    int id_turno = 1;
    std::chrono::time_point<std::chrono::steady_clock> ultimo_cambio_de_turno = std::chrono::steady_clock::now();
    int ultimo_numero_notificado = 0; // Comenzar en 31 para iniciar con 30 segundos

    while (en_ejecucion)
    {
        auto ahora = std::chrono::steady_clock::now();
        int segundos_transcurridos = std::chrono::duration_cast<std::chrono::seconds>(ahora - ultimo_cambio_de_turno).count();

        Accion *accion;
        if (cola->try_pop(accion))
        {
            id_desconectado = accion->ejecutar_accion(escenario);
            // id_desconectado = accion->avisar_desconectado();
            delete accion;
        }

        if (segundos_transcurridos >= DURACION_TURNO or id_turno == id_desconectado)
        {
            // Realizar el cambio de turno
            id_turno = monitor_jugadores->cambiar_turno();
            ultimo_cambio_de_turno = ahora; // Reiniciar el temporizador
            ultimo_numero_notificado = 0;
            segundos_transcurridos = 0; // Reiniciar el último número notificado
            monitor_jugadores->limpiar_desconectados();
            id_desconectado = -1;
        }

        // Contar en reversa desde 30 hasta 0
        int segundo_actual = round(DURACION_TURNO - segundos_transcurridos);

        // Verificar si es un nuevo número antes de notificar a los jugadores
        if (segundo_actual != ultimo_numero_notificado)
        {
            monitor_jugadores->mandar_segundos(segundo_actual);
            ultimo_numero_notificado = segundo_actual;
        }

        // Sleep de 3 milisegundos para evitar un busy wait
        // std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
    delete monitor_jugadores;
    delete cola;
}
