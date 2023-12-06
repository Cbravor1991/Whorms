#include "worm_mortar.h"

WormMortar::WormMortar(int ammo) : mira(LONG_SIGHT), municion(ammo) {}

void WormMortar::render(SDL2pp::Renderer &renderer, TextureManager &tex_manager, int x, int y, int flip, int angulo)
{
    std::string path = "/sprites/Weapon/Worm/mortar/wbaz2.png";
    std::shared_ptr<SDL2pp::Texture> texture = tex_manager.getTexture(path);

    int src_x = 0, src_y = 0;
    src_y = 60 * 16;

    renderer.Copy(
        *texture,
        SDL2pp::Rect(src_x, src_y, 60, 60),
        SDL2pp::Rect(x, 200 - y, 50, 50),   
        -angulo,                            
        SDL2pp::NullOpt,                    
        flip                                
    );
    if (municion != 0)
    {
        potencia.render(renderer, tex_manager, x, y, angulo, mira.recibir_angulo(), flip);
        mira.render(renderer, tex_manager, x, y, angulo, flip);
    }
}

Action *WormMortar::usar(int x, int y, bool direccion)
{
    int angulo = mira.recibir_angulo();
    int pot = potencia.obtenerPotencia();
    Action *accion = new PowerShoot(angulo, direccion, pot);
    potencia.resetearPotencia();
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
    potencia.aumentarPotencia();
}

bool WormMortar::isMaxPower()
{
    return (potencia.obtenerPotencia() >= MAXIMA_POTENCIA);
}
