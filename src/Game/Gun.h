/*
 * Gun.h
 *
 * Asteroid - Copyright (c) 12 févr. 2013 - Jerome Mourey
 *
 * This software is provided 'as-is', without any express or
 * implied warranty. In no event will the authors be held
 * liable for any damages arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute
 * it freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented;
 *    you must not claim that you wrote the original software.
 *    If you use this software in a product, an acknowledgment
 *    in the product documentation would be appreciated but
 *    is not required.
 * 
 * 2. Altered source versions must be plainly marked as such,
 *    and must not be misrepresented as being the original software.
 * 
 * 3. This notice may not be removed or altered from any
 *    source distribution.
 *
 *  Created on: 12 févr. 2013
 */

#ifndef GUN_H_
#define GUN_H_

#include <Engine/Weapon.h>
#include <SFML/System/Clock.hpp>

class Entity;

class Gun :public Weapon
{
public:
	Gun(Entity* entity);
	virtual ~Gun();
	virtual void fire();

	void onBulletDied(Entity* bullet);
	int cadence;
	
private:
	sf::Clock m_clock;

};

#endif /* GUN_H_ */
