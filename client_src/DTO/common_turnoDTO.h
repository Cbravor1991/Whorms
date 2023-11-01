

#include <string>
#include <map>
#include <vector>
#include "common_state_game.h"

class TurnoDTO : public StateGame
{
private:
    int id;
    bool permiso;

public:
    TurnoDTO(int id, bool permiso) : id(id), permiso(permiso) {}

    void cambiar_render(bool &permiso) override
    {
        permiso = this->permiso;
        std::cout << "Cambio turno a: " << id << std::endl;
    }
};
