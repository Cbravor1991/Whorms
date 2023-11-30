#include "common_vientoDTO.h"

VientoDTO::VientoDTO(float velocidad, bool direccion) : velocidad(velocidad), direccion(direccion)
{
    type = TIPO_VIENTO;
}

void VientoDTO::cambiar_render(bool &permiso)
{
}

void VientoDTO::cargar(VientoDTO &viento)
{
    viento.direccion = this->direccion;
    viento.velocidad = this->velocidad;
}

float VientoDTO::obtenerVelocidad() 
{
    return velocidad;
}

bool VientoDTO::obtenerDireccion()
{
    return direccion;
}