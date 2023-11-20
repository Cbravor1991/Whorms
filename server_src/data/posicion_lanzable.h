#ifndef POSICION_LANZABLE_H
#define POSICION_LANZABLE_H

#include "../server_protocol.h"
#include "posicion_objeto.h"

class PosicionLanzable : public PosicionObjeto
{
private:
    int tipo_bomba;
    bool explosion;

public:
    PosicionLanzable() : PosicionObjeto(0, 0, 0, 0), tipo_bomba(0) {}
    PosicionLanzable(int tipo_bomba, int x, int y, int direccion, int angulo, bool explosion) : PosicionObjeto(x, y, direccion, angulo), tipo_bomba(tipo_bomba), explosion(explosion) {}

    int recibir_altura() { return y; }

    void enviar_data(ProtocoloServer *protocolo) const
    {
        protocolo->enviar_lanzable(tipo_bomba, x, y, direccion, angulo, explosion);
    }
};

#endif