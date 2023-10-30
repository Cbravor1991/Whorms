#include "accion.h"

class Desconexion : public Accion
{
public:
    Desconexion(int id) : Accion(id) {}
    void ejecutar_accion(Escenario &escenario) override
    {
        escenario.avisar_desconexion(jugador_id);
    }

    int avisar_desconectado() override { return jugador_id; }
};