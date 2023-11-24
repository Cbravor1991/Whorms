#include "worm_grenade_holy.h"

WormHolyGrenade::WormHolyGrenade(int ammo) : municion(ammo) {}

void WormHolyGrenade::render(SDL2pp::Renderer& renderer, TextureManager& tex_manager, int x, int y, int flip, int angulo) 
{
    std::string path = "/sprites/Weapon/Worm/holyGrenade/whgrlnk.png";
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

const int WormHolyGrenade::getWeapon() {

    return HOLY_GRENADE;
}

void WormHolyGrenade::increaseAngle() {
    mira.aumentar_angulo();
}
    
void WormHolyGrenade::decreaseAngle() {
    mira.disminuir_angulo();
}

int WormHolyGrenade::getAmmo() {
    return municion;
}
