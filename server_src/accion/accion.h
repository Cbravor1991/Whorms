
#ifndef ACCION_H_
#define ACCION_H_

#include "../escenario.h"

class Accion
{
protected:
    int jugador_id;

public:
    Accion(int id) : jugador_id(id) {}

    virtual int ejecutar_accion(Escenario &escenario, bool cuenta_regresiva)
    {
        escenario.avisar_desconexion(jugador_id);
        return -1;
    }

    virtual ~Accion() {}
};

#endif
