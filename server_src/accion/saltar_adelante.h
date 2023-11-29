#include "accion.h"

class SaltarAdelante : public Accion
{
public:
    SaltarAdelante(int id) : Accion(id) {}
    int ejecutar_accion(Escenario &escenario, bool cuenta_regresiva) override
    {
        escenario.mover_gusano_arriba_adelante(jugador_id);
        return -1;
    }
};