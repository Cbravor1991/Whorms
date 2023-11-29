#ifndef SHOOT_TIMER_H
#define SHOOT_TIMER_H

#include <string>
#include "action.h"

class TimedShoot : public Action
{
private:
    bool direccion;
    int timer;

public:
    TimedShoot(bool direccion, int timer) : direccion(direccion), timer(timer) {}
    void mandar_accion(ProtocoloCliente &protocolo) override
    {
        protocolo.enviar_disparo_timeado(direccion, timer);
    }
};

#endif