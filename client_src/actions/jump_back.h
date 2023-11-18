#ifndef JUMP_BACK_H_
#define JUMP_BACK_H_

#include <string>
#include "action.h"






class JumpBack : public Action {


     

public:
     void mandar_accion(ProtocoloCliente& protocolo) override { protocolo.enviar_movimiento(MOVIMIENTO_ARRIBA_ATRAS);}
};

#endif