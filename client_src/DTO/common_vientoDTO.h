#ifndef COMMON_VIENTODTO_H
#define COMMON_VIENTODTO_H

#include <string>
#include <map>
#include <vector>
#include "common_state_game.h"
#include <ostream>
#include <iostream>

class VientoDTO : public StateGame
{
private:
    float velocidad;
    bool direccion;

public:
    VientoDTO(float velocidad, bool direccion);
    void cambiar_render(bool &permiso);
    void cargar();
};
#endif