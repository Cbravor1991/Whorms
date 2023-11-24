#ifndef WORM_BANANA_H
#define WORM_BANANA_H

#include "worm_weapon.h"
#include "crosshair.h"
class WormBanana : public WormWeapon {

    private:
    Crosshair mira;
    int municion;

    public:
    explicit WormBanana(int ammo);
    void render(SDL2pp::Renderer& renderer, TextureManager& tex_manager, int x, int y, int flip, int angulo);
    const int getWeapon();
    void increaseAngle();
    void decreaseAngle();
    int getAmmo();
    ~WormBanana() {}
};

#endif