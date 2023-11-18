#ifndef JUMP_FOWARD_H_
#define JUMP_FOWARD_H_

#include <string>
#include "action.h"



class JumpFoward : public Action {


     

public:
     void mandar_accion(ProtocoloCliente& protocolo) override { protocolo.enviar_movimiento(MOVIMIENTO_ARRIBA_ADELANTE);}
};

#endif