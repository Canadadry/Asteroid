/*
 * Entity.h
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

#ifndef ENTITY_H_
#define ENTITY_H_


//#include <vector>

#include <Signal/Signal.h>

class Body;
class Physics;
class Health;
class Weapon;
class View;
class GamePad;
class Game;

namespace sf{
	class RenderTarget;
}



class Entity
{
public:
	Entity();
	virtual ~Entity();

	//ACTION
    virtual void update();

    // COMPONENTS
	Body*                body()          const;
	Health*              health()        const;
	Physics*             physics()       const;
	View*                view()          const;
	Weapon*              weapon()        const;
	GamePad*             gamepad()       const;
	void setBody         (Body* body);
	void setHealth       (Health* health);
	void setPhysics      (Physics* physics);
	void setView         (View* view);
	void setWeapon       (Weapon* weapon);
	void setGamepad      (GamePad* gamepad);

	// SIGNALS
	Signal1< Entity* >      entityCreated;
	Signal1< Entity* >      destroyed;

	Game*                   game;

private:
	Body*    m_body;
	Health*  m_health;
	Physics* m_physics;
	Weapon*  m_weapon;
	View*    m_view;
	GamePad* m_gamepad;

};

#endif /* ENTITY_H_ */
