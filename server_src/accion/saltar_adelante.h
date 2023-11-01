#include "accion.h"

class SaltarAdelante : public Accion
{
public:
    SaltarAdelante(int id) : Accion(id) {}
    int ejecutar_accion(Escenario &escenario) override
    {
        escenario.mover_gusano_arriba_adelante(1, jugador_id);
        return -1;
    }
};