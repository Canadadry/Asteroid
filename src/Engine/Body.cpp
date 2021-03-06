/*
 * Body.cpp
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

#include "Body.h"
#include <cmath>

Body::Body(Entity* entity)
: x       (0.0)
, y       (0.0)
, angle   (0.0)
, radius  (0.0)
, type    (0)
, collisionHandler(0)
, m_entity(entity)
{
}

Body::~Body()
{
}

Entity* Body::entity()
{
	return m_entity;
}

bool Body::intersects(const Body& body)
{
	 float dx = x - body.x;
	 float dy = y - body.y;

	 return  sqrt((dx * dx) + (dy * dy)) <= radius + body.radius;
}


bool Body::handleCollision(Body* body)
{
	bool ret = true;
	if(collisionHandler)
	{
		ret = collisionHandler->HandleCollision(body);
	}
	return ret;
}


