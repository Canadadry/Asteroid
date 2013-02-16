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
{
	m_clock.restart();
	ammo = 5;
}

Gun::~Gun()
{
}

void Gun::fire()
{
	if( ammo <= 0 ) return;
	if(m_clock.getElapsedTime().asMilliseconds() < cadence) return;
	m_clock.restart();

	Bullet* bullet = new Bullet();
	bullet->body()->x = m_entity->body()->x;
	bullet->body()->y = m_entity->body()->y;
	bullet->body()->x -= sin(-m_entity->body()->angle) * (m_entity->body()->radius + bullet->body()->radius + 1);
	bullet->body()->y -= cos(-m_entity->body()->angle) * (m_entity->body()->radius + bullet->body()->radius + 1);
	bullet->body()->angle = m_entity->body()->angle;
	bullet->physics()->thrust(-10);
	bullet->destroyed.Connect(this,&Gun::onBulletDied);
	m_entity->entityCreated(bullet);

	Weapon::fire();
}

void Gun::onBulletDied(Entity* bullet)
{
	ammo++;
}

