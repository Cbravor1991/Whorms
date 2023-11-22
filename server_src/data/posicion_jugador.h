#ifndef POSICION_JUGADOR_H
#define POSICION_JUGADOR_H

#include "../server_protocol.h"
#include "posicion_objeto.h"

class PosicionJugador : public PosicionObjeto
{
private:
    int id;
    int id_gusano;
    int vida;
    bool en_movimiento;

public:
    PosicionJugador(int id, int id_gusano, int x, int y, int direccion, int angulo, int vida, bool en_movimiento) : PosicionObjeto(x, y, direccion, angulo), id(id), id_gusano(id_gusano), vida(vida), en_movimiento(en_movimiento) {}

    int recibir_altura() { return y; }

    void enviar_data(ProtocoloServer *protocolo) const
    {
        protocolo->enviar_jugador(id, id_gusano, x, y, direccion, angulo, vida, en_movimiento);
    }
};

#endif