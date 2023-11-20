#include "common_ataque_aereo.h"

#include <SDL2pp/SDL2pp.hh>

AtaqueAereo::AtaqueAereo()
{
}

void AtaqueAereo::render(SDL2pp::Renderer &renderer, TextureManager &tex_manager)
{
    x = 100;
    y = 100;
    std::cout << "imprimi el valor" << this->y << '\n';

    std::vector<int> miVector;

    // Llenar el vector con valores desde 28 hasta 115

    std::string path = "/sprites/Weapon/Icons/airmisil.png";
    std::shared_ptr<SDL2pp::Texture> sprites = tex_manager.getTexture(path);

    int src_x = 0, src_y = 0; // by default, standing sprite
    if (is_alive)
    {
        src_y = 60 * run_phase;
    }
    renderer.Copy(
        *sprites,
        SDL2pp::Rect(src_x, src_y, 60, 60),              // que parte del spike queres que te cargue
        SDL2pp::Rect(this->x, 200 - this->y, 50, 50), 0, // la posicion en pantalla y el tamaño
        SDL2pp::NullOpt,                                 // rotation center - not needed
        SDL_FLIP_HORIZONTAL                              // vertical flip

    );
}
