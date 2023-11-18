#ifndef WEAPON_H_
#define WEAPON_H_

#include <string>

class Weapon {


public:
    virtual std::string obtener_nombre() = 0;
};

#endif