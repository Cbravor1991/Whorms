

#include <string>
#include <map>
#include <vector>
#include "common_state_game.h"

class SegundosDTO : public StateGame
{
private:
    int segundos;

public:
    SegundosDTO(int segundos) : segundos(segundos)
    {
    }

    void cambiar_render(bool &permiso) override
    {
        std::cout << "Segundo: " << segundos << std::endl;
    }
};
