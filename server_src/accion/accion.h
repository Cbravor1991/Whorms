
#ifndef ACCION_H_
#define ACCION_H_

#include "../escenario.h"

class Accion
{
protected:
    int jugador_id;

public:
    Accion(int id) : jugador_id(id) {}

    virtual void ejecutar_accion(Escenario &escenario) {}

    virtual int avisar_desconectado() { return -1; }

    virtual ~Accion() {}
};

#endif
