#ifndef WORM_WEAPON_H
#define WORM_WEAPON_H

#include "../../graphics/texture_manager.h"
#include "../../actions/action.h"
#include "../../actions/shoot.h"
#include "../../actions/position.h"

const int NO_WEAPON = 0;
const int AIR_STRIKE = 1;
const int TELEPORT = 2;
const int BAT = 3;
const int DYNAMITE = 4;
const int BAZOOKA = 5;
const int MORTAR = 6;
const int GREEN_GRENADE = 7;
const int CLUSTER_GRENADE = 8;
const int HOLY_GRENADE = 9;
const int BANANA = 10;

const int INFINITE_AMMO = -1;

class WormWeapon
{
    // std::shared_ptr<SDL2pp::Texture> texture;

public:
    WormWeapon(){};
    WormWeapon(int ammo){};
    virtual void render(SDL2pp::Renderer &renderer, TextureManager &tex_manager, int x, int y, int flip, int angulo) = 0;
    virtual const int getWeapon() = 0;
    virtual void increaseAngle() = 0;
    virtual void decreaseAngle() = 0;
    virtual Action *usar(int x, int y, bool direccion) = 0;
    virtual int getAmmo() = 0;
    virtual void setTimer(int segundos) = 0;
    virtual int getTimer() = 0;
    virtual void increasePower() = 0;
    virtual bool isMaxPower() = 0;
    virtual ~WormWeapon() {}
};

#endif