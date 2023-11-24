#include "RayCastWeaponExploded.h"

RayCastWeaponExploded::RayCastWeaponExploded() : closest(NULL) {}

RayCastWeaponExploded::~RayCastWeaponExploded() {}

b2Body *RayCastWeaponExploded::getClosestWorm()
{
    if (!this->closest)
    {
        return NULL;
    }
    if (!this->closest->gusano)
    {
        this->closest = NULL;
        return NULL;
    }

    this->affected_worms.push_back(this->closest);
    b2Body *closest_worm = this->closest;
    this->closest = NULL;
    return closest_worm;
}

float RayCastWeaponExploded::ReportFixture(b2Fixture *fixture,
                                           const b2Vec2 &point, const b2Vec2 &normal, float fraction)
{
    b2Body *closest_body = fixture->GetBody();
    for (b2Body *affected_worm : this->affected_worms)
    {
        if (affected_worm == closest_body)
        {
            return -1;
        }
    }
    this->closest = closest_body;
    return fraction;
}
