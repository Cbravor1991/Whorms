#ifndef COMMON_GANADORDTO_H
#define COMMON_GANADORDTO_H

#include <string>
#include <map>
#include <vector>
#include "common_state_game.h"
#include <ostream>
#include <iostream>

class GanadorDTO : public StateGame
{
private:
    int id_ganador;
    bool ganaste;

public:
    GanadorDTO(int id_ganador, bool ganaste);
    void cambiar_render(bool &permiso);
    void cargar();
};
#endif