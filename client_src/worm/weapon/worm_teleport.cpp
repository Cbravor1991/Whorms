#include "worm_teleport.h"
#include "../../actions/position.h"

WormTeleport::WormTeleport(int ammo) : municion(INFINITE_AMMO) {}

void WormTeleport::render(SDL2pp::Renderer &renderer, TextureManager &tex_manager, int x, int y, int flip, int angulo)
{
    std::string path = "/sprites/Weapon/Worm/teleport/wtellnk.png";
    std::shared_ptr<SDL2pp::Texture> texture = tex_manager.getTexture(path);

    int src_x = 0, src_y = 0;
    src_y = 60 * 9;

    renderer.Copy(
        *texture,
        SDL2pp::Rect(src_x, src_y, 60, 60), 
        SDL2pp::Rect(x, 200 - y, 50, 50),  
        -angulo,                           
        SDL2pp::NullOpt,                   
        flip                                
    );
}

Action *WormTeleport::usar(int x, int y, bool direccion)
{
    Action *accion = new Position(x, y);
    return accion;
}

const int WormTeleport::getWeapon()
{

    return TELEPORT;
}

void WormTeleport::increaseAngle() {}

void WormTeleport::decreaseAngle() {}

int WormTeleport::getAmmo()
{
    return municion;
}

void WormTeleport::setTimer(int segundos) {}

int WormTeleport::getTimer() 
{
    return 0;
}

void WormTeleport::increasePower() {}

bool WormTeleport::isMaxPower() 
{
    return false;
}

