#include "accion.h"

class Desconexion : public Accion
{
public:
    Desconexion(int id) : Accion(id) {}
    int ejecutar_accion(Escenario &escenario) override
    {
        escenario.avisar_desconexion(jugador_id);
        return jugador_id;
    }
};