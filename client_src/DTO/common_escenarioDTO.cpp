
#include "common_escenarioDTO.h"

EscenarioDTO::EscenarioDTO(int x, int y, std::vector<VigaDTO> vigas) : x(x), y(y), vigas(vigas) { type = TIPO_ESCENARIO; }

void EscenarioDTO::cambiar_render(bool &permiso)
{
    for (const VigaDTO &viga : vigas)
    {
        viga.mostrar();
    }
}

std::vector<VigaDTO> EscenarioDTO::obtener_vigas()
{
    return vigas;
}