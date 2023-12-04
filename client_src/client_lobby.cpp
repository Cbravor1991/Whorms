#include "./client_lobby.h"
#include <cstring>
#include <utility>
#include <string>
#include <iostream>

Lobby::Lobby(const std::string &hostname, const std::string &servname) : hostname(hostname), servname(servname), protocolo(hostname, servname)
{

    partida = protocolo.recibir_partidas();
    escenarios = protocolo.recibir_escenarios();

    std::vector<int> prueba = obtener_partidas();
      if (!prueba.empty()) {
        std::cout << "La partida es: " << prueba[0] << '\n';
    } else {
        std::cout << "El vector de partidas está vacío.\n";
    }
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
    return protocolo.recibir_tipo_fondo(); // cambiar nombre funcion
}

bool Lobby::modo_partida()
{
    bool modo = protocolo.recibir_modo_partida();
    if (modo)
    {
        tipo_fondo = protocolo.recibir_tipo_fondo();
    }
    return modo;
}

void Lobby::enviar_comienzo_juego()
{
    protocolo.enviar_comienzo_juego();
    bool modo = protocolo.recibir_modo_partida();
    if (modo)
    {
        tipo_fondo = protocolo.recibir_tipo_fondo();
    }
}

void Lobby::jugar()
{
    en_juego = true;
    Game juego(protocolo);
    juego.run();
}

    std::vector<int>Lobby::obtener_partidas()
{
    return partida;
}
