/*
 * Ship.cpp
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

#include "Ship.h"
#include <Engine/Body.h>
#include <Engine/Physics.h>
#include <Engine/View.h>
#include <Engine/Health.h>
#include <Engine/Weapon.h>

#include <Game/Gun.h>
#include <Game/EntityType.h>
#include <Game/BonusType.h>
#include <Game/AsteroidGame.h>
#include <Game/Bonus.h>

#include <SFML/Graphics/ConvexShape.hpp>

#include <cmath>

#define PI 3.14151


Ship::Ship()
: m_shape(new sf::ConvexShape(3) )
, m_bonus(0)
{
	setBody(new Body(this));
	body()->x = 400;
	body()->y = 300;
	body()->radius = 10;
	body()->type = EntityType::EntityShip;
	body()->collisionHandler = this;


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
	health()->invincibilityFrame = 1000;
	health()->died.Connect(this,&Ship::onDied);

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

bool Ship::HandleCollision(Body* body)
{
	return false;
}

void Ship::onDied()
{
	destroyed(this);
}

void Ship::update()
{
	if(m_bonus)
	{
		if(m_bonus->update())
		{
			delete m_bonus;
			m_bonus = 0;
		}
	}

	AsteroidGame* agame = (AsteroidGame*)game;
	agame->shipHealth = health()->hits;

	if(health()->invincible())
	{
		if(m_shape->getOutlineColor() != sf::Color::Yellow)
			m_shape->setOutlineColor(sf::Color::Yellow);
	}
	else
	{
		if(m_shape->getOutlineColor() != sf::Color::White)
			m_shape->setOutlineColor(sf::Color::White);
	}
}

void Ship::setBonus(Bonus* bonus)
{
	if(m_bonus)
	{
		delete m_bonus;
	}
	m_bonus = bonus;

	switch(m_bonus->type())
	{
		case BonusType::HealthBonus   : health()->hit(-1);break;
		case BonusType::RayBonus      : ((Gun*)weapon())->rayCount++;break;
		case BonusType::PiercingBonus : ((Gun*)weapon())->piercing = true;break;
		case BonusType::LenghtBonus   : ((Gun*)weapon())->bulletLifeTime += 5;break;
		default: break;


	}

	// TODO : correct this ugly hack


}

