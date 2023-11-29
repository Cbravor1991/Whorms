

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
    EscenarioDTO(int x, int y, std::vector<VigaDTO> vigas);

    std::vector<VigaDTO> obtener_vigas();

    void cambiar_render(bool &permiso) override;
};
#endif
