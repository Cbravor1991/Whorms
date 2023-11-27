#include <iostream>
#include <sstream>
#include <valarray>
#include <vector>
#include <utility>
#include <netinet/in.h>
#include <fstream>
#include "server_lobby.h"

ServerLobby::ServerLobby(
    ProtocoloServer *protocolo, Lobby *lobby) : protocolo(protocolo), lobby(lobby)
{
}

void ServerLobby::run()
{
     std::vector<int> partidas;
     partidas = lobby->obtener_partidas();
     std::vector<int> escenario = lobby->obtener_escenarios();
    protocolo->enviar_partidas(partidas);
    protocolo->enviar_partidas(escenario);
    //se utiliza para saber si el jugador se va a unir o crear una partida

    bool modo_lobby = protocolo->recibir_modo();
    if (modo_lobby){
        int escenario = protocolo->recibir_escenario();
        Jugador *jugador = new Jugador(protocolo);
        lobby->crear_partida(jugador, escenario);
    }else {
        int partida = protocolo->recibir_partida();
        Jugador *jugador = new Jugador(protocolo);
        lobby->agregar_jugador(jugador, partida);

    }

   
 
}
