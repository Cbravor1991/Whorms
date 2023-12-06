#include "worm_banana.h"

WormBanana::WormBanana(int ammo) : mira(LONG_SIGHT), municion(ammo), timer(5) {}

void WormBanana::render(SDL2pp::Renderer &renderer, TextureManager &tex_manager, int x, int y, int flip, int angulo)
{
    std::string path = "/sprites/Weapon/Worm/banana/wbanlnk.png";
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

Action *WormBanana::usar(int x, int y, bool direccion)
{
    int angulo = mira.recibir_angulo();
    int pot = potencia.obtenerPotencia();
    Action *accion = new TimedPowerShoot(angulo, direccion, pot, timer);
    potencia.resetearPotencia();
    return accion;
}

const int WormBanana::getWeapon()
{
    return BANANA;
}

void WormBanana::increaseAngle()
{
    mira.aumentar_angulo();
}

void WormBanana::decreaseAngle()
{
    mira.disminuir_angulo();
}

int WormBanana::getAmmo()
{
    return municion;
}

void WormBanana::setTimer(int segundos)
{
    timer = segundos;
}

int WormBanana::getTimer()
{
    return timer;
}

void WormBanana::increasePower()
{
    potencia.aumentarPotencia();
}

bool WormBanana::isMaxPower()
{ 
    return (potencia.obtenerPotencia() >= MAXIMA_POTENCIA);
}
