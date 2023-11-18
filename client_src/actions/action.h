#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include "../client_protocol.h"

const int MOVIMIENTO_IZQUIERDA = 1;
const int MOVIMIENTO_DERECHA = 2;
const int MOVIMIENTO_ARRIBA_ADELANTE = 3;
const int MOVIMIENTO_ARRIBA_ATRAS = 4;

class Action {

public:
    Action() {}
    virtual void mandar_accion(ProtocoloCliente& protocolo){}
    virtual ~Action() {}
};

#endif