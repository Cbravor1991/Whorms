#ifndef GRANADA_SANTA_H
#define GRANADA_SANTA_H

#include "arma.h"
#include <string>

class GranadaSanta : public Arma
{
private:
public:
    GranadaSanta(bool direccion, int angulo, int segundos, int potencia);
    GranadaSanta(Mundo *mundo, b2Body *cuerpo, int segundos);
    ~GranadaSanta();

    int disparar(Mundo *mundo, b2Body *disparador) override;

    void contacto();

    void explotar_regresiva();

    PosicionLanzable conseguir_posicion();
};

#endif
