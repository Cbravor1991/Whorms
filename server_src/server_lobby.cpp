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
    // partidas = lobby.obtener_partidas();
    // protocolo->enviar_partidas(partidas);
    // int partida_id = protocolo->recibir_partida();
    Jugador *jugador = new Jugador(protocolo);
    lobby->agregar_jugador(jugador, 1);
}
