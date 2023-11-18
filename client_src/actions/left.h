#ifndef LEFT_H_
#define LEFT_H_

#include <string>
#include "action.h"



class Left : public Action {


     

public:
     void mandar_accion(ProtocoloCliente& protocolo) override { protocolo.enviar_movimiento(MOVIMIENTO_IZQUIERDA);}
};

#endif