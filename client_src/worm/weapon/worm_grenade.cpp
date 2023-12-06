#include "worm_grenade.h"

WormGreenGrenade::WormGreenGrenade(int ammo) : mira(LONG_SIGHT), municion(INFINITE_AMMO), timer(5) {}

void WormGreenGrenade::render(SDL2pp::Renderer &renderer, TextureManager &tex_manager, int x, int y, int flip, int angulo)
{
    std::string path = "/sprites/Weapon/Worm/grenade/wgrnlnk.png";
    std::shared_ptr<SDL2pp::Texture> texture = tex_manager.getTexture(path);

    int src_x = 0, src_y = 0;
    src_y = 60 * 6;

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

Action *WormGreenGrenade::usar(int x, int y, bool direccion)
{
    int angulo = mira.recibir_angulo();
    int pot = potencia.obtenerPotencia();
    Action *accion = new TimedPowerShoot(angulo, direccion, pot, timer);
    potencia.resetearPotencia();
    return accion;
}

const int WormGreenGrenade::getWeapon()
{

    return GREEN_GRENADE;
}

void WormGreenGrenade::increaseAngle()
{
    mira.aumentar_angulo();
}

void WormGreenGrenade::decreaseAngle()
{
    mira.disminuir_angulo();
}

int WormGreenGrenade::getAmmo()
{
    return municion;
}

void WormGreenGrenade::setTimer(int segundos)
{
    timer = segundos;
}

int WormGreenGrenade::getTimer()
{
    return timer;
}

void WormGreenGrenade::increasePower()
{
    potencia.aumentarPotencia();
}

bool WormGreenGrenade::isMaxPower()
{
    return (potencia.obtenerPotencia() >= MAXIMA_POTENCIA);
}
