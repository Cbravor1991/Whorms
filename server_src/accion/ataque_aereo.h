#include "accion.h"

class AtaqueAereo : public Accion
{
public:
    AtaqueAereo(int id) : Accion(id) {}
    int ejecutar_accion(Escenario &escenario) override
    {
        escenario.equipar_arma(1, jugador_id, 1);
        return -1;
    }
};