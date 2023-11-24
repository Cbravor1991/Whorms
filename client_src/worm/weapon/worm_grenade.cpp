#include "worm_grenade.h"

WormGreenGrenade::WormGreenGrenade(int ammo) : municion(INFINITE_AMMO) {}

void WormGreenGrenade::render(SDL2pp::Renderer& renderer, TextureManager& tex_manager, int x, int y, int flip, int angulo) 
{
    std::string path = "/sprites/Weapon/Worm/grenade/wgrnlnk.png";
    //ver de usar el sprite de apuntar
    std::shared_ptr<SDL2pp::Texture> texture = tex_manager.getTexture(path);

    int src_x = 0, src_y = 0; 
    src_y = 60 * 6;

    renderer.Copy(
            *texture,
            SDL2pp::Rect(src_x, src_y, 60, 60), // que parte del sprite queres que te cargue
            SDL2pp::Rect(x, 200 - y, 50, 50),   // la posicion en pantalla y el tamaño
            -angulo,                            // rotation
            SDL2pp::NullOpt,                    // rotation center - not needed
            flip                                //flip
        ); 
}

const int WormGreenGrenade::getWeapon() {

    return GREEN_GRENADE;
}

void WormGreenGrenade::increaseAngle() {
    mira.aumentar_angulo();
}
    
void WormGreenGrenade::decreaseAngle() {
    mira.disminuir_angulo();
}

int WormGreenGrenade::getAmmo() {
    return municion;
}
