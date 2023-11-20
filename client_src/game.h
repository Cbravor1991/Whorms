#ifndef GAME_H
#define GAME_H
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


class Game
{
private:
    Cliente cliente;
    GameView view;
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

    
    // prueba de concepto
    Weapon *armaRecibida = nullptr;

    bool probar_arma = false;

public:
    // reemplazar por socket cuando este lobby
    explicit Game(const std::string &hostname, const std::string &servname);

    void run();

    bool gameLoop(StateGame *estado, bool &nuevo_estado);

    bool manejarEventos();

    void procesar_estado(StateGame *estado);

    void cargar_escenario(EscenarioDTO *escenario);

    void cargar_arma (PaqueteDTO *paquete);

    void procesar_paquete(PaqueteDTO *paquete);

    void renderizar_misiles ();

    void renderizar();
};
#endif // GAME_H