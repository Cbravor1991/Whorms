#include "crosshair.h"
#include <cmath>

Crosshair::Crosshair(int radio) : radius(radio), angle(0), total_frames(31), animation_frame(0)
{

    for (int i = 0; i < (total_frames * 4) + 1; i++)
    {
        int x = (int)(i / 4);
        animation.push_back(x);
    }
}

void Crosshair::render(SDL2pp::Renderer &renderer, TextureManager &tex_manager, int worm_x, int worm_y, int worm_angle, int flip)
{

    std::string path_mira = "/sprites/crshairr.png";
    std::shared_ptr<SDL2pp::Texture> texture_mira = tex_manager.getTexture(path_mira);

    int src_x = 0, src_y = 0;
    src_y = 60 * animation.at(animation_frame);

    int crsh_x = 0, crsh_y = 0;

    float angle_radians = 0;
    if (flip == SDL_FLIP_NONE)
    {
        angle_radians = (180 + angle - worm_angle) * (M_PI / 180);
    }
    else
    {
        angle_radians = -(angle + worm_angle) * (M_PI / 180);
    }

    crsh_x = worm_x + (int)(radius * cos(angle_radians)) + 5;
    crsh_y = (int)(radius * sin(angle_radians)) - worm_y + 5;

    renderer.Copy(
        *texture_mira,
        SDL2pp::Rect(src_x, src_y, 60, 60),         
        SDL2pp::Rect(crsh_x, 200 + crsh_y, 40, 40), 
        0,                                          
        SDL2pp::NullOpt,                            
        SDL_FLIP_NONE                             
    );

    this->update_animation();
}

int Crosshair::recibir_angulo()
{
    return angle;
}

void Crosshair::aumentar_angulo()
{
    if (angle >= 90)
    {
        angle = 90;
        return;
    }
    this->angle += 5;
}

void Crosshair::disminuir_angulo()
{
    if (angle <= -90)
    {
        angle = -90;
        return;
    }
    this->angle -= 5;
}

void Crosshair::update_animation()
{
    this->animation_frame++;
    if (animation_frame > (total_frames * 4))
    { 
        this->animation_frame = 0;
    }
}
