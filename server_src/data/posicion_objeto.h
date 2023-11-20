#ifndef POSICION_OBJETO_H
#define POSICION_OBJETO_H

#include "../server_protocol.h"

class PosicionObjeto
{
protected:
    int x;
    int y;
    int direccion;
    int angulo;

public:
    PosicionObjeto(int x, int y, int direccion, int angulo) : x(x), y(y), direccion(direccion), angulo(angulo) {}

    int recibir_altura() { return y; }

    virtual void enviar_data(ProtocoloServer *protocolo) const
    {
    }
};

#endif