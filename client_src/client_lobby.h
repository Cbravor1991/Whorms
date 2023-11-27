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
    
    Lobby(const std::string &hostname, const std::string &servname);

    void enviar_partida (int partida);

    void enviar_escenario (int escenario);

  
};
#endif
