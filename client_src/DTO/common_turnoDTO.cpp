
#include "common_turnoDTO.h"
TurnoDTO::TurnoDTO(int id, bool permiso, int gusano_id) : id(id), permiso(permiso), gusano_id(gusano_id)
{
    type = TIPO_TURNO;
}

void TurnoDTO::cambiar_render(bool &permiso)
{
    permiso = this->permiso;
    std::cout << "Cambio turno a: " << id << std::endl;
}

int TurnoDTO::obtenerIdTurno()
{
    return id * 10 + gusano_id;
}

bool TurnoDTO::obtenerPermiso()
{
    return permiso;
}
