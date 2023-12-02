#ifndef LOBBY_H
#define LOBBY_H

#pragma once
#include "./game.h"
#include <optional>
#include <vector>
#include <string>
#include <QApplication>
#include "client_protocol.h"

class Lobby
{
private:
    const std::string hostname;
    const std::string servname;
    ProtocoloCliente protocolo;
    std::vector<int> partida;
    std::vector<int> escenarios;

public:
    bool en_juego = false;

    Lobby(const std::string &hostname, const std::string &servname);

    void enviar_partida(int partida);

    int enviar_escenario(int escenario);

    void jugar();

    bool modo_partida();

    int cantidad_jugadores();

    void enviar_comienzo_juego();
};
#endif
