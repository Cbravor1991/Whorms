#ifndef ARMA_H
#define ARMA_H

#include "objeto.h"
#include <string>

class Arma : public Objeto
{
protected:
    int damanio;
    int radio;
    bool waiting_to_explode;
    int tiempo_hasta_explotar;
    float angulo;
    float fuerza;

public:
    Arma();
    virtual ~Arma();

    // Dispara un arma teledirigida
    virtual int disparar(Mundo *mundo, b2Body *disparador, std::vector<Objeto *> *objetos);

    // Explota el arma
    // virtual void explode();
};

#endif
