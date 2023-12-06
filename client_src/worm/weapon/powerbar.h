#ifndef POWERBAR_H
#define POWERBAR_H

#include <vector>
#include "../../graphics/texture_manager.h"

const int MAXIMA_POTENCIA = 12;

class PowerBar {
    int potencia;
    bool renderizar;
    public:
    explicit PowerBar();
    void aumentarPotencia();
    int obtenerPotencia();
    void resetearPotencia();
    void render(SDL2pp::Renderer &renderer, TextureManager &tex_manager, int worm_x, int worm_y, int worm_angle, int sight_angle, int flip);

};

#endif
