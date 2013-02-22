/*
 * Gun.cpp
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

#include "Gun.h"
#include <Game/Bullet.h>
#include <Engine/Entity.h>
#include <Engine/Body.h>
#include <Engine/Physics.h>

#include <cmath>

Gun::Gun(Entity* entity)
: Weapon(entity)
, cadence(100)
, rayCount(1)
, piercing(false)
, bulletLifeTime(25)
{
	m_clock.restart();
	ammo = 5;
}

Gun::~Gun()
{
}

#define PI 3.1415926535

void Gun::fire()
{
	if( ammo <= 0 ) return;
	if(m_clock.getElapsedTime().asMilliseconds() < cadence) return;
	m_clock.restart();

	const float offset = 10;
	Body* b = m_entity->body();
	createBullet(b->x,b->y,b->angle , -10,b->radius*2+1,0.0f,piercing);

	for(int i = 1; i<rayCount;i++)
	{
		createBullet(b->x,b->y,b->angle , -10,b->radius*2+1,  offset*i,piercing);
		createBullet(b->x,b->y,b->angle , -10,b->radius*2+1, -offset*i,piercing);
	}

//	createBullet(b->x,b->y,b->angle + PI/2  ,-10,b->radius*2+1);
//	createBullet(b->x,b->y,b->angle + PI    ,-10,b->radius*2+1);
//	createBullet(b->x,b->y,b->angle +3*PI/2 ,-10,b->radius*2+1);

	Weapon::fire();
}

void Gun::createBullet(float x,float y,float angle,float speed,float dist,float offset,bool piercingBullet)
{
	Bullet* bullet = new Bullet(bulletLifeTime,piercingBullet);
	bullet->body()->x = x;
	bullet->body()->y = y;
	bullet->body()->x -= sin(-angle) * dist;
	bullet->body()->y -= cos(-angle) * dist;

	bullet->body()->x -= sin(-angle + PI/2) * offset;
	bullet->body()->y -= cos(-angle + PI/2) * offset;


	bullet->body()->angle = angle;
	bullet->physics()->thrust(speed);
	bullet->destroyed.Connect(this,&Gun::onBulletDied);
	m_entity->entityCreated(bullet);


}

void Gun::onBulletDied(Entity* bullet)
{
	ammo++;
}

