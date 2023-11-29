#ifndef SHOOT_POWER_H
#define SHOOT_POWER_H

#include <string>
#include "action.h"

class PowerShoot : public Action
{
private:
    int angulo;
    bool direccion;
    int potencia;

public:
    PowerShoot(int angulo, bool direccion, int potencia) : angulo(angulo), direccion(direccion), potencia(potencia) {}
    void mandar_accion(ProtocoloCliente &protocolo) override
    {
        protocolo.enviar_disparo_potente(angulo, direccion, potencia);
    }
};

#endif
