/*
 * Game.cpp
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

#include "Game.h"
#include <Engine/Entity.h>
#include <Engine/View.h>
#include <Engine/GamePad.h>

#include <SFML/Window/Event.hpp>

Game::Game()
: m_entities()
{
}

Game::~Game()
{
}

void Game::addEntity(Entity* entity)
{
	//printf("entity created called\n");
	entity->entityCreated.Connect(this,&Game::addEntity);
	entity->destroyed.Connect(this,&Game::onEntityDestroyed);
	m_entities.push_back(entity);
	if(entity->view())
	{
		m_views.push_front(entity->view());
	}
	if(entity->gamepad())
	{
		m_gamepads.push_front(entity->gamepad());
	}
}

void Game::onEntityDestroyed(Entity* entity)
{
	
	m_entities_to_destroyed.push_back(entity);
}


void Game::destroyedEntity(Entity* entity)
{
	m_entities.remove(entity);
	if(entity->view())
	{
		m_views.remove(entity->view());
	}
	if(entity->gamepad())
	{
		m_gamepads.remove(entity->gamepad());
	}
	delete entity;
}

typedef  std::list<GamePad*>::iterator GamePad_it;
void Game::handleEvent(const sf::Event& Event)
{
//	for(GamePad_it it = m_gamepads.begin(); it != m_gamepads.end();it++)
//	{
//		(*it)->handleEvent(Event);
//	}
}

typedef  std::list<View*>::iterator View_it;
void Game::render(sf::RenderTarget* screen_surface)
{
	for(View_it it = m_views.begin(); it != m_views.end();it++)
	{
		(*it)->render(*screen_surface);
	}
}

typedef  std::list<Entity*>::iterator Entity_it;
void Game::update(int elapsedTimeMS)
{
	sf::Event Event;
	for(GamePad_it it = m_gamepads.begin(); it != m_gamepads.end();it++)
	{
		(*it)->handleEvent(Event);
	}

	for(Entity_it it = m_entities.begin(); it != m_entities.end();it++)
	{
		(*it)->update();
	}
	for(Entity_it it = m_entities_to_destroyed.begin(); it != m_entities_to_destroyed.end();it++)
	{
		destroyedEntity(*it);
	}
	m_entities_to_destroyed.clear();
}


