#include "lobby.h"

Lobby::Lobby()
{
    Partida *partida = new Partida();
    partidas[0] = partida;
}

std::vector<int> Lobby::obtener_partidas()
{  
    std::vector<int> partidas_ids;
    for (const auto& par : partidas) {
        partidas_ids.push_back(par.first);
    }
    
    return partidas_ids;
}

     std::vector<int> Lobby::obtener_escenarios()
{   

     std::vector<int> partidas_ids;
     partidas_ids.push_back(1);
    //  for (const auto& par : partidas) {
    //      partidas_ids.push_back(par.first);
    //  }
    
    return partidas_ids;
}

void Lobby::crear_partida(Jugador *jugador, int escenario)
{
    Partida *partida = new Partida();
    partidas[partida_id] = partida;
    partida->agregar_jugador(jugador);
    partida_id++;
}

void Lobby::agregar_jugador(Jugador *jugador, int partida_id)
{
    Partida *partida = partidas[partida_id];
    partida->agregar_jugador(jugador);
}

Lobby::~Lobby()
{
    for (const auto &entry : partidas)
    {
        Partida *partida = entry.second;
        partida->detener_partida();
        partida->join();
        delete partida;
    }

    // Limpiar el vector
    partidas.clear();
}