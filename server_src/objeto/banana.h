#ifndef BANANA_H
#define BANANA_H

#include "arma.h"
#include <string>

class Banana : public Arma
{
private:
public:
    Banana(bool direccion, int angulo, int segundos, int potencia);
    Banana(Mundo *mundo, b2Body *cuerpo, int segundos);
    ~Banana();

    int disparar(Mundo *mundo, b2Body *disparador) override;

    void contacto();

    void explotar_regresiva();

    PosicionLanzable conseguir_posicion();
};

#endif
