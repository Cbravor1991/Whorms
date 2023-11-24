#ifndef WORM_GRENADE_CLUSTER_H
#define WORM_GRENADE_CLUSTER_H

#include "worm_weapon.h"
#include "crosshair.h"
class WormClusterGrenade : public WormWeapon
{

private:
    Crosshair mira;
    int municion;

public:
    explicit WormClusterGrenade(int ammo);
    void render(SDL2pp::Renderer &renderer, TextureManager &tex_manager, int x, int y, int flip, int angulo);
    Action *usar(int x, int y, bool direccion);
    const int getWeapon();
    void increaseAngle();
    void decreaseAngle();
    int getAmmo();
    ~WormClusterGrenade() {}
};

#endif
