#ifndef SHOOT_POWER_TIMER_H
#define SHOOT_POWER_TIMER_H

#include <string>
#include "action.h"

class TimedPowerShoot : public Action
{
private:
    int angulo;
    bool direccion;
    int potencia;
    int timer;
    
public:
    TimedPowerShoot(int angulo, bool direccion, int potencia, int timer) : angulo(angulo), direccion(direccion), potencia(potencia), timer(timer) {}
    void mandar_accion(ProtocoloCliente &protocolo) override
    {
        protocolo.enviar_disparo_potente_timeado(angulo, direccion, potencia, timer);
    }
};

#endif