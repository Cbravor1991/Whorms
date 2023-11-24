#include "worm_grenade_cluster.h"

WormClusterGrenade::WormClusterGrenade(int ammo) : municion(ammo) {}

void WormClusterGrenade::render(SDL2pp::Renderer& renderer, TextureManager& tex_manager, int x, int y, int flip, int angulo) 
{
    std::string path = "/sprites/Weapon/Worm/clusterGrenade/wclslnk.png";
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

const int WormClusterGrenade::getWeapon() {

    return CLUSTER_GRENADE;
}

void WormClusterGrenade::increaseAngle() {
    mira.aumentar_angulo();
}
    
void WormClusterGrenade::decreaseAngle() {
    mira.disminuir_angulo();
}

int WormClusterGrenade::getAmmo() {
    return municion;
}
