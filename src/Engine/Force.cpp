/*
 * Force.cpp
 *
 * Asteroid - Copyright (c) 3 mars 2013 - Jerome Mourey
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
 *  Created on: 3 mars 2013
 */

#include "Force.h"
#include <Engine/Entity.h>
#include <Engine/Physics.h>
#include <Engine/Body.h>

#include <cmath>

Force::Force()
{
	// TODO Auto-generated constructor stub

}

Force::~Force()
{
	// TODO Auto-generated destructor stub
}

Friction::Friction()
: drag(1.0){}

Friction::~Friction(){}

void Friction::affectEntity(Entity* entity)
{
	entity->physics()->velocityX *= entity->physics()->drag;
	entity->physics()->velocityY *= entity->physics()->drag;
}

Attraction::Attraction()
: origin(0)
, power(1.0)
{}

Attraction::~Attraction(){}

void Attraction::affectEntity(Entity* entity)
{
	if( origin != 0)
		{
			const float max_speed = 3.0f; // pixel per cycle (16ms)
			const float max_force = 1.0f; // pixel per cycle per cycle (16ms)

			float desired_velocityX = (origin->x - entity->body()->x);
			float desired_velocityY = (origin->y - entity->body()->y);
			float norme  = sqrt(desired_velocityX*desired_velocityX + desired_velocityY*desired_velocityY);
			desired_velocityX *= max_speed / norme;
			desired_velocityY *= max_speed / norme;


			float steeringX = desired_velocityX - entity->physics()->velocityX;
			float steeringY = desired_velocityY - entity->physics()->velocityY;

			norme  = sqrt(steeringX*steeringX + steeringY*steeringY);
			if(norme > max_force)
			{
				steeringX *= max_force / norme;
				steeringY *= max_force / norme;
			}

			steeringX *= power;
			steeringY *= power;

			entity->physics()->velocityX += steeringX;
			entity->physics()->velocityY += steeringY;

			norme  = sqrt(entity->physics()->velocityX*entity->physics()->velocityX + entity->physics()->velocityY*entity->physics()->velocityY);
			if(norme > max_speed)
			{
				entity->physics()->velocityX *= max_speed / norme;
				entity->physics()->velocityY *= max_speed / norme;
			}
		}

}
