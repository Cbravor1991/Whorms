#ifndef WORM_BAZOOKA_H
#define WORM_BAZOOKA_H
#include "worm_weapon.h"
#include "crosshair.h"
class WormBazooka : public WormWeapon {

    private:
    Crosshair mira;
    int municion;

    public:
    explicit WormBazooka(int ammo);
    void render(SDL2pp::Renderer& renderer, TextureManager& tex_manager, int x, int y, int flip, int angulo);
    const int getWeapon();
    void increaseAngle();
    void decreaseAngle();
    int getAmmo();
    ~WormBazooka() {}
};

#endif