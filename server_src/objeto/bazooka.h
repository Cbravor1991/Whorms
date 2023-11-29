#ifndef BAZOOKA_H
#define BAZOOKA_H

#include "arma.h"
#include <string>

class Bazooka : public Arma
{
private:
public:
    Bazooka(bool direccion, int angulo, int potencia);
    Bazooka(Mundo *mundo, b2Body *cuerpo);
    ~Bazooka();

    void contacto_explosivo();

    int disparar(Mundo *mundo, b2Body *disparador) override;

    PosicionLanzable conseguir_posicion();
};

#endif
