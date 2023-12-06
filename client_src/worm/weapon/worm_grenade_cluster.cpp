#include "worm_grenade_cluster.h"

WormClusterGrenade::WormClusterGrenade(int ammo) : mira(LONG_SIGHT), municion(ammo), timer(5) {}

void WormClusterGrenade::render(SDL2pp::Renderer &renderer, TextureManager &tex_manager, int x, int y, int flip, int angulo)
{
    std::string path = "/sprites/Weapon/Worm/clusterGrenade/wclslnk.png";
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

Action *WormClusterGrenade::usar(int x, int y, bool direccion)
{
    int angulo = mira.recibir_angulo();
    int pot = potencia.obtenerPotencia();
    Action *accion = new TimedPowerShoot(angulo, direccion, pot, timer);
    potencia.resetearPotencia();
    return accion;
}

const int WormClusterGrenade::getWeapon()
{

    return CLUSTER_GRENADE;
}

void WormClusterGrenade::increaseAngle()
{
    mira.aumentar_angulo();
}

void WormClusterGrenade::decreaseAngle()
{
    mira.disminuir_angulo();
}

int WormClusterGrenade::getAmmo()
{
    return municion;
}

void WormClusterGrenade::setTimer(int segundos)
{
    timer = segundos;
}

int WormClusterGrenade::getTimer()
{
    return timer;
}

void WormClusterGrenade::increasePower()
{
    potencia.aumentarPotencia();
}

bool WormClusterGrenade::isMaxPower()
{
    return (potencia.obtenerPotencia() >= MAXIMA_POTENCIA);
}
