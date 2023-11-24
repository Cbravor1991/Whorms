#ifndef WORM_DYNAMITE_H
#define WORM_DYNAMITE_H
#include "worm_weapon.h"

class WormDynamite : public WormWeapon
{
    int municion;

public:
    explicit WormDynamite(int ammo);
    void render(SDL2pp::Renderer &renderer, TextureManager &tex_manager, int x, int y, int flip, int angulo);
    Action *usar(int x, int y, bool direccion);
    const int getWeapon();
    void increaseAngle();
    void decreaseAngle();
    int getAmmo();
    ~WormDynamite() {}
};

#endif
