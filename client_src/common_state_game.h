

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
    bool turno = false;
    int tipo_mensaje;

public:
    StateGame();
    void cargar_escenario(EscenarioDTO escenario);
    void cargar_tipo_mensaje(int tipo_mensaje);
    void cargar_turno(bool turno);
    int obtener_turno();
    int obtener_tipo_mensaje();
    void cargar_jugador(JugadorDTO jugador);
    EscenarioDTO obtener_escenario();
    JugadorDTO obtener_jugador();
};

#endif
