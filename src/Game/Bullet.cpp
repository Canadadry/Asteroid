/*
 * Bullet.cpp
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

#include "Bullet.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <Engine/Body.h>
#include <Engine/Physics.h>
#include <Engine/View.h>
#include <Engine/Health.h>
#include <Engine/Weapon.h>

#include <Game/EntityType.h>
#include <Game/AsteroidGame.h>

extern std::string path;

Bullet::Bullet(int lifeTime,bool piercing)
:Entity()
, m_shape(new sf::Sprite )
, m_texture(new sf::Texture), m_age(0)
, m_lifeTime(lifeTime)
, m_isPiercing(piercing)
{
	name = "Bullet";

	setBody(new Body(this));
	body()->radius = 4;
	body()->collisionHandler = this;
	body()->type = EntityType::EntityBullet;

	setPhysics(new Physics(this));
	physics()->drag = 1.0;

	setView(new View(this));
	view()->drawable = m_shape;
	m_texture->loadFromFile(path+"bullet.png");
	m_shape->setTexture(*m_texture);
	m_shape->setOrigin(sf::Vector2f(m_texture->getSize().x/2,m_texture->getSize().y/2));


}

Bullet::~Bullet()
{
	delete body();
	delete physics();
	delete view();
}


bool Bullet::HandleCollision(Body* body)
{
	bool ret = false;
	switch(body->type)
	{


		case EntityType::EntityShip    : break;
		case EntityType::EntityBullet  : break;
		case EntityType::EntityAsteroid: {
			AsteroidGame* agame = (AsteroidGame*)game;
			agame->score += 10;
		body->entity()->health()->hit(1);break;
		}
	}
	if(!m_isPiercing)
	{
		destroyThis();
	}
	return ret;
}


void Bullet::update()
{
	m_age++;
//	if (m_age > 20) view()->alpha -= 0.2;
	if (m_age > m_lifeTime)
	{
		destroyThis();
	}
}

