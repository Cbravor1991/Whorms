#ifndef __SERVERAIRATTACKMISSILE_H__
#define __SERVERAIRATTACKMISSILE_H__

#include "arma.h"
#include "mundo.h"
#include <string>

class MisilAereo : public Arma
{

private:
    int contador = 0;

public:
    MisilAereo(Mundo *world, float x, float y, int misil);
    ~MisilAereo();

    PosicionLanzable conseguir_posicion();
    void contacto();
};

#endif
