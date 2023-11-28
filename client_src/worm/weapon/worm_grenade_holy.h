#ifndef WORM_GRENADE_HOLY_H
#define WORM_GRENADE_HOLY_H
#include "worm_weapon.h"
#include "crosshair.h"
#include "powerbar.h"
class WormHolyGrenade : public WormWeapon
{

private:
    Crosshair mira;
    int municion;
    int timer;
    //int potencia;
    PowerBar potencia;
public:
    explicit WormHolyGrenade(int ammo);
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
    ~WormHolyGrenade() {}
};

#endif
