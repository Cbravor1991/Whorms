#include "accion.h"

class MoverIzquierda : public Accion
{
public:
    MoverIzquierda(int id) : Accion(id) {}

    int ejecutar_accion(Escenario &escenario) override
    {
        escenario.mover_gusano_izquierda(1, jugador_id);
        return -1;
    }
};