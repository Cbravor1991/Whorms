#ifndef WORM_STATUS_H
#define WORM_STATUS_H

#include "../graphics/texture_manager.h"

const int IDLE = 0;
const int WALK = 1;

class WormStatus {
    //std::shared_ptr<SDL2pp::Texture> texture;
    
    public:

    WormStatus() {};
    virtual void render(SDL2pp::Renderer& renderer, TextureManager& tex_manager, int x, int y, int flip, int angulo) = 0;
    virtual const int getState() = 0;
    virtual void reset_animation() = 0;
    virtual void update_animation() = 0;

};

#endif
