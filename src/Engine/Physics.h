/*
 * Physics.h
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

#ifndef PHYSICS_H_
#define PHYSICS_H_
class Entity;
class World;
class Body;
class Physics
{
public:
	Physics(Entity* entity);
	virtual ~Physics();

	void  setAttractionPoint(Body* attractionPoint, float attractionPower);
	void  update(World& world);
	void  thrust(float power);

	float   drag;
	float   velocityX;
	float   velocityY;

private:
	Entity* m_entity;
	Body*   m_attractionPoint;
	float   m_attractionPower;
};

#endif /* PHYSICS_H_ */
