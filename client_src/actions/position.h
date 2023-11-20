#ifndef POSITION_H_
#define POSITION_H_

#include <string>
#include "action.h"

class Position : public Action
{
private:
    int x;
    int y;

public:
    Position(int x, int y) : x(x), y(y) {}
    void mandar_accion(ProtocoloCliente &protocolo) override { protocolo.enviar_posicion(x, y); }
};

#endif