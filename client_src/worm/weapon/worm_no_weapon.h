#ifndef WORM_NO_WEAPON_H
#define WORM_NO_WEAPON_H

#include "worm_weapon.h"

class WormNoWeapon : public WormWeapon
{

public:
    explicit WormNoWeapon(int ammo) {}
    void render(SDL2pp::Renderer &renderer, TextureManager &tex_manager, int x, int y, int flip, int angulo) {}
    Action *usar(int x, int y, bool direccion)
    {
        Action *accion = new Position(x, y);
        return accion;
    }
    const int getWeapon() { return NO_WEAPON; }
    void increaseAngle() {}
    void decreaseAngle() {}
    int getAmmo() { return 0; }
    void setTimer(int segundos) {}
    int getTimer() { return 0; }
    void increasePower() {}
    ~WormNoWeapon() {}
};

#endif