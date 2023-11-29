#include "accion.h"

class MoverDerecha : public Accion
{
public:
    MoverDerecha(int id) : Accion(id) {}
    int ejecutar_accion(Escenario &escenario, bool cuenta_regresiva) override
    {
        escenario.mover_gusano_derecha(jugador_id);
        return -1;
    }
};