#ifndef WORM_AIRSTRIKE_H
#define WORM_AIRSTRIKE_H

#include "worm_weapon.h"
#include "crosshair.h"
class WormAirstike : public WormWeapon {
    private:
    int municion;//max=2

    public:
    explicit WormAirstike(int ammo);
    void render(SDL2pp::Renderer& renderer, TextureManager& tex_manager, int x, int y, int flip, int angulo);
    const int getWeapon();
    void increaseAngle();
    void decreaseAngle();
    int getAmmo();
    ~WormAirstike() {}
};

#endif
