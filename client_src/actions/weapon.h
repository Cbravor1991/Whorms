#ifndef WEAPON_H_
#define WEAPON_H_

#include <string>
#include "action.h"

const int ATAQUE_AEREO = 1;

class Weapon : public Action {

public:
    int x;
    int y;
    bool is_alive;  
    virtual void mandar_accion(ProtocoloCliente& protocolo){}
    virtual void render(SDL2pp::Renderer &renderer, TextureManager& tex_manager) {}
};

#endif