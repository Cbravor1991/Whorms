#ifndef GRANADA_ROJA_H
#define GRANADA_ROJA_H

#include "arma.h"
#include <string>

class GranadaRoja : public Arma
{
private:
public:
    GranadaRoja(bool direccion, int angulo, int segundos, int potencia);
    GranadaRoja(Mundo *mundo, b2Body *cuerpo, int segundos);
    ~GranadaRoja();

    int disparar(Mundo *mundo, b2Body *disparador) override;

    void contacto();

    void explotar_regresiva();

    PosicionLanzable conseguir_posicion();
};

#endif
