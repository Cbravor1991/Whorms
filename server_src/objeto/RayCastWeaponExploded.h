#ifndef __RAYCASTWEAPONEXPLODED_H__
#define __RAYCASTWEAPONEXPLODED_H__

#include "../../libs/box2d-2.4.0/include/box2d/box2d.h"
#include <vector>
#include <cstdint>
#include <ostream>
#include <iostream>

class RayCastWeaponExploded : public b2RayCastCallback
{
private:
    std::vector<b2Body *> affected_worms;
    b2Body *closest;

public:
    RayCastWeaponExploded();
    ~RayCastWeaponExploded();

    // Devuelve el gusano mas cercano a la explosion, si hay
    b2Body *getClosestWorm();

    // Busca al objeto mas cercano a la explosion
    float ReportFixture(b2Fixture *fixture, const b2Vec2 &point,
                        const b2Vec2 &normal, float fraction) override;
};

#endif
