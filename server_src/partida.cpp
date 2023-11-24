#include "partida.h"
#include <iostream>
#include <chrono>
#include <cmath>

Partida::Partida() : en_ejecucion(false), monitor_jugadores(new MonitorJugadores()), cola(new Queue<Accion *>(100)), escenario(200, 200, monitor_jugadores)
{
    // escenario.colocar_viga(50, 70, 0, -40);
    escenario.colocar_viga(70, 100, 1, 11);
    escenario.colocar_viga(180, 80, 1, 9);
    escenario.colocar_viga(150, 110, 0, -11);
    escenario.colocar_viga(370, 40, 0, -9);
    escenario.colocar_viga(200, 160, 1, 45);
    escenario.colocar_viga(300, 50, 1, 20);
    escenario.colocar_viga(250, 80, 1, -45);
    escenario.colocar_viga(300, 110, 0, 20);
    escenario.colocar_viga(400, 60, 0, -20);
    escenario.colocar_viga(0, 80, 1, 0);
    escenario.colocar_viga(100, 170, 0, -30);
    escenario.colocar_viga(340, 170, 1, 0);
    escenario.colocar_viga(500, 60, 0, 23);
    escenario.colocar_viga(450, 80, 0, 12);
    escenario.colocar_viga(480, 180, 1, -32);
    // escenario.colocar_viga(90, 140, 1, 0);
    // escenario.colocar_viga(340, 140, 1, 0);
    // escenario.colocar_viga(440, 210, 1, 0);
    // escenario.colocar_viga(940, 10, 1, 0);
}

void Partida::agregar_jugador(Jugador *jugador)
{
    int jugador_id = monitor_jugadores->agregar_jugador(jugador);
    jugador->jugar(cola, jugador_id);
    escenario.agregar_jugador(jugador_id);
    if (!en_ejecucion)
    {
        en_ejecucion = true;
        start();
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
