#ifndef ARMA_H
#define ARMA_H

#include "objeto.h"

#include <string>

class Fragmento;

class Arma : public Objeto
{
protected:
    int danio;
    int radio;
    bool direccion;
    bool esperando_a_explotar = false;
    int tiempo_hasta_explotar = -1;
    float angulo = 0.0;
    float fuerza;
    int contactos = 0;
    RayCastWeaponExploded explosion;

public:
    Arma();
    virtual ~Arma();

    // Dispara un arma teledirigida
    virtual int disparar(Mundo *mundo, b2Body *disparador);

    virtual void mandar_fragmentos(int danio, int radio, int cantidad, int tipo);

    int cuenta_regresiva();

    virtual void explotar_regresiva();

    // Explota el arma
    virtual void explotar(const b2Vec2 &center);
};

#endif
