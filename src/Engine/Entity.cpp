/*
 * Entity.cpp
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

#include "Entity.h"
#include <Engine/Body.h>
#include <Engine/Physics.h>

Entity::Entity()
: m_body         (0)
, m_health       (0)
, m_physics      (0)
, m_weapon       (0)
, m_view         (0)
, m_gamepad      (0)
//, m_group        (0)
//, m_targets      (0)
{
}

Entity::~Entity()
{
//	destroyed(this);
}


Body*                Entity::body()          const{ return m_body          ;}
View*                Entity::view()          const{ return m_view          ;}
Weapon*              Entity::weapon()        const{ return m_weapon        ;}
Health*              Entity::health()        const{ return m_health        ;}
Physics*             Entity::physics()       const{ return m_physics       ;}
GamePad*             Entity::gamepad()       const{ return m_gamepad       ;}

void Entity::setBody   (Body*    body   )         { m_body    = body   ; }
void Entity::setHealth (Health*  health )         { m_health  = health ; }
void Entity::setPhysics(Physics* physics)         { m_physics = physics; }
void Entity::setView   (View*    view   )         { m_view    = view   ; }
void Entity::setWeapon (Weapon*  weapon )         { m_weapon  = weapon ; }
void Entity::setGamepad(GamePad* gamepad)         { m_gamepad = gamepad; }



//std::vector<Entity*> Entity::group()         const{ return m_group         ;}
//std::vector<Entity*> Entity::targets()       const{ return m_targets       ;}

