#ifndef VIGADTO_H_
#define VIGADTO_H_
#include <ostream>
#include <iostream>
#include <SDL2pp/SDL2pp.hh>
#include "../graphics/texture_manager.h"

class VigaDTO
{
private:
    bool tipo; // true es la larga false corta de 30
    int x;
    int y;
    int angulo;

public:
    VigaDTO(bool tipo, int x, int y, int angulo);

    void mostrar() const;

    void renderizar(SDL2pp::Renderer &renderer, TextureManager& tex_manager);
};

#endif // VIGADTO_H_
