#include "accion.h"

class MoverDerecha : public Accion
{
public:
    MoverDerecha(int id) : Accion(id) {}
    void ejecutar_accion(Escenario &escenario) override
    {

        escenario.mover_gusano_derecha(1, jugador_id);
    }
};