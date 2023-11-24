#ifndef WORM_GRENADE_HOLY_H
#define WORM_GRENADE_HOLY_H
#include "worm_weapon.h"
#include "crosshair.h"
class WormHolyGrenade : public WormWeapon {

    private:
    Crosshair mira;
    int municion;

    public:
    explicit WormHolyGrenade(int ammo);
    void render(SDL2pp::Renderer& renderer, TextureManager& tex_manager, int x, int y, int flip, int angulo);
    const int getWeapon();
    void increaseAngle();
    void decreaseAngle();
    int getAmmo();
    ~WormHolyGrenade() {}
};

#endif
