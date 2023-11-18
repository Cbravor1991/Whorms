#ifndef WEAPON_H_
#define WEAPON_H_

#include <string>
#include "action.h"

const int ATAQUE_AEREO = 1;

class Weapon : public Action {

public:
    virtual void mandar_accion(ProtocoloCliente& protocolo){}
};

#endif