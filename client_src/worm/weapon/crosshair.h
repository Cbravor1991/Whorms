#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include "../../graphics/texture_manager.h"

class Crosshair {

    private:
    int radius;//radio de la mira(circulo donde se mueve)
    float angle;//angulo de la mira
    
    //animacion como la de walk
    int total_frames;
    int animation_frame;
    std::vector<int> animation;

    public:

    explicit Crosshair();

    void render(SDL2pp::Renderer& renderer, TextureManager& tex_manager, int worm_x, int worm_y, int worm_angle, int flag);

    void aumentar_angulo();
    void disminuir_angulo();

    void update_animation();
};

#endif
