#ifndef PROVISIONDTO_H_
#define PROVISIONDTO_H_
#include <ostream>
#include <iostream>
#include <SDL2pp/SDL2pp.hh>
#include "../graphics/texture_manager.h"

class ProvisionDTO
{
private:
    int tipo;
    int x;
    int y;
    int angulo;

public:
    ProvisionDTO(int tipo, int x, int y, int angulo);

    void mostrar() const;

    void renderizar(SDL2pp::Renderer &renderer, TextureManager& tex_manager);
};

#endif // PROVISIONDTO_H_
