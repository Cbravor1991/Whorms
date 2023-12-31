#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include "../../graphics/texture_manager.h"

#define SHORT_SIGHT 25
#define LONG_SIGHT 45

class Crosshair
{

private:
    int radius; // radio de la mira(circulo donde se mueve)
    int angle;  // angulo de la mira
    int total_frames;
    int animation_frame;
    std::vector<int> animation;

public:
    explicit Crosshair(int radio);

    void render(SDL2pp::Renderer &renderer, TextureManager &tex_manager, int worm_x, int worm_y, int worm_angle, int flip);

    void aumentar_angulo();
    void disminuir_angulo();
    int recibir_angulo();

    void update_animation();
};

#endif
