
#include "common_turnoDTO.h"
TurnoDTO::TurnoDTO(int id, bool permiso, int gusano_id) : id(id), permiso(permiso), gusano_id(gusano_id)
{
    type = TIPO_TURNO;
}

void TurnoDTO::cambiar_render(bool &permiso)
{
    permiso = this->permiso;
}

int TurnoDTO::obtenerIdTurno()
{
    return id * 100 + gusano_id;
}

bool TurnoDTO::obtenerPermiso()
{
    return permiso;
}
