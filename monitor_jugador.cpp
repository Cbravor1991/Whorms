#include "monitor_jugador.h"
#include "turno.cpp"

int MonitorJugadores::cambiar_turno()
{
    int id_turno = turno.cambiar_turno();
    std::string comando = "turno " + std::to_string(id_turno);
    for (const auto &entry : jugadores)
    {
        Jugador *jugador = entry.second;
        jugador->recibir_comando(comando);
    }
    return id_turno;
}
void MonitorJugadores::notificar_segundos(int segundos)
{
    std::cout << "Segundo: " << segundos << std::endl;
    // for (const auto &par : jugadores)
    //{Jugador *jugador = par.second;
    //  jugador->notificar_segundos(segundos);
    // }
}

void MonitorJugadores::actualizar_jugadores_cantidad(int cantidad)
{
    std::unique_lock<std::mutex> lck(mutex_);
    std::cout << "Jugadores " << cantidad
              << ", esperando al resto de tus amigos…" << std::endl;
    std::string comando = "cantidad " + std::to_string(cantidad);
    for (const auto &entry : jugadores)
    {
        Jugador *jugador = entry.second;
        jugador->recibir_comando(comando);
    }
}

void MonitorJugadores::actualizar_jugadores_jugador(int id, int x, int y)
{
    std::cout << "Jugador " << id << " en coordenadas"
              << " X: " << x << " Y: " << y << std::endl;
    std::string comando = "jugador " + std::to_string(id) + " " + std::to_string(x) + " " + std::to_string(y);
    for (const auto &entry : jugadores)
    {
        Jugador *jugador = entry.second;
        jugador->recibir_comando(comando);
    }
}

int MonitorJugadores::agregar_jugador(Jugador *jugador)
{
    std::unique_lock<std::mutex> lck(mutex_);
    id++;
    jugadores[id] = jugador;
    turno.agregar_id(id);

    lck.unlock();

    actualizar_cantidad_jugadores(1);
    // cargar_mapa(jugador);

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

void MonitorJugadores::agregar_viga(bool tipo, int x, int y)
{
    Viga nueva_viga;
    nueva_viga.tipo = tipo;
    nueva_viga.x = x;
    nueva_viga.y = y;

    vigas.push_back(nueva_viga);
}

void MonitorJugadores::cargar_mapa(Jugador *jugador)
{
    for (auto &viga : vigas)
    {
        std::string comando = "viga " + std::to_string(viga.tipo) + " " + std::to_string(viga.x) + " " + std::to_string(viga.y);
        jugador->recibir_comando(comando);
    }
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
