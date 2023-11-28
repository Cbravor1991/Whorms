#ifndef POWERBAR_H
#define POWERBAR_H

#include <vector>
#include "../../graphics/texture_manager.h"

const int MAXIMA_POTENCIA = 12;

class PowerBar {
    int potencia;
    bool renderizar;
    // animacion como la de walk
    //std::vector<int> animation;
    public:
    explicit PowerBar();
    void aumentarPotencia();
    int obtenerPotencia();
    void resetearPotencia();
    //agrego el angulo de la mira?
    void render(SDL2pp::Renderer &renderer, TextureManager &tex_manager, int worm_x, int worm_y, int worm_angle, int sight_angle, int flip);

};

#endif
