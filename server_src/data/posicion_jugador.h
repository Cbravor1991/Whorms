#ifndef POSICION_JUGADOR_H
#define POSICION_JUGADOR_H

#include "../server_protocol.h"

class PosicionJugador
{
private:
    int id;
    int x;
    int y;
    int direccion;
    int angulo;

public:
    PosicionJugador(int id, int x, int y, int direccion, int angulo) : id(id), x(x), y(y), direccion(direccion), angulo(angulo) {}

    int recibir_altura() { return y; }

    void enviar_data(ProtocoloServer *protocolo) const
    {
        protocolo->enviar_jugador(id, x, y, direccion, angulo);
    }
};

#endif