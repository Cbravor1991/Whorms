#include "common_segundosDTO.h"

SegundosDTO::SegundosDTO(int segundos) : segundos(segundos)
{
    type = TIPO_SEGUNDO;
}

void SegundosDTO::cambiar_render(bool &permiso)
{
    std::cout << "Segundo: " << segundos << std::endl;
}

int SegundosDTO::obtenerTiempo() { return segundos; }
