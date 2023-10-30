

#ifndef STATEGAME_H_
#define STATEGAME_H_

#include <string>
#include <map>
#include <vector>
#include "common_escenarioDTO.h"
#include "common_jugadorDTO.h"
#include "common_jugadorDTO.h"

class StateGame
{
private:
    EscenarioDTO escenario;
    JugadorDTO jugador;
    int tipo_mensaje;

public:
    StateGame();
    void cargar_escenario(EscenarioDTO escenario);
    void cargar_tipo_mensaje(int tipo_mensaje);
    int obtener_tipo_menseje();
    void cargar_jugador(JugadorDTO jugador);
    EscenarioDTO obtener_escenario();
    JugadorDTO obtener_jugador();
};

#endif
