#ifndef OBJETO_H_
#define OBJETO_H_
#include <ostream>
#include <iostream>
#include <SDL2pp/SDL2pp.hh>
#include "../graphics/texture_manager.h"

class Objeto
{
private:
    int tipo; // true es la larga false corta de 30
    int x;
    int y;
    int angulo;

public:
    Objeto(int tipo, int x, int y, int angulo);

    void mostrar() const;

    void renderizar(SDL2pp::Renderer &renderer, TextureManager& tex_manager);

    int getX() const;

    int getY() const;

    int getAngulo() const;

    int getTipo() const;

};

#endif // OBJETO_H_
