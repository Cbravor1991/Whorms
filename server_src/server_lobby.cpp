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
    // se utiliza para saber si el jugador se va a unir o crear una partida

    bool modo_lobby = protocolo->recibir_modo();
    //OJO: la clase lobby puede ser accedida por varios ServerLobby threads al mismo
    //tiempo, es necesario que lobby tenga un lock (por lo menos) para proteger esos recursos.
    if (modo_lobby)
    {
        int escenario = protocolo->recibir_escenario();
        Jugador *jugador = new Jugador(protocolo);
        int partida = lobby->crear_partida(jugador, escenario);
        if (protocolo->recibir_jugar())
        {
            lobby->iniciar_partida(partida);
        }
    }
    else
    {
        int partida = protocolo->recibir_partida();
        Jugador *jugador = new Jugador(protocolo);
        lobby->agregar_jugador(jugador, partida);
    }
}
