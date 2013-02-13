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

Gun::Gun(Entity* entity)
: Weapon(entity)
{
	ammo = 5;
}

Gun::~Gun()
{
}

void Gun::fire()
{
	printf("fire \n");

	if( ammo <= 0 ) return;


	Bullet* bullet = new Bullet();
	printf("Gun create bullet %d\n",bullet);

	bullet->body()->x = m_entity->body()->x;
	bullet->body()->y = m_entity->body()->y;
	bullet->body()->angle = m_entity->body()->angle;
	bullet->physics()->thrust(10);
	m_entity->entityCreated(bullet);
	bullet->destroyed.Connect(this,&Gun::onBulletDied);

//	m_bullets.push_back(bullet);

	Weapon::fire();
}

void Gun::onBulletDied(Entity* bullet)
{
	printf("Gun destroyed entity %d\n",bullet);
	bullet->destroyed.Disconnect(this,&Gun::onBulletDied);
//	delete bullet;

	ammo++;
	//m_entities.remove(entity);
//	if(entity->view())
//	{
//		m_views.remove(entity->view());
//	}
}

