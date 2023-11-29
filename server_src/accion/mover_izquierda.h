#include "accion.h"

class MoverIzquierda : public Accion
{
public:
    MoverIzquierda(int id) : Accion(id) {}

    int ejecutar_accion(Escenario &escenario, bool cuenta_regresiva) override
    {
        escenario.mover_gusano_izquierda(jugador_id);
        return -1;
    }
};