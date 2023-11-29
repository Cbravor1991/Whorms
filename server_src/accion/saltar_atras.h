#include "accion.h"

class SaltarAtras : public Accion
{
public:
    SaltarAtras(int id) : Accion(id) {}
    int ejecutar_accion(Escenario &escenario, bool cuenta_regresiva) override
    {
        escenario.mover_gusano_arriba_atras(jugador_id);
        return -1;
    }
};