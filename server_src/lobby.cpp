#include "lobby.h"

Lobby::Lobby()
{
    std::vector<PosicionViga> vigas = configuracion_mapa.getVigas();
    for (const PosicionViga& viga : vigas) {
        escenarios[0].colocar_viga(viga.obtener_x(), viga.obtener_y(), viga.obtener_tipo(), viga.obtener_angulo());
    }
    escenarios[0].spawns_automaticos = configuracion_mapa.getSpawnsAutomaticos();
    escenarios[0].mapa_fondo = configuracion_mapa.getFondo();
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

int Lobby::crear_partida(Jugador *jugador, int escenario)
{
    Partida *partida = new Partida(escenarios[escenario]);
    partidas[partida_id] = partida;
    partida->agregar_jugador(jugador);
    int id = partida_id;
    partida_id++;
    return id;
}

void Lobby::iniciar_partida(int partida)
{
    partidas[partida]->start();
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