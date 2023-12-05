
#include "common_objeto.h"

Objeto::Objeto(int tipo, int x, int y, int angulo, int id) : tipo(tipo), x(x), y(y), angulo(angulo), id(id) {} // Declaración del constructor

void Objeto::renderizar(SDL2pp::Renderer &renderer, TextureManager& tex_manager, int id_objeto_seleccionado)
{   
    int ancho_sprite;
    int ancho_textura;
    std::shared_ptr<SDL2pp::Texture> sprites;
    std::string path;

    if (tipo == 1 || tipo == 0)
    {  
        if (tipo == 1) {
            if (id == id_objeto_seleccionado) {
               path = "/sprites/vigal_borrar.png";
            } else {
                path = "/sprites/vigas/grdl4.png";
            }
            sprites = tex_manager.getTexture(path);
            ancho_sprite = 140;
            ancho_textura = 62;
        } else {
            if (id == id_objeto_seleccionado) {
               path = "/sprites/vigas_borrar.png";
            } else {
                path = "/sprites/vigas/grds4.png";
            }
            sprites = tex_manager.getTexture(path);
            ancho_sprite = 70;
            ancho_textura = 32;
        }
        renderer.Copy(
                *sprites,
                SDL2pp::Rect(0, 0, ancho_sprite, 20),             
                SDL2pp::Rect(x + 20, 220 - y, ancho_textura, 12), 
                -angulo,                                         
                SDL2pp::NullOpt,                                 
                SDL_FLIP_HORIZONTAL                               
            );
    }
    else if (tipo == 2)
    {   
        if (id == id_objeto_seleccionado) {
            path = "/sprites/gusano_borrar_1.png";
        } else {
            path = "/sprites/worm/walk/wwalk.png";
        }
        std::shared_ptr<SDL2pp::Texture> texture = tex_manager.getTexture(path);
        renderer.Copy(
            *texture,
            SDL2pp::Rect(0, 0, 60, 60), 
            SDL2pp::Rect(x, 200 - y, 50, 50),
            -angulo,                            
            SDL2pp::NullOpt,                   
            SDL_FLIP_HORIZONTAL                               
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

int Objeto::getId() const
{
    return id;
}