#ifndef __ATAQUE_AEREO_H__
#define __ATAQUE_AEREO_H__

#include "arma.h"
#include "misil_aereo.h"
#include <string>

class AtaqueAereo : public Arma
{
private:
    int x;
    int y;

public:
    AtaqueAereo(int x, int y);
    ~AtaqueAereo();

    int disparar(Mundo *mundo, b2Body *disparador) override;

    PosicionLanzable conseguir_posicion();
};

#endif
