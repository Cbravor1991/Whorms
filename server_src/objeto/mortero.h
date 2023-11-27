#ifndef MORTERO_H
#define MORTERO_H

#include "arma.h"
#include <string>

class Mortero : public Arma
{
private:
public:
    Mortero(bool direccion, int angulo);
    Mortero(Mundo *mundo, b2Body *cuerpo);
    ~Mortero();

    void contacto_explosivo();

    int disparar(Mundo *mundo, b2Body *disparador) override;

    PosicionLanzable conseguir_posicion();
};

#endif
