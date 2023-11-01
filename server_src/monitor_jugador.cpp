#include "monitor_jugador.h"

int MonitorJugadores::cambiar_turno()
{
    int id_turno = turno.cambiar_turno();
    for (const auto &entry : jugadores)
    {
        Jugador *jugador = entry.second;
        jugador->recibir_comando(new CambioTurno(id_turno));
    }
    return id_turno;
}

void MonitorJugadores::mandar_paquete(std::vector<PosicionJugador> jugadores)
{
    for (const auto &entry : this->jugadores)
    {
        Jugador *jugador = entry.second;
        jugador->recibir_comando(new Paquete(jugadores));
    }
}

void MonitorJugadores::mandar_segundos(int segundos)
{
    for (const auto &entry : jugadores)
    {
        Jugador *jugador = entry.second;
        jugador->recibir_comando(new Segundo(segundos));
    }
}

void MonitorJugadores::mandar_escenario(int x, int y, std::vector<PosicionViga> vigas, int id)
{
    Jugador *jugador = jugadores[id];
    jugador->recibir_comando(new EscenarioInformacion(x, y, vigas));
}

void MonitorJugadores::actualizar_jugadores_cantidad(int cantidad)
{
    std::unique_lock<std::mutex> lck(mutex_);
    std::cout << "Jugadores " << cantidad
              << ", esperando al resto de tus amigos…" << std::endl;
}

int MonitorJugadores::agregar_jugador(Jugador *jugador)
{
    actualizar_cantidad_jugadores(1);
    std::unique_lock<std::mutex> lck(mutex_);
    int id = cantidad_jugadores;
    while (jugadores[id] != nullptr)
    {
        id++;
    }
    jugadores[id] = jugador;
    turno.agregar_id(id);

    lck.unlock();

    return id;
}

void MonitorJugadores::avisar_desconexion()
{
    eliminar_jugadores_desconectados();
    actualizar_cantidad_jugadores(-1);
}

void MonitorJugadores::limpiar_desconectados()
{
    // Liberar la memoria de todos los jugadores desconectados en el vector
    for (auto jugador : jugadores_desconectados)
    {
        delete jugador;
    }

    // Limpiar el vector
    jugadores_desconectados.clear();
}

void MonitorJugadores::eliminar_jugadores_desconectados()
{
    std::unique_lock<std::mutex> lck(mutex_);

    // Utiliza un iterador para recorrer el mapa de jugadores
    auto it = jugadores.begin();
    while (it != jugadores.end())
    {
        int id = it->first;
        Jugador *jugador = it->second;

        if (!jugador->sigo_conectado())
        {
            jugadores_desconectados.push_back(jugador);
            it = jugadores.erase(it);
            turno.eliminar_id(id); // Elimina el ID del jugador de la clase Turno
        }
        else
        {
            ++it;
        }
    }
}

void MonitorJugadores::actualizar_cantidad_jugadores(int cantidad)
{
    cantidad_jugadores += cantidad;
    actualizar_jugadores_cantidad(cantidad_jugadores);
}

MonitorJugadores::~MonitorJugadores()
{
    limpiar_desconectados();
    // Liberar la memoria de todos los jugadores en el vector
    for (const auto &entry : jugadores)
    {
        Jugador *jugador = entry.second;
        delete jugador;
    }

    // Limpiar el vector
    jugadores.clear();
}
