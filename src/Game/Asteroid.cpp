/*
 * Asteroid.cpp
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

#include "Asteroid.h"
#include <Engine/Body.h>
#include <Engine/Physics.h>
#include <Engine/View.h>
#include <Engine/Health.h>

#include <Game/BonusEntity.h>
#include <Game/EntityType.h>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <cmath>


extern std::string path;
extern double frand_a_b(double a, double b);


Asteroid::Asteroid()
: Entity()
, m_shape(new sf::Sprite )
, m_texture(new sf::Texture)
{
	name = "Asteroid";

	setBody(new Body(this));
	body()->angle = frand_a_b(0.0,360.0);
	body()->radius = frand_a_b(5.0,30.0);
	body()->x = frand_a_b(10.0,790.0);
	body()->y = frand_a_b(10.0,590.0);
	body()->type = EntityType::EntityAsteroid;
	body()->collisionHandler = this;

	setPhysics(new Physics(this));
	physics()->thrust(frand_a_b(0.0,2.0));
	physics()->drag = 1.0;


	setView(new View(this));
	view()->drawable = m_shape;

	m_texture->loadFromFile(path+"rock.png");
	m_shape->setTexture(*m_texture);
	m_shape->setOrigin(sf::Vector2f(m_texture->getSize().x/2,m_texture->getSize().y/2));
	float factor = body()->radius/(float)m_texture->getSize().x*2.0;
	m_shape->scale(factor,factor);


	setHealth(new Health(this));
	health()->hits = 3;
	health()->hurt.Connect(this,&Asteroid::onHurt);

}

Asteroid::~Asteroid()
{
	destroyThis();

	delete body();
	delete physics();
	delete view();
}

bool Asteroid::HandleCollision(Body* body)
{
	bool ret = false;
	switch(body->type)
	{
		case EntityType::EntityAsteroid: break;
		case EntityType::EntityBullet  : break;
		case EntityType::EntityShip    : {
			body->entity()->health()->hit(1);
			//printf("hitting ship!\n");
			break;
		}

	}

	return ret;
}


void Asteroid::update()
{
}

void Asteroid::onHurt()
{

	body()->radius*=0.75;
	m_shape->setRotation(body()->radius);
	m_shape->setOrigin(body()->radius,body()->radius);
	m_shape->scale(0.75,0.75);

	physics()->velocityX *= -1 ;
	physics()->velocityY *= -1 ;

	if(body()->radius < 10)
	{
		destroyThis();
		return;
	}

	if( (body()->radius*0.75 < 10) && (frand_a_b(0.0,1.0) > 0.7))
	{
		BonusEntity* bonusEntity = new BonusEntity();
		bonusEntity->body()->x = body()->x ;
		bonusEntity->body()->y = body()->y ;
		bonusEntity->body()->radius = body()->radius;
		bonusEntity->body()->angle = body()->radius;
		bonusEntity->physics()->thrust(1.0);

		entityCreated(bonusEntity);
	}
	else
	{
		Asteroid* asteroid = new Asteroid();
		asteroid->body()->x = body()->x ;
		asteroid->body()->y = body()->y ;
		asteroid->body()->radius = body()->radius;
		asteroid->body()->angle = body()->radius;
		float factor = body()->radius/(float)m_texture->getSize().x*2.0;
		m_shape->setScale(factor,factor);

		entityCreated(asteroid);
	}

}


