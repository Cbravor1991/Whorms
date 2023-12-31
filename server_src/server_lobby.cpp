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
    protocolo->enviar_escenarios(escenario);
    // se utiliza para saber si el jugador se va a unir o crear una partida

    int modo_lobby = protocolo->recibir_modo();
    if (modo_lobby == 1)
    {
        int escenario = protocolo->recibir_escenario();
        std::string mapa_recibido = protocolo->recibir_nombre_mapa();
   

        
        Jugador *jugador = new Jugador(protocolo);
        int partida = lobby->crear_partida(jugador, escenario, mapa_recibido);
        protocolo->enviar_partida_creada(partida);
        if (protocolo->recibir_jugar())
        {
            lobby->iniciar_partida(partida);
        }
    }
    else if(modo_lobby==0)
    {
        int partida = protocolo->recibir_partida();
        Jugador *jugador = new Jugador(protocolo);
        lobby->agregar_jugador(jugador, partida);
    }
}
