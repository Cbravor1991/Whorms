#ifndef LOBBY_H
#define LOBBY_H

#include <vector>
#include <string>
#include <map>
#include "monitor_jugador.h"
#include "partida.h"

#include "../../server_src/configuracion.h"
#include "../../server_src/configuracion_mapa.h"
#include "data/posicion_viga.h"

#define configuracion Configuracion::obtener_configuracion()
#define configuracion_mapa ConfiguracionMapa::obtener_configuracion_mapa()

// Definición de la clase Lobby
class Lobby
{
public:
    Lobby();
    ~Lobby();

    std::vector<int> obtener_partidas();
    std::vector<int> obtener_escenarios();

    void agregar_jugador(Jugador *jugador, int partida_id);

    // Crear una nueva partida con un escenario
    int crear_partida(Jugador *jugador, int escenario);

    void iniciar_partida(int partida);

private:
    std::map<int, Partida *> partidas;
    std::map<int, Escenario> escenarios;
    int partida_id = 1;
};

#endif