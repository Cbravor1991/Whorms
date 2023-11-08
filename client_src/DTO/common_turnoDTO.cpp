
#include "common_turnoDTO.h"
TurnoDTO::TurnoDTO(int id, bool permiso) : id(id), permiso(permiso) {}

void TurnoDTO::cambiar_render(bool &permiso)
{
    permiso = this->permiso;
    std::cout << "Cambio turno a: " << id << std::endl;
}

int TurnoDTO::obtenerIdTurno()
{
    return id;
}

bool TurnoDTO::obtenerPermiso()
{
    return permiso;
}
