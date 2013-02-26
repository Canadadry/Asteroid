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

#include "EntityType.h"
#include "BonusEntity.h"
#include "Bonus.h"
#include "Ship.h"
#include <Game/BonusType.h>
#include <Game/AsteroidGame.h>

extern Screen* currentScreen ;
extern std::string path;
#define PI 3.14151

BonusEntity::BonusEntity(Bonus* bonus)
: Entity()
, m_shape(new sf::Sprite)
, m_texture(new sf::Texture)
, m_bonus(bonus)
, m_age(0)
{

	printf("new bonus\n");
	setBody(new Body(this));
	body()->radius = 5;
	body()->collisionHandler = this;
	body()->type = EntityType::EntityBonus;

	setPhysics(new Physics(this));
	physics()->drag = 1.0;

	Entity* ship = ((AsteroidGame*)currentScreen)->ship;
	physics()->setAttractionPoint(ship->body(),-0.02);

	setView(new View(this));
	view()->drawable = m_shape;
	//m_shape->setTexture(*m_texture);
//	m_shape->setFillColor(sf::Color::Transparent);
//	m_shape->setOutlineThickness(1.0f);
	switch(m_bonus->type())
	{
		case BonusType::HealthBonus   : m_texture->loadFromFile(path+"health.png");break;
		case BonusType::RayBonus      : m_texture->loadFromFile(path+"powerup.png");break;
		case BonusType::PiercingBonus : m_texture->loadFromFile(path+"piercingBullet.png");break;
		//case BonusType::LenghtBonus   : m_texture->loadFromFile(path+"health.png");break;
		//TODO : make lenghtBonus image

//		case BonusType::HealthBonus   : m_shape->setOutlineColor(sf::Color::Red); break;
//		case BonusType::RayBonus      : m_shape->setOutlineColor(sf::Color::Blue); break;
//		case BonusType::PiercingBonus : m_shape->setOutlineColor(sf::Color::Green); break;
//		case BonusType::LenghtBonus   : m_shape->setOutlineColor(sf::Color::Magenta); break;

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
		((Ship*)(body->entity()))->setBonus(m_bonus);
		destroyed(this);
	}
	return ret;

}


void BonusEntity::update()
{
	m_age++;
//	if (m_age > 20) view()->alpha -= 0.2;
	if (m_age > 1000)
	{
		destroyed(this);
	}
	m_shape->setRotation(-body()->angle/PI*180.0 );
}
