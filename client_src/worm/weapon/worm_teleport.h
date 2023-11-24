#ifndef WORM_TELEPORT_H
#define WORM_TELEPORT_H

#include "worm_weapon.h"

class WormTeleport : public WormWeapon {

    private:
    int municion;

    public:
    explicit WormTeleport(int ammo);
    void render(SDL2pp::Renderer& renderer, TextureManager& tex_manager, int x, int y, int flip, int angulo);
    const int getWeapon();
    void increaseAngle();
    void decreaseAngle();
    int getAmmo();
    ~WormTeleport() {}
};

#endif
