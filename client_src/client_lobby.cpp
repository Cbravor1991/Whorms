#include "./client_lobby.h"
#include <cstring>
#include <utility>
#include <string>
#include <iostream>

Lobby::Lobby(const std::string &hostname, const std::string &servname) : hostname(hostname), servname(servname), protocolo(hostname, servname)
{

    partida = protocolo.recibir_partidas();
    escenarios = protocolo.recibir_escenarios();
}

void Lobby::enviar_partida(int partida)
{
    protocolo.enviar_modo(0);
    protocolo.enviar_partida(partida);
}

int Lobby::enviar_escenario(int escenario)
{
    protocolo.enviar_modo(1);
    protocolo.enviar_escenario(escenario);
    protocolo.recibir_modo_partida();
    protocolo.recibir_cantidad_jugadores_en_espera();
    return protocolo.recibir_cantidad_jugadores_en_espera(); // cambiar nombre funcion
}

bool Lobby::modo_partida()
{
    return protocolo.recibir_modo_partida();
}

int Lobby::cantidad_jugadores()
{
    return protocolo.recibir_cantidad_jugadores_en_espera();
}

void Lobby::enviar_comienzo_juego()
{
    protocolo.enviar_comienzo_juego();
    while (!modo_partida())
    {

        cantidad_jugadores();
    }
}

void Lobby::jugar()
{
    en_juego = true;
    Game juego(protocolo);
    juego.run();
}
