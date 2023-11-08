#include "common_segundosDTO.h"

SegundosDTO::SegundosDTO(int segundos) : segundos(segundos)
{
}

void SegundosDTO::cambiar_render(bool &permiso)
{
    std::cout << "Segundo: " << segundos << std::endl;
}

int SegundosDTO::obtenerTiempo() { return segundos; }
