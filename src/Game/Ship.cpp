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

#include <Game/BonusEntity.h>

#include <Game/Gun.h>
#include <Game/EntityType.h>
#include <Game/AsteroidGame.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <cmath>

#define PI 3.14151

extern std::string path;

Ship::Ship()
: Entity()
, m_shape(new sf::Sprite )
, m_texture(new sf::Texture)
{
	name = "Ship";

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

	m_texture->loadFromFile(path+"ship.png");
	m_shape->setTexture(*m_texture);
	m_shape->setOrigin(sf::Vector2f(m_texture->getSize().x/2,m_texture->getSize().y/2));

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

	AsteroidGame* agame = (AsteroidGame*)game;
	agame->shipHealth = health()->hits;

	if(health()->invincible())
	{
		m_shape->setColor(sf::Color(255,255,255,128));
	}
	else
	{
		m_shape->setColor(sf::Color(255,255,255,255));
	}
}

void Ship::setBonus(int bonus)
{

	switch(bonus)
	{
		case BonusEntity::HealthBonus   : health()->hit(-1);break;
		case BonusEntity::RayBonus      : ((Gun*)weapon())->rayCount++;break;
		case BonusEntity::PiercingBonus : ((Gun*)weapon())->piercing = true;break;
		case BonusEntity::LenghtBonus   : ((Gun*)weapon())->bulletLifeTime += 5;break;
		default: break;
	}
}

