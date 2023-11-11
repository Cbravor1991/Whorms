
#include "common_vigaDTO.h"
VigaDTO::VigaDTO(bool tipo, int x, int y, int angulo) : tipo(tipo), x(x), y(y), angulo(angulo) {} // Declaración del constructor

void VigaDTO::mostrar() const { std::cout << "Viga tipo" << tipo << " en X: " << x << " Y: " << y << " Angulo:" << angulo << std::endl; }

void VigaDTO::renderizar(SDL2pp::Renderer &renderer, TextureManager& tex_manager)
{   

    int ancho_sprite;
    int ancho_textura;
    std::shared_ptr<SDL2pp::Texture> sprites;
    if (tipo)
    {   
        std::string path = "/sprites/vigas/grdl4.png";
        sprites = tex_manager.getTexture(path);
        ancho_sprite = 140;
        ancho_textura = 60;
    }

    else
    {   
        std::string path = "/sprites/vigas/grds4.png";
        sprites = tex_manager.getTexture(path);
        ancho_sprite = 70;
        ancho_textura = 30;
        
    }

    renderer.Copy(
            *sprites,
            SDL2pp::Rect(0, 0, ancho_sprite, 20),             // que parte del spike queres que te cargue
            SDL2pp::Rect(x + 20, 220 - y, ancho_textura, 12), // la posicion en pantalla y el tamaño
            0.0,                                              // don't rotate
            SDL2pp::NullOpt,                                  // rotation center - not needed
            SDL_FLIP_HORIZONTAL                               // vertical flip
        );
}
