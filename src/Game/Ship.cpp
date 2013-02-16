/*
 * Ship.cpp
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

#include "Ship.h"
#include <Engine/Body.h>
#include <Engine/Physics.h>
#include <Engine/View.h>
#include <Engine/Health.h>
#include <Engine/Weapon.h>

#include <Game/Gun.h>

#include <SFML/Graphics/ConvexShape.hpp>

#include <cmath>

#define PI 3.14151


Ship::Ship()
: m_shape(new sf::ConvexShape(3) )
{
	setBody(new Body(this));
	body()->x = 400;
	body()->y = 300;
	body()->radius = 10;

	setPhysics(new Physics(this));
	physics()->drag = 0.9;

	setView(new View(this));
	view()->drawable = m_shape;
	m_shape->setPoint(0,sf::Vector2f( 0.0 ,-10.0));
	m_shape->setPoint(1,sf::Vector2f( 5.0 , 0.0));
	m_shape->setPoint(2,sf::Vector2f(-5.0 , 0.0));
	m_shape->setFillColor(sf::Color::Transparent);
	m_shape->setOutlineThickness(1.0f);
	m_shape->setOutlineColor(sf::Color::White);


	setHealth(new Health(this));
	health()->hits = 5;

	Weapon* weapon = 0;
	weapon = new Gun(this);
	setWeapon(weapon);
}

Ship::~Ship()
{
	if(health()->hits > 0) destroyed(this);

	delete body();
	delete physics();
	delete view();
	delete weapon();
}


void Ship::onDied()
{
	destroyed(this);
}
