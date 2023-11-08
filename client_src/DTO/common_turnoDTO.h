

#include <string>
#include <map>
#include <vector>
#include "common_state_game.h"
#include <ostream>
#include <iostream>

class TurnoDTO : public StateGame
{
private:
    int id;
    bool permiso;

public:
    TurnoDTO(int id, bool permiso);

    void cambiar_render(bool &permiso);

    int obtenerIdTurno();

    bool obtenerPermiso();
};
