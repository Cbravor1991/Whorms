
#include "common_vigaDTO.h"
VigaDTO::VigaDTO(bool tipo, int x, int y, int angulo) : tipo(tipo), x(x), y(y), angulo(angulo) {} // Declaración del constructor

void VigaDTO::mostrar() const { std::cout << "Viga tipo" << tipo << " en X: " << x << " Y: " << y << " Angulo:" << angulo << std::endl; }

void VigaDTO::renderizar(SDL2pp::Renderer &renderer)
{
    if (tipo)
    {
        SDL2pp::Texture sprites(renderer, SDL2pp::Surface(DATA_PATH "/sprites/vigas/grdl4.png"));
        renderer.Copy(
            sprites,
            SDL2pp::Rect(0, 0, 140, 20),           // que parte del spike queres que te cargue
            SDL2pp::Rect(x + 20, 220 - y, 60, 12), // la posicion en pantalla y el tamaño
            0.0,                                   // don't rotate
            SDL2pp::NullOpt,                       // rotation center - not needed
            SDL_FLIP_HORIZONTAL                    // vertical flip
        );
    }

    else
    {
        SDL2pp::Texture sprites(renderer, SDL2pp::Surface(DATA_PATH "/sprites/vigas/grds4.png"));
        renderer.Copy(
            sprites,
            SDL2pp::Rect(0, 0, 70, 20),            // que parte del spike queres que te cargue
            SDL2pp::Rect(x + 20, 220 - y, 30, 12), // la posicion en pantalla y el tamaño
            0.0,                                   // don't rotate
            SDL2pp::NullOpt,                       // rotation center - not needed
            SDL_FLIP_HORIZONTAL                    // vertical flip
        );
    }
}
