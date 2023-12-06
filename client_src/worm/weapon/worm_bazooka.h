#ifndef WORM_BAZOOKA_H
#define WORM_BAZOOKA_H
#include "worm_weapon.h"
#include "crosshair.h"
#include "powerbar.h"

class WormBazooka : public WormWeapon
{

private:
    Crosshair mira;
    int municion;
    PowerBar potencia;
public:
    explicit WormBazooka(int ammo);
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
    ~WormBazooka() {}
};

#endif
