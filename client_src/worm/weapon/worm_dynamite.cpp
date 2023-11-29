#include "worm_dynamite.h"
WormDynamite::WormDynamite(int ammo) : municion(ammo), timer(5) {}

void WormDynamite::render(SDL2pp::Renderer &renderer, TextureManager &tex_manager, int x, int y, int flip, int angulo)
{
    std::string path = "/sprites/Weapon/Worm/dynamite/wdynlnk.png";
    std::shared_ptr<SDL2pp::Texture> texture = tex_manager.getTexture(path);

    int src_x = 0, src_y = 0;
    src_y = 60 * 8;

    renderer.Copy(
        *texture,
        SDL2pp::Rect(src_x, src_y, 60, 60), // que parte del sprite queres que te cargue
        SDL2pp::Rect(x, 200 - y, 50, 50),   // la posicion en pantalla y el tamaño
        -angulo,                            // rotation
        SDL2pp::NullOpt,                    // rotation center - not needed
        flip                                // flip
    );
}

Action *WormDynamite::usar(int x, int y, bool direccion)
{//aca hace falta cambiarlo? -> hay que enviar timer, pero no el angulo
    Action *accion = new TimedShoot(direccion, timer);
    //Action *accion = new Position(x, y);//hace falta la posicion? deberia ser como el bate, pero con timer y sin angulo
    return accion;
}

const int WormDynamite::getWeapon()
{

    return DYNAMITE;
}

void WormDynamite::increaseAngle() {}

void WormDynamite::decreaseAngle() {}

int WormDynamite::getAmmo()
{
    return municion;
}

void WormDynamite::setTimer(int segundos) 
{
    timer = segundos;
}

int WormDynamite::getTimer() 
{
    return timer;
}

void WormDynamite::increasePower() {}

bool WormDynamite::isMaxPower() 
{//como no tiene potencia, nunca llega a MAXIMA_POTENCIA
    return false;
}

