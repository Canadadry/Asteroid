/*
 * Game.h
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

#ifndef GAME_H_
#define GAME_H_

#include "Screen.h"
#include <list>

class Screen;
class Entity;
class View;
class GamePad;

class Game: public Screen
{
public:
	Game();
	virtual ~Game();

	virtual void render(sf::RenderTarget* screen_surface);
	virtual void handleEvent(const sf::Event& Event) ;
    virtual void update(int elapsedTimeMS) ;

protected:
    void addEntity(Entity* entity);
	void destroyedEntity(Entity* entity);
    void onEntityDestroyed(Entity* entity);

private:
    std::list<Entity*>  m_entities_to_destroyed;
    std::list<Entity*>  m_entities;
    std::list<View*>    m_views;
    std::list<GamePad*> m_gamepads;


};

#endif /* GAME_H_ */
