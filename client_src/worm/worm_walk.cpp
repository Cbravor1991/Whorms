#include "worm_walk.h"

#include <iostream>
#include <algorithm>
WormWalk::WormWalk(): animation_frame(0), total_frames(13) 
{

    for(int i=0; i < (total_frames*6)+1; i++){
        int x = (int) (i/6);
        animation.push_back(x);
    }

}


void WormWalk::render(SDL2pp::Renderer& renderer, TextureManager& tex_manager, int x, int y, int flip, int angulo) {

    std::string path = "/sprites/worm/walk/wwalk.png";
    std::shared_ptr<SDL2pp::Texture> texture = tex_manager.getTexture(path);

    int src_x = 0, src_y = 0; 
    src_y = 60 * animation.at(animation_frame); 

    
    renderer.Copy(
        *texture,
        SDL2pp::Rect(src_x, src_y, 60, 60), // que parte del sprite queres que te cargue
        SDL2pp::Rect(x, 200 - y, 50, 50),   // la posicion en pantalla y el tamaño
        -angulo,                            // don't rotate
        SDL2pp::NullOpt,                    // rotation center - not needed
        flip                                // vertical flip
    );
    
}

const int WormWalk::getState() {
    return WALK;
}


void WormWalk::reset_animation() {
    animation_frame = 0;
}

void WormWalk::update_animation() {

    this->animation_frame++;
    if(animation_frame > (total_frames * 6)) {//esto es porque renderiza cada 6 veces
        this->reset_animation();
    }
}