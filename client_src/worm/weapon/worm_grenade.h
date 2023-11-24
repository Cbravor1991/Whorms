#ifndef WORM_GRENADE_H
#define WORM_GRENADE_H

#include "worm_weapon.h"
#include "crosshair.h"
class WormGreenGrenade : public WormWeapon {

    private:
    Crosshair mira;
    int municion;

    public:
    explicit WormGreenGrenade(int ammo);
    void render(SDL2pp::Renderer& renderer, TextureManager& tex_manager, int x, int y, int flip, int angulo);
    const int getWeapon();
    void increaseAngle();
    void decreaseAngle();
    int getAmmo();
    ~WormGreenGrenade() {}
};
#endif
