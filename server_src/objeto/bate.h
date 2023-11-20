#ifndef __SERVERBAT_H__
#define __SERVERBAT_H__

#include "Weapon.h"
#include <string>

class Bat: public Weapon{		
	public:
		Bat(World& world, GameParameters& parameters);
		~Bat();

		const std::string& getName() override;

		void setInitialVelocity() override;

		void explode() override;
};

#endif
