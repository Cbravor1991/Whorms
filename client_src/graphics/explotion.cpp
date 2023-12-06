#include "explotion.h"

Explotion::Explotion(int pos_x, int pos_y): x(pos_x), y(pos_y), fin(false) {}

void Explotion::renderizar(SDL2pp::Renderer& renderer, TextureManager& tex_manager) {

    std::shared_ptr<SDL2pp::Texture> circle =  tex_manager.getTexture("/Effects/explosion/circle50.png");
    std::shared_ptr<SDL2pp::Texture> elipse =  tex_manager.getTexture("/Effects/explosion/elipse75.png");
    std::shared_ptr<SDL2pp::Texture> pow =  tex_manager.getTexture("/Effects/explosion/expow.png");

    int src_x = 0;
    int src_y_circ = cant_iteraciones * 100;
    int src_y_elip = cant_iteraciones * 224;
    int src_y_pow = cant_iteraciones * 60;

    renderer.Copy(
        *circle,
        SDL2pp::Rect(src_x, src_y_circ, 100, 100),
        SDL2pp::Rect(x+10, 200 - y, 40, 40),  
        0,                            
        SDL2pp::NullOpt,                    
        SDL_FLIP_NONE                               
    );

    renderer.Copy(
        *elipse,
        SDL2pp::Rect(src_x, src_y_elip, 224, 224), 
        SDL2pp::Rect(x+10, 200 - y, 40, 40),   
        0,                            
        SDL2pp::NullOpt,                   
        SDL_FLIP_NONE                              
    );

    renderer.Copy(
        *pow,
        SDL2pp::Rect(src_x, src_y_pow, 60, 60),
        SDL2pp::Rect(x+15, 200 - y, 30, 40),   
        0,                            
        SDL2pp::NullOpt,                    
        SDL_FLIP_NONE                               
    );


    cant_iteraciones++;
    if(cant_iteraciones >= 8 ) {
        this->fin = true;
    }
    
}

bool Explotion::finalizo() {
    return this->fin;
}