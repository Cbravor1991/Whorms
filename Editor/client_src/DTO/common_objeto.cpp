
#include "common_objeto.h"

Objeto::Objeto(int tipo, int x, int y, int angulo) : tipo(tipo), x(x), y(y), angulo(angulo) {} // Declaración del constructor

void Objeto::mostrar() const { std::cout << "Viga tipo" << tipo << " en X: " << x << " Y: " << y << " Angulo:" << angulo << std::endl; }

void Objeto::renderizar(SDL2pp::Renderer &renderer, TextureManager& tex_manager)
{   
    int ancho_sprite;
    int ancho_textura;
    std::shared_ptr<SDL2pp::Texture> sprites;

    if (tipo == 1 || tipo == 0)
    {  
        if (tipo == 1) {
            std::string path = "/sprites/vigas/grdl4.png";
            sprites = tex_manager.getTexture(path);
            ancho_sprite = 140;
            ancho_textura = 62;//60
        } else {
            std::string path = "/sprites/vigas/grds4.png";
            sprites = tex_manager.getTexture(path);
            ancho_sprite = 70;
            ancho_textura = 32;//30
        }
        renderer.Copy(
                *sprites,
                SDL2pp::Rect(0, 0, ancho_sprite, 20),             // que parte del spike queres que te cargue
                SDL2pp::Rect(x + 20, 220 - y, ancho_textura, 12), // la posicion en pantalla y el tamaño
                -angulo,                                          // grados que roto, en sentido horario
                SDL2pp::NullOpt,                                  // rotation center - not needed
                SDL_FLIP_HORIZONTAL                               // vertical flip
            );
    }
    else if (tipo == 2)
    {   
        std::string path = "/sprites/worm/walk/wwalk.png";
        std::shared_ptr<SDL2pp::Texture> texture = tex_manager.getTexture(path);
        renderer.Copy(
            *texture,
            SDL2pp::Rect(0, 0, 60, 60), // que parte del sprite queres que te cargue
            SDL2pp::Rect(x, 200 - y, 50, 50),   // la posicion en pantalla y el tamaño
            -angulo,                            // don't rotate
            SDL2pp::NullOpt,                    // rotation center - not needed
            SDL_FLIP_HORIZONTAL                                // vertical flip
        );
    }
}

int Objeto::getX() const
{
    return x;
}

int Objeto::getY() const
{
    return y;
}

int Objeto::getAngulo() const
{
    return angulo;
}

int Objeto::getTipo() const
{
    return tipo;
}