

#ifndef ESCENARIODTO_H_
#define ESCENARIODTO_H_

#include <string>
#include <map>
#include <vector>
#include "common_vigaDTO.h"
#include "common_state_game.h"
#include "common_provisionDTO.h"

class EscenarioDTO : public StateGame
{
private:
    int x;
    int y;
    std::vector<VigaDTO> vigas;
    std::vector<ProvisionDTO> provisiones;

public:
    EscenarioDTO(int x, int y, std::vector<VigaDTO> vigas, std::vector<ProvisionDTO> provisiones);

    std::vector<VigaDTO> obtener_vigas();

    std::vector<ProvisionDTO> obtener_provisiones();

    void cambiar_render(bool &permiso) override;
};
#endif
