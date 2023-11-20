
#ifndef ACCION_H_
#define ACCION_H_

#include "../escenario.h"

class Accion
{
protected:
    int jugador_id;

public:
    Accion(int id) : jugador_id(id) {}

    virtual int ejecutar_accion(Escenario &escenario)
    {
        escenario.avisar_desconexion(jugador_id);
        return jugador_id;
    }

    virtual ~Accion() {}
};

#endif
