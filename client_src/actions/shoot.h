#ifndef SHOOT_H
#define SHOOT_H

#include <string>
#include "action.h"

class Shoot : public Action
{
private:
    int angulo;
    bool direccion;

public:
    Shoot(int angulo, bool direccion) : angulo(angulo), direccion(direccion) {}
    void mandar_accion(ProtocoloCliente &protocolo) override
    {
        protocolo.enviar_disparo(angulo, direccion);
    }
};

#endif