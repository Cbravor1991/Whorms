#include "common_vientoDTO.h"

VientoDTO::VientoDTO(float velocidad, bool direccion) : velocidad(velocidad), direccion(direccion)
{
    type = TIPO_VIENTO;
}

void VientoDTO::cambiar_render(bool &permiso)
{
}

void VientoDTO::cargar()
{
}
