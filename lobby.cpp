#include "lobby.h"
#include "partida.cpp"

Lobby::Lobby()
{
    Partida *partida = new Partida();
    partidas[1] = partida;
}

std::map<int, Partida *> Lobby::obtener_partidas() const
{
    return partidas;
}

void Lobby::crear_partida(Jugador *jugador, int partida_id)
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