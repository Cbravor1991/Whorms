

#ifndef COMMON_STATE_GAME_H_
#define COMMON_STATE_GAME_H_

#include <string>
#include <map>
#include <vector>

const int TIPO_TURNO = 0;
const int TIPO_SEGUNDO = 1;
const int TIPO_PAQUETE = 2;
const int TIPO_ESCENARIO = 3;
const int TIPO_ARMA = 4;
const int TIPO_VIENTO = 6;
const int TIPO_GANADOR = 7;

class StateGame
{

public:
    int type;

    StateGame() {}
    virtual void cambiar_render(bool &permiso) {}
    virtual ~StateGame() {}
};

#endif
