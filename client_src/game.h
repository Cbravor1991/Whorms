#ifndef GAME_H
#define GAME_H

#pragma once
#include <string>
#include "client.h"
#include "graphics/view.h"
#include <vector>
#include <map>
#include <set>
#include "actions/right.h"
#include "actions/left.h"
#include "actions/jump_back.h"
#include "actions/jump_foward.h"
#include "actions/weapon.h"
#include "actions/position.h"
#include "DTO/common_state_game.h"
#include "DTO/common_vigaDTO.h"
#include "DTO/common_jugadorDTO.h"
#include "DTO/common_paqueteDTO.h"
#include "DTO/common_escenarioDTO.h"
#include "DTO/common_turnoDTO.h"
#include "DTO/common_segundosDTO.h"
#include "DTO/common_armaDTO.h"
#include "DTO/common_objetoDTO.h"
#include "DTO/common_vientoDTO.h"
#include "DTO/common_ganadorDTO.h"
#include "graphics/team_health.h"

class Game
{
private:
    Cliente cliente;
    GameView view;
    std::vector<Explotion> explosiones;
    std::vector<ObjetoDTO> objetos;
    std::vector<VigaDTO> vigas;
    std::map<int, JugadorDTO> jugadores;
    int tiempo_restante_turno = 30;
    int turno = 1; // id del jugador con turno
    bool permiso = false;
    int gusanoX;
    int gusanoY;
    int armaX;
    int armaY;
    int tipo;
    bool termino_juego = false;
    bool gane = true;
    bool cola_vacia = true;
    VientoDTO viento;
    TeamHealth vida_equipos;
    int fondo_pantalla = 2;


public:
    explicit Game( ProtocoloCliente & protocolo);

    void run();

    bool gameLoop(StateGame *estado, bool &nuevo_estado);

    bool manejarEventos();

    void procesar_estado(StateGame *estado);

    void cargar_escenario(EscenarioDTO *escenario);

    void cargar_arma(PaqueteDTO *paquete);

    void procesar_paquete(PaqueteDTO *paquete);

    void renderizar_misiles();

    void renderizar();

    bool endGameLoop();

      void cargar_fondo_pantalla(int fondo_recibido);
};
#endif // GAME_H