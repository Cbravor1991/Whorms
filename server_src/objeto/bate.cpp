#include "Bat.h"
#include <string>

Bat::Bat(World& world, GameParameters& parameters):
	Weapon(world, parameters, parameters.getWeaponDamage(BAT_NAME),
		parameters.getWeaponRadius(BAT_NAME)){}
		
Bat::~Bat(){}

const std::string& Bat::getName(){
	return BAT_NAME;
}

void Bat::setInitialVelocity(){
	this->explode();
}

void Bat::explode(){
	b2Vec2 center = this->body->GetPosition();
	this->attackWormExplosion(center, this->angle);

	this->waiting_to_explode = false;
	this->is_dead = true;
}
