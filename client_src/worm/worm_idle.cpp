#include "worm_idle.h"

WormIdle::WormIdle(): animation_frame(0), total_frames(0) {}

void WormIdle::render(SDL2pp::Renderer& renderer, TextureManager& tex_manager, int x, int y, int flip, int angulo) 
{
    std::string path = "/sprites/worm/walk/wwalk.png";
    std::shared_ptr<SDL2pp::Texture> texture = tex_manager.getTexture(path);

    int src_x = 0, src_y = 0;

    renderer.Copy(
            *texture,
            SDL2pp::Rect(src_x, src_y, 60, 60), 
            SDL2pp::Rect(x, 200 - y, 50, 50),   
            -angulo,                            
            SDL2pp::NullOpt,                    
            flip                               
        );    
}

const int WormIdle::getState() {
    return IDLE;
}

void WormIdle::reset_animation() {
    animation_frame = 0;
}

void WormIdle::update_animation() {
    return;
}



    