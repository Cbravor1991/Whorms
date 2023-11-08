

#include <string>
#include <map>
#include <vector>
#include "common_state_game.h"
#include <ostream>
#include <iostream>

class SegundosDTO : public StateGame
{
private:
    int segundos;

public:
    SegundosDTO(int segundos);
    void cambiar_render(bool &permiso);

    int obtenerTiempo();
};
