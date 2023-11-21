#ifndef WORM_WEAPON_H
#define WORM_WEAPON_H

#include "../../graphics/texture_manager.h"

const int NO_WEAPON = 0;
const int AIR_STRIKE = 1;
const int TELEPORT = 2;

class WormWeapon {
    //std::shared_ptr<SDL2pp::Texture> texture;
    
    public:

    WormWeapon() {};
    virtual void render(SDL2pp::Renderer& renderer, TextureManager& tex_manager, int x, int y, int flip, int angulo) = 0;
    virtual const int getWeapon() = 0;

    virtual ~WormWeapon() {}

};

#endif