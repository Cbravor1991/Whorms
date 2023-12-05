#include "lobby.h"

Lobby::Lobby()
{
}

std::vector<int> Lobby::obtener_partidas()
{
    std::vector<int> partidas_ids;
    for (const auto &par : partidas_disponibles)
    {
        partidas_ids.push_back(par.first);
    }

    return partidas_ids;
}

std::vector<int> Lobby::obtener_escenarios()
{

    std::vector<int> escenarios_ids;

    return escenarios_ids;
}

int Lobby::crear_partida(Jugador *jugador, int escenario, std::string&nombre_mapa)
{  
    std::unique_lock<std::mutex> lck(mutex_);
    ConfiguracionMapa configuracion_mapa = ConfiguracionMapa::obtener_configuracion_mapa(nombre_mapa);
    Partida *partida = new Partida(configuracion_mapa);
    partidas_disponibles[partida_id] = partida;
    partida->agregar_jugador(jugador);
    int id = partida_id;
    partida_id++;
    lck.unlock();
    return id;
}

void Lobby::iniciar_partida(int partida)
{
    std::unique_lock<std::mutex> lck(mutex_);
    if (partidas_disponibles.find(partida) != partidas_disponibles.end())
    {
        // Obtener el puntero a la partida desde partidas_disponibles
        Partida *partida_ptr = partidas_disponibles[partida];

        // Eliminar la partida de partidas_disponibles
        partidas_disponibles.erase(partida);

        // Agregar la partida a partidas_en_juego
        partidas_en_juego.push_back(partida_ptr);

        // Iniciar la partida
        partida_ptr->start();
    }
    lck.unlock();
}

void Lobby::agregar_jugador(Jugador *jugador, int partida_id)
{
    std::unique_lock<std::mutex> lck(mutex_);
    Partida *partida = partidas_disponibles[partida_id];
    partida->agregar_jugador(jugador);
    lck.unlock();
}

Lobby::~Lobby()
{
    // Limpiar partidas disponibles
    for (const auto &entry : partidas_disponibles)
    {
        Partida *partida = entry.second;
        delete partida;
    }

    // Limpiar partidas en juego
    for (Partida *partida : partidas_en_juego)
    {
        partida->detener_partida();
        partida->join();
        delete partida;
    }

    // Limpiar los vectores
    partidas_disponibles.clear();
    partidas_en_juego.clear();
}