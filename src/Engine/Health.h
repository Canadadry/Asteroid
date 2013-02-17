/*
 * Health.h
 *
 * Asteroid - Copyright (c) 12 f�vr. 2013 - Jerome Mourey
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
 *  Created on: 12 f�vr. 2013
 */

#ifndef HEALTH_H_
#define HEALTH_H_

#include <Signal/Signal.h>
#include <SFML/System/Clock.hpp>

class Entity;

class Health
{
public:
	Health(Entity* entity);
	virtual ~Health();

	void hit(int damage);
	bool invincible();

	int               hits;
	int               invincibilityFrame;
	Signal0 <void>    died;
	Signal0 <void>    hurt;

private:
	Entity*   m_entity;
	sf::Clock m_clock;

};

#endif /* HEALTH_H_ */
