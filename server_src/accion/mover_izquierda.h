#include "accion.h"

class MoverIzquierda : public Accion
{
public:
    MoverIzquierda(int id) : Accion(id) {}

    void ejecutar_accion(Escenario &escenario) override
    {
        escenario.mover_gusano_izquierda(jugador_id);
    }
};