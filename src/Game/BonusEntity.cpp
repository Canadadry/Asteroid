/*
 * BonusEntity.cpp
 *
 * Asteroid - Copyright (c) 20 févr. 2013 - Jerome Mourey
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
 *  Created on: 20 févr. 2013
 */

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <Engine/Body.h>
#include <Engine/Physics.h>
#include <Engine/View.h>
#include <Engine/Force.h>


#include "EntityType.h"
#include "BonusEntity.h"
#include "Ship.h"
#include <Game/AsteroidGame.h>
#include <cmath>

extern double frand_a_b(double a, double b);
extern Screen* currentScreen ;
extern std::string path;
#define PI 3.14151


Attraction* BonusEntity::m_shipAttraction = 0;
const std::string BonusEntity::bonusName[BonusCount] = {"HealthBonus","RayBonus","PiercingBonus","LenghtBonus"};


BonusEntity::BonusEntity()
: Entity()
, m_shape(new sf::Sprite)
, m_texture(new sf::Texture)
, m_age(0)
, m_type(0)
{
	m_type = floor(frand_a_b(0.0,BonusEntity::BonusCount-1)+0.5);
	name = bonusName[m_type];

	if(m_shipAttraction == 0)
	{
		m_shipAttraction = new Attraction();
		m_shipAttraction->origin = ((AsteroidGame*)currentScreen)->ship->body();
		m_shipAttraction->power = 0.02;
	}

	setBody(new Body(this));
	body()->radius = 5;
	body()->collisionHandler = this;
	body()->type = EntityType::EntityBonus;

	setPhysics(new Physics(this));
	physics()->drag = 1.0;

	physics()->forces.push_back(m_shipAttraction);

	setView(new View(this));
	view()->drawable = m_shape;
	switch(m_type)
	{
		case BonusEntity::HealthBonus   : m_texture->loadFromFile(path+"health.png");break;
		case BonusEntity::RayBonus      : m_texture->loadFromFile(path+"powerup.png");break;
		case BonusEntity::PiercingBonus : m_texture->loadFromFile(path+"piercingBullet.png");break;
		//case BonusType::LenghtBonus   : m_texture->loadFromFile(path+"health.png");break;
		//TODO : make lenghtBonus image
		default: break;
	}

	m_shape->setTexture(*m_texture);
	m_shape->setOrigin(sf::Vector2f(m_texture->getSize().x/2,m_texture->getSize().y/2));

}

BonusEntity::~BonusEntity()
{
	delete body();
	delete physics();
	delete view();
}

bool BonusEntity::HandleCollision(Body* body)
{
	bool ret = false;
	if(body->type == EntityType::EntityShip)
	{
		((Ship*)(body->entity()))->setBonus(m_type);
		destroyed(this);
	}
	return ret;

}


int BonusEntity::type() const
{
	return m_type;
}

void BonusEntity::update()
{
	m_age++;
	if (m_age > 1000)
	{
		destroyed(this);
	}
	m_shape->setRotation(-body()->angle/PI*180.0 );
}
