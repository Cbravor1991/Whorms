#include "accion.h"

class Desconexion : public Accion
{
public:
    Desconexion(int id) : Accion(id) {}
    int ejecutar_accion(Escenario &escenario, bool cuenta_regresiva) override
    {
        escenario.avisar_desconexion(jugador_id);
        return -1;
    }
};