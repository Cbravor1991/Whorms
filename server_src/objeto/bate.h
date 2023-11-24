#ifndef BATE_H
#define BATE_H

#include "arma.h"
#include <string>

class Bate : public Arma
{
private:
    void empujar(const b2Vec2 &center);

public:
    Bate(bool direccion, int angulo);
    ~Bate();
    int disparar(Mundo *mundo, b2Body *disparador, std::vector<Objeto *> *objetos) override;
    PosicionLanzable conseguir_posicion();
};

#endif
