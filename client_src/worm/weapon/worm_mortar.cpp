#include "worm_mortar.h"

WormMortar::WormMortar(int ammo) : municion(ammo) {}

void WormMortar::render(SDL2pp::Renderer &renderer, TextureManager &tex_manager, int x, int y, int flip, int angulo)
{
    std::string path = "/sprites/Weapon/Worm/bazooka/wbazlnk.png";
    // ver de usar el sprite de apuntar(mortero es misma animacion que bazooka, pero cambia disparo)
    std::shared_ptr<SDL2pp::Texture> texture = tex_manager.getTexture(path);

    int src_x = 0, src_y = 0;
    src_y = 60 * 6;

    renderer.Copy(
        *texture,
        SDL2pp::Rect(src_x, src_y, 60, 60), // que parte del sprite queres que te cargue
        SDL2pp::Rect(x, 200 - y, 50, 50),   // la posicion en pantalla y el tamaño
        -angulo,                            // rotation
        SDL2pp::NullOpt,                    // rotation center - not needed
        flip                                // flip
    );

    mira.render(renderer, tex_manager, x, y, angulo, flip);
}

Action *WormMortar::usar(int x, int y, bool direccion)
{
    int angulo = mira.recibir_angulo();
    Action *accion = new Shoot(angulo, direccion);
    return accion;
}

const int WormMortar::getWeapon()
{

    return MORTAR;
}

void WormMortar::increaseAngle()
{
    mira.aumentar_angulo();
}

void WormMortar::decreaseAngle()
{
    mira.disminuir_angulo();
}

int WormMortar::getAmmo()
{
    return municion;
}

void WormMortar::setTimer(int segundos) {}

int WormMortar::getTimer() 
{
    return 0;
}

void WormMortar::increasePower() 
{
    potencia++;
}
