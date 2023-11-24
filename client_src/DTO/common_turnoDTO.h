

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
    int gusano_id;

public:
    TurnoDTO(int id, bool permiso, int gusano_id);

    void cambiar_render(bool &permiso);

    int obtenerIdTurno();

    bool obtenerPermiso();
};
