#include "monitor_jugador.h"

void MonitorJugadores::actualizar_jugadores_viga(bool tipo, int x, int y)
{
    std::unique_lock<std::mutex> lck(mutex_);
    std::cout << "Viga " << tipo << " en coordenadas"
              << " X: " << x << " Y: " << y << std::endl;
    for (auto &jugador : jugadores)
    {
        jugador->enviar_viga(tipo, x, y);
    }
}

void MonitorJugadores::actualizar_jugadores_cantidad(int cantidad)
{
    std::unique_lock<std::mutex> lck(mutex_);
    std::cout << "Jugadores " << cantidad
              << ", esperando al resto de tus amigos…" << std::endl;
    for (auto &jugador : jugadores)
    {
        jugador->enviar_cantidad_jugadores(cantidad);
    }
}

void MonitorJugadores::actualizar_jugadores_jugador(int id, int x, int y)
{
    std::unique_lock<std::mutex> lck(mutex_);
    std::cout << "Jugador " << id << " en coordenadas"
              << " X: " << x << " Y: " << y << std::endl;
    for (auto &jugador : jugadores)
    {
        jugador->enviar_jugador(id, x, y);
    }
}

void MonitorJugadores::agregar_jugador(Jugador *jugador)
{
    std::unique_lock<std::mutex> lck(mutex_);
    jugadores.push_back(jugador);
    lck.unlock();
    actualizar_cantidad_jugadores(1);
    cargar_mapa(jugador);
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
    // Utiliza un iterador para recorrer la lista de jugadores
    auto it = jugadores.begin();
    while (it != jugadores.end())
    {
        Jugador *jugador = *it;
        if (!jugador->sigo_conectado())
        {
            jugadores_desconectados.push_back(jugador);
            it = jugadores.erase(it);
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
        jugador->enviar_viga(viga.tipo, viga.x, viga.y);
    }
}

MonitorJugadores::~MonitorJugadores()
{
    limpiar_desconectados();
    // Liberar la memoria de todos los jugadores en el vector
    for (auto jugador : jugadores)
    {
        delete jugador;
    }

    // Limpiar el vector
    jugadores.clear();
}
