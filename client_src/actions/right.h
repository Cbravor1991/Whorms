

#include <string>
#include "action.h"



class Right : public Action {


     

public:
    void mandar_accion(ProtocoloCliente& protocolo) override { protocolo.enviar_movimiento(MOVIMIENTO_DERECHA);}
};

