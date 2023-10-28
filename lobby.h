#ifndef LOBBY_H
#define LOBBY_H

#include <vector>
#include <string>
#include <map>
#include "monitor_jugador.h"
#include "partida.h"

// Definición de la clase Lobby
class Lobby
{
public:
    Lobby();
    ~Lobby();

    std::map<int, Partida *> obtener_partidas() const;

    void agregar_jugador(Jugador *jugador, int partida_id);

    // Crear una nueva partida con un escenario
    void crear_partida(Jugador *jugador, int partida_id);

private:
    std::map<int, Partida *> partidas;
    int partida_id;
};

#endif