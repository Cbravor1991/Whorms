#include "worm_bat.h"

WormBat::WormBat(int ammo) : municion(INFINITE_AMMO) {}

void WormBat::render(SDL2pp::Renderer& renderer, TextureManager& tex_manager, int x, int y, int flip, int angulo) 
{
    std::string path = "/sprites/Weapon/Worm/bat/wbsblnk.png";
    //ver de usar el sprite de apuntar
    std::shared_ptr<SDL2pp::Texture> texture = tex_manager.getTexture(path);

    int src_x = 0, src_y = 0; 
    src_y = 60 * 8;

    renderer.Copy(
            *texture,
            SDL2pp::Rect(src_x, src_y, 60, 60), // que parte del sprite queres que te cargue
            SDL2pp::Rect(x, 200 - y, 50, 50),   // la posicion en pantalla y el tamaño
            -angulo,                            // rotation
            SDL2pp::NullOpt,                    // rotation center - not needed
            flip                                //flip
        ); 
    
    mira.render(renderer, tex_manager, x, y, angulo, flip);
}

const int WormBat::getWeapon() {

    return BAT;
}

void WormBat::increaseAngle() {
    mira.aumentar_angulo();
}
    
void WormBat::decreaseAngle() {
    mira.disminuir_angulo();
}

int WormBat::getAmmo() {
    return municion;
}
