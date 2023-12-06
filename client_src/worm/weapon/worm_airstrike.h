#ifndef WORM_AIRSTRIKE_H
#define WORM_AIRSTRIKE_H

#include "worm_weapon.h"
class WormAirstike : public WormWeapon
{
private:
    int municion;

public:
    explicit WormAirstike(int ammo);
    void render(SDL2pp::Renderer &renderer, TextureManager &tex_manager, int x, int y, int flip, int angulo);
    Action *usar(int x, int y, bool direccion);
    const int getWeapon();
    void increaseAngle();
    void decreaseAngle();
    int getAmmo();
    void setTimer(int segundos);
    int getTimer();
    void increasePower();
    bool isMaxPower();
    ~WormAirstike() {}
};

#endif
