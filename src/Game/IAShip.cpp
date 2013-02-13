/*
 * IAShip.cpp
 *
 * Asteroid - Copyright (c) 13 févr. 2013 - Jerome Mourey
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
 *  Created on: 13 févr. 2013
 */

#include "IAShip.h"
#include <Engine/Entity.h>
#include <Engine/Body.h>
#include <Engine/Weapon.h>
#include <Engine/Physics.h>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#define PI 3.14151

double frand_a_b(double a, double b)
{
	return ( rand()/(double)RAND_MAX ) * (b-a) + a;
}



IAShip::IAShip(Entity* entity)
: GamePad(entity)
, m_turnDirection(0.0)
{
}

IAShip::~IAShip()
{
}


void IAShip::handleEvent(const sf::Event& event)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_entity->body()->angle -= 0.02;
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_entity->body()->angle += 0.02;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_entity->physics()->thrust(-0.2);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_entity->physics()->thrust(0.2);
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_entity->weapon()->fire();
	}

	//	if(m_turnDirection<0.1)
	//	{
	//		if (frand_a_b(0.0,1.0) < 0.2) m_turnDirection = frand_a_b(-PI/3,PI/3);
	//	}
	//	else{
	//		m_turnDirection -= 0.2;
	//		m_entity->body()->angle += 0.2;
	//	}
	//	m_entity->physics()->thrust(frand_a_b(0.0,0.5));



}

