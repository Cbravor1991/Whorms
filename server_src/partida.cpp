#include "partida.h"
#include <iostream>
#include <chrono>
#include <cmath>

Partida::Partida(ConfiguracionMapa mapa) : en_ejecucion(false), monitor_jugadores(new MonitorJugadores()), cola(new Queue<Accion *>(100)), escenario(mapa, monitor_jugadores)
{
    tipo_fondo = mapa.getFondo();
}

void Partida::agregar_jugador(Jugador *jugador)
{
    monitor_jugadores->agregar_jugador(jugador);
}

void Partida::detener_partida()
{
    en_ejecucion = false;
}

void Partida::run()
{

    monitor_jugadores->comenzar_juego(cola, tipo_fondo);
    escenario.agregar_jugadores();
    std::chrono::time_point<std::chrono::steady_clock> ultimo_cambio_de_turno = std::chrono::steady_clock::now();
    int ultimo_numero_notificado = 0; // Comenzar en 31 para iniciar con 30 segundos
    en_ejecucion = true;
    int segundos_regresivos = -1;
    int segundo_actual = 30;
    bool cuenta_regresiva = false;
    int id_regresivo = -1;
    Accion *accion = nullptr;
    while (en_ejecucion)
    {
        auto ahora = std::chrono::steady_clock::now();
        int segundos_transcurridos = std::chrono::duration_cast<std::chrono::seconds>(ahora - ultimo_cambio_de_turno).count();

        if (cola->try_pop(accion))
        {
            if (accion != nullptr)
            {
                int regresivo = accion->ejecutar_accion(escenario, cuenta_regresiva);
                if (regresivo > 0)
                {
                    segundos_regresivos = segundo_actual - regresivo;
                    cuenta_regresiva = true;
                    id_regresivo = id_turno;
                    if (segundos_regresivos < 0)
                    {
                        segundos_regresivos = 1;
                    }
                }
                delete accion;
            }
        }

        if (segundos_regresivos == segundo_actual and cuenta_regresiva)
        {
            escenario.explotar_bombas_regresivas(id_regresivo);
            cuenta_regresiva = false;
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
            cuenta_regresiva = false;
        }

        // Contar en reversa desde 30 hasta 0
        segundo_actual = round(DURACION_TURNO - segundos_transcurridos);

        // Verificar si es un nuevo número antes de notificar a los jugadores
        if (segundo_actual != ultimo_numero_notificado)
        {
            monitor_jugadores->mandar_segundos(segundo_actual);
            ultimo_numero_notificado = segundo_actual;
        }

        auto frame_rate_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<float>(FRAME_RATE));
        auto tiempo_restante = frame_rate_ms - (std::chrono::steady_clock::now() - ahora);

        // Dormir solo si el tiempo restante es positivo
        if (tiempo_restante.count() > 0)
        {
            std::this_thread::sleep_for(tiempo_restante);
        }
    }
    delete monitor_jugadores;
    while (cola->try_pop(accion))
    {
        delete accion;
    }
    delete cola;
}
