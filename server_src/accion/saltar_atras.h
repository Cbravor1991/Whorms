#include "accion.h"

class SaltarAtras : public Accion
{
public:
    SaltarAtras(int id) : Accion(id) {}
    int ejecutar_accion(Escenario &escenario) override
    {
        escenario.mover_gusano_arriba_atras(1, jugador_id);
        return -1;
    }
};