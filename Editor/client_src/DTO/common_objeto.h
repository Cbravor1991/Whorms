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
    int id;

public:
    Objeto(int tipo, int x, int y, int angulo, int id);

    void mostrar() const;

    void renderizar(SDL2pp::Renderer &renderer, TextureManager& tex_manager, int id_objeto_seleccionado);

    int getX() const;

    int getY() const;

    int getAngulo() const;

    int getTipo() const;

};

#endif // OBJETO_H_
