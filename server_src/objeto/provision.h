#ifndef PROVISION_H
#define PROVISION_H

#include "arma.h"

#include <string>

#define configuracion Configuracion::obtener_configuracion()

#define EXPLOTAR 0
#define CURAR 1

class Provision : public Arma
{
private:
    int danio = 20;
    int tipo;
    int x;
    int y;
    int angulo;
    std::array<int, 11> ammo;
    RayCastWeaponExploded explosion;

public:
    Provision(Mundo *mundo, int tipo, int x, int y);
    virtual ~Provision();

    void intentar_curar();

    PosicionLanzable conseguir_posicion();

    void cambiar_angulo_viga();

    void intentar_explotar();
};

#endif
