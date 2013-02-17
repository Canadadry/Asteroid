/*
 * World.cpp
 *
 * Asteroid - Copyright (c) 16 févr. 2013 - Jerome Mourey
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
 *  Created on: 16 févr. 2013
 */

#include "World.h"
#include <Engine/Body.h>

World::World()
{
}

World::~World()
{
}

void World::addBody(Body* body)
{
	m_bodies.push_back(body);
}

void World::removeBody(Body* body)
{
	m_bodies.remove(body);
}

typedef std::list<Body*>::iterator bIter;
bool World::checkBodyCollision(Body* body)
{
	bool ret = false;
	for(bIter it = m_bodies.begin() ; it != m_bodies.end() ; it++ )
	{
		if(body == *it) continue;
		if( body->intersects(**it))
		{
			ret = ret | body->handleCollision(*it);
		}
	}

	return ret;

}
