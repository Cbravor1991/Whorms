#ifndef POSICION_JUGADOR_H
#define POSICION_JUGADOR_H

#include "../server_protocol.h"

class PosicionJugador
{
private:
    int id;
    int x;
    int y;

public:
    PosicionJugador(int id, int x, int y) : id(id), x(x), y(y) {}

    void enviar_data(ProtocoloServer *protocolo) const
    {
        protocolo->enviar_jugador(id, x, y);
    }
};

#endif