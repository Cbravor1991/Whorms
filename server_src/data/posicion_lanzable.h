#ifndef POSICION_LANZABLE_H
#define POSICION_LANZABLE_H

#include "../server_protocol.h"
#include "posicion_objeto.h"

class PosicionLanzable : public PosicionObjeto
{
private:
    int tipo;
    bool explosion;

public:
    PosicionLanzable() : PosicionObjeto(0, 0, 0, 0), tipo(0) {}
    PosicionLanzable(int tipo, int x, int y, int direccion, int angulo, bool explosion) : PosicionObjeto(x, y, direccion, angulo), tipo(tipo), explosion(explosion) {}

    int recibir_altura() { return y; }

    void enviar_data(ProtocoloServer *protocolo) const
    {
        protocolo->enviar_lanzable(tipo, x, y, direccion, angulo, explosion);
    }
};

#endif