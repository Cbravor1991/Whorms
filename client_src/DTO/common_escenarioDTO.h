

#ifndef ESCENARIODTO_H_
#define ESCENARIODTO_H_

#include <string>
#include <map>
#include <vector>
#include "common_vigaDTO.h"
#include "common_state_game.h"

class EscenarioDTO : public StateGame
{
private:
    int x;
    int y;
    std::vector<VigaDTO> vigas;

public:
    EscenarioDTO(int x, int y, std::vector<VigaDTO> vigas) : x(x), y(y), vigas(vigas) {}

    void cambiar_render(bool &permiso) override
    {
        for (const VigaDTO &viga : vigas)
        {
            viga.mostrar();
        }
    }
};

#endif
