#include "partida.h"
#include <iostream>
#include <chrono>
#include <cmath>

Partida::Partida() : en_ejecucion(false), monitor_jugadores(new MonitorJugadores()), cola(new Queue<Accion *>(100)), escenario(200, 200, monitor_jugadores)
{
    escenario.colocar_viga(50, 70, 0, -40);
    escenario.colocar_viga(70, 100, 1, 0);
    escenario.colocar_viga(150, 80, 1, 40);
    escenario.colocar_viga(220, 110, 0, 0);
    escenario.colocar_viga(90, 140, 1, 0);
}

void Partida::agregar_jugador(Jugador *jugador)
{
    int jugador_id = monitor_jugadores->agregar_jugador(jugador);
    jugador->jugar(cola, jugador_id);
    escenario.agregar_jugador(jugador_id);
    if (!en_ejecucion)
    {
        en_ejecucion = true;
        id_turno = monitor_jugadores->cambiar_turno();
        start();
    }
    if (VACIO == monitor_jugadores->recibir_turno())
    {
        id_turno = monitor_jugadores->cambiar_turno();
    }
}

void Partida::detener_partida()
{
    en_ejecucion = false;
}

void Partida::run()
{
    std::chrono::time_point<std::chrono::steady_clock> ultimo_cambio_de_turno = std::chrono::steady_clock::now();
    int ultimo_numero_notificado = 0; // Comenzar en 31 para iniciar con 30 segundos

    while (en_ejecucion)
    {
        auto ahora = std::chrono::steady_clock::now();
        int segundos_transcurridos = std::chrono::duration_cast<std::chrono::seconds>(ahora - ultimo_cambio_de_turno).count();

        Accion *accion = nullptr;
        if (cola->try_pop(accion))
        {
            if (accion != nullptr)
            {
                accion->ejecutar_accion(escenario);
                delete accion;
            }
        }

        if (id_turno != monitor_jugadores->recibir_turno())
        {
            id_turno = monitor_jugadores->recibir_turno();
            ultimo_cambio_de_turno = ahora; // Reiniciar el temporizador
            ultimo_numero_notificado = 0;
            segundos_transcurridos = 0; // Reiniciar el último número notificado
        }

        if (segundos_transcurridos >= DURACION_TURNO)
        {
            // Realizar el cambio de turno
            id_turno = escenario.cambiar_turno(id_turno);
            ultimo_cambio_de_turno = ahora; // Reiniciar el temporizador
            ultimo_numero_notificado = 0;
            segundos_transcurridos = 0; // Reiniciar el último número notificado
            monitor_jugadores->limpiar_desconectados();
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
        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
    delete monitor_jugadores;

    delete cola;
}
