#include "common_ganadorDTO.h"

GanadorDTO::GanadorDTO(int id_ganador, bool ganaste) : id_ganador(id_ganador), ganaste(ganaste)
{
    type = TIPO_GANADOR;
}

void GanadorDTO::cambiar_render(bool &permiso)
{
}

void GanadorDTO::cargar()
{
}

bool GanadorDTO::obtenerEstado()
{
    return this->ganaste;
}