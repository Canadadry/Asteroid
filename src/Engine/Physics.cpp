/*
 * Physics.cpp
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

#include "Physics.h"

#include <Engine/Entity.h>
#include <Engine/Body.h>
#include <cmath>
#include <Engine/World.h>

Physics::Physics(Entity* entity)
:drag     (0.0)
,velocityX(0.0)
,velocityY(0.0)
,m_entity (entity)
,m_attractionPoint(0)
,m_attractionPower(0.f)
{}

Physics::~Physics()
{
}

void  Physics::update(World& world)
{
	// apply forces
	if( m_attractionPoint != NULL)
	{
		const float max_speed = 3.0f; // pixel per cycle (16ms)
		const float max_force = 1.0f; // pixel per cycle per cycle (16ms)

		float desired_velocityX = (m_attractionPoint->x - m_entity->body()->x);
		float desired_velocityY = (m_attractionPoint->y - m_entity->body()->y);
		float norme  = sqrt(desired_velocityX*desired_velocityX + desired_velocityY*desired_velocityY);
		desired_velocityX *= max_speed / norme;
		desired_velocityY *= max_speed / norme;


		float steeringX = desired_velocityX - velocityX;
		float steeringY = desired_velocityY - velocityY;

		norme  = sqrt(steeringX*steeringX + steeringY*steeringY);
		if(norme > max_force)
		{
			steeringX *= max_force / norme;
			steeringY *= max_force / norme;
		}

		steeringX *= m_attractionPower;
		steeringY *= m_attractionPower;

		velocityX += steeringX;
		velocityY += steeringY;

		norme  = sqrt(velocityX*velocityX + velocityY*velocityY);
		if(norme > max_speed)
		{
			velocityX *= max_speed / norme;
			velocityY *= max_speed / norme;
		}
	}

	// apply friction
	velocityX *= drag;
	velocityY *= drag;

	//moving body if it's possible
	m_entity->body()->x += velocityX;
	m_entity->body()->y += velocityY;

	if(world.checkBodyCollision(m_entity->body()))
	{
		m_entity->body()->x -= velocityX;
		m_entity->body()->y -= velocityY;
		velocityX *= -1;
		velocityY *= -1;
	}


	if(      m_entity->body()->x <  0  ) m_entity->body()->x = 800;
	else if( m_entity->body()->x > 800 ) m_entity->body()->x = 0;

	if(      m_entity->body()->y <  0  ) m_entity->body()->y = 600;
	else if( m_entity->body()->y > 600 ) m_entity->body()->y = 0;

}

void Physics::setAttractionPoint(Body* attractionPoint, float attractionPower)
{
	m_attractionPoint = attractionPoint;
	m_attractionPower = attractionPower;
}

void  Physics::thrust(float power)
{
	velocityX += sin(-m_entity->body()->angle) * power;
	velocityY += cos(-m_entity->body()->angle) * power;
}

