#include "worm_bat.h"
#include "../../actions/shoot.h"

WormBat::WormBat(int ammo) : mira(SHORT_SIGHT), municion(INFINITE_AMMO) {}

void WormBat::render(SDL2pp::Renderer &renderer, TextureManager &tex_manager, int x, int y, int flip, int angulo)
{
    std::string path = "/sprites/Weapon/Worm/bat/wbsblnk.png";
    std::shared_ptr<SDL2pp::Texture> texture = tex_manager.getTexture(path);

    int src_x = 0, src_y = 0;
    src_y = 60 * 8;

    renderer.Copy(
        *texture,
        SDL2pp::Rect(src_x, src_y, 60, 60), 
        SDL2pp::Rect(x, 200 - y, 50, 50),   
        -angulo,                            
        SDL2pp::NullOpt,                    
        flip                               
    );

    mira.render(renderer, tex_manager, x, y, angulo, flip);
}

Action *WormBat::usar(int x, int y, bool direccion)
{
    int angulo = mira.recibir_angulo();
    Action *accion = new Shoot(angulo, direccion);
    return accion;
}

const int WormBat::getWeapon()
{

    return BAT;
}

void WormBat::increaseAngle()
{
    mira.aumentar_angulo();
}

void WormBat::decreaseAngle()
{
    mira.disminuir_angulo();
}

int WormBat::getAmmo()
{
    return municion;
}

void WormBat::setTimer(int segundos) {}

int WormBat::getTimer() 
{
    return 0;
}

void WormBat::increasePower() {}

bool WormBat::isMaxPower() 
{
    return false;
}

