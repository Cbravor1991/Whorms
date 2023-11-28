#include "common_provisionDTO.h"

ProvisionDTO::ProvisionDTO(int tipo, int x, int y, int angulo) : tipo(tipo), x(x), y(y), angulo(angulo) {} // Declaración del constructor

void ProvisionDTO::mostrar() const { std::cout << "Provision tipo" << tipo << " en X: " << x << " Y: " << y << " Angulo:" << angulo << std::endl; }

void ProvisionDTO::renderizar(SDL2pp::Renderer &renderer, TextureManager& tex_manager)
{   
    std::string path = "/sprites/misc/crates/wcrate0.png";
    std::shared_ptr<SDL2pp::Texture> texture = tex_manager.getTexture(path);

    int src_x = 0, src_y = 0;
    src_y = 60 * 9;

    renderer.Copy(
        *texture,
        SDL2pp::Rect(src_x, src_y, 60, 60), // que parte del sprite queres que te cargue
        SDL2pp::Rect(x, 200 - y, 40, 40),   // la posicion en pantalla y el tamaño
        -angulo,                            // rotation
        SDL2pp::NullOpt,                    // rotation center - not needed
        SDL_FLIP_NONE                       // flip
    );

}
