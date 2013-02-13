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

#include <SFML/Graphics/CircleShape.hpp>

extern double frand_a_b(double a, double b);


Asteroid::Asteroid()
: m_shape(new sf::CircleShape(20) )
{
	setBody(new Body(this));
	body()->radius = 20;
	body()->x = frand_a_b(10.0,790.0);
	body()->y = frand_a_b(10.0,590.0);

	setPhysics(new Physics(this));
	physics()->velocityX = frand_a_b(-1.0,1.0);
	physics()->velocityY = frand_a_b(-1.0,1.0);
	physics()->drag = 1.0;


	setView(new View(this));
	view()->drawable = m_shape;
	m_shape->setFillColor(sf::Color::Transparent);
	m_shape->setOutlineThickness(1.0f);
	m_shape->setOutlineColor(sf::Color::White);

	setHealth(new Health(this));
	health()->hits = 3;
	health()->hurt.Connect(this,&Asteroid::onHurt);

}

Asteroid::~Asteroid()
{
	if(health()->hits > 0) destroyed(this);

	delete body();
	delete physics();
	delete view();
}

void Asteroid::update()
{
	physics()->update();
	if(body()->x < 0 || body()->x > 800)
	{
		physics()->velocityX *= -1;
	}
	if(body()->y < 0 || body()->y > 600)
	{
		physics()->velocityY *= -1;
	}


	m_shape->setRadius(body()->radius);
	m_shape->setPosition(body()->x,body()->y);



}


void Asteroid::onHurt()
{
	body()->radius*=0.75;
	m_shape->setRotation(body()->radius);
	if(body()->radius < 10)
	{
		destroyed(this);
		return;
	}

	Asteroid* asteroid = new Asteroid();
	asteroid->body()->x = body()->x ;
	asteroid->body()->y = body()->y ;
	asteroid->body()->radius = body()->radius;
	entityCreated(asteroid);

}


