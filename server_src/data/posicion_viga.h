#ifndef POSICION_VIGA_H
#define POSICION_VIGA_H

#include "../server_protocol.h"

class PosicionViga
{
private:
    bool tipo;
    int x;
    int y;

public:
    PosicionViga(bool tipo, int x, int y) : tipo(tipo), x(x), y(y) {}

    void enviar_data(ProtocoloServer *protocolo) const
    {
        protocolo->enviar_viga(tipo, x, y);
    }
};

#endif