#include "lobby.h"

Lobby::Lobby()
{
    escenarios[0].colocar_viga(70, 100, 1, 11);
    escenarios[0].colocar_viga(180, 80, 1, 9);
    escenarios[0].colocar_viga(150, 110, 0, -11);
    escenarios[0].colocar_viga(370, 40, 0, -9);
    escenarios[0].colocar_viga(200, 160, 1, 45);
    escenarios[0].colocar_viga(300, 50, 1, 20);
    escenarios[0].colocar_viga(250, 80, 1, -45);
    escenarios[0].colocar_viga(300, 110, 0, 20);
    escenarios[0].colocar_viga(400, 60, 0, -20);
    escenarios[0].colocar_viga(0, 80, 1, 0);
    escenarios[0].colocar_viga(100, 170, 0, -30);
    escenarios[0].colocar_viga(340, 170, 1, 0);
    escenarios[0].colocar_viga(500, 60, 0, 23);
    escenarios[0].colocar_viga(450, 80, 0, 12);
    escenarios[0].colocar_viga(480, 180, 1, -32);
    Partida *partida = new Partida(escenarios[0]);
    partidas[0] = partida;
}

std::vector<int> Lobby::obtener_partidas()
{
    std::vector<int> partidas_ids;
    for (const auto &par : partidas)
    {
        partidas_ids.push_back(par.first);
    }

    return partidas_ids;
}

std::vector<int> Lobby::obtener_escenarios()
{

    std::vector<int> escenarios_ids;
    for (const auto &par : escenarios)
    {
        escenarios_ids.push_back(par.first);
    }

    return escenarios_ids;
}

void Lobby::crear_partida(Jugador *jugador, int escenario)
{
    Partida *partida = new Partida(escenarios[escenario]);
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