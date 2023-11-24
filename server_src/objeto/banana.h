#ifndef BANANA_H
#define BANANA_H

#include "arma.h"
#include <string>

class Banana : public Arma
{
private:
public:
    Banana(bool direccion, int angulo);
    Banana(Mundo *mundo, b2Body* cuerpo);
    ~Banana();

    int disparar(Mundo *mundo, b2Body *disparador, std::vector<Objeto *> *objetos) override;

    PosicionLanzable conseguir_posicion();
};

#endif
