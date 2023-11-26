#ifndef WORM_MORTAR_H
#define WORM_MORTAR_H

#include "worm_weapon.h"
#include "crosshair.h"

class WormMortar : public WormWeapon
{

private:
    Crosshair mira;
    int municion;
    int potencia;
public:
    explicit WormMortar(int ammo);
    void render(SDL2pp::Renderer &renderer, TextureManager &tex_manager, int x, int y, int flip, int angulo);
    Action *usar(int x, int y, bool direccion);
    const int getWeapon();
    void increaseAngle();
    void decreaseAngle();
    int getAmmo();
    void setTimer(int segundos);
    int getTimer();
    void increasePower();
    ~WormMortar() {}
};

#endif
