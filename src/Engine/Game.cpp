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
#include <Engine/Physics.h>

#include <SFML/Window/Event.hpp>

#include <algorithm>

typedef  std::list<GamePad*>::iterator GamePad_it;
typedef  std::list<View*>::iterator View_it;
typedef  std::list<Entity*>::iterator Entity_it;
typedef  std::list<Physics*>::iterator Physic_it;


Game::Game(int window_width,int window_height)
: m_entities()
, m_window_width(window_width)
, m_window_height(window_height)
{
}

Game::~Game()
{
	for(Entity_it it = m_entities.begin(); it != m_entities.end();it++)
	{
		destroyedEntity(*it);
	}
}

void Game::addEntity(Entity* entity)
{
	Entity_it findIter = std::find(m_entities.begin(), m_entities.end(), entity);
	if(findIter != m_entities.end())
	{
		printf("entity already added!!!\n");
		return;
	}
	entity->game = this;
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
	if(entity->physics())
	{
		m_physics.push_front(entity->physics());
	}
	if(entity->body())
	{
		m_world.addBody(entity->body());
	}
}

void Game::onEntityDestroyed(Entity* entity)
{
	Entity_it findIter = std::find(m_entities_to_destroyed.begin(), m_entities_to_destroyed.end(), entity);

	if(findIter != m_entities_to_destroyed.end())
	{
		printf("entity already register to be destroyed!!!\n");
		return;
	}
	m_entities_to_destroyed.push_back(entity);
}



void Game::clear()
{
	for(Entity_it it = m_entities.begin(); it != m_entities.end();it++)
	{
		onEntityDestroyed(*it);
	}
}

void Game::destroyedEntity(Entity* entity)
{
	Entity_it findIter = std::find(m_entities_to_destroyed.begin(), m_entities_to_destroyed.end(), entity);

	if(findIter != m_entities_to_destroyed.end())
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
		if(entity->physics())
		{
			m_physics.remove(entity->physics());
		}
		if(entity->body())
		{
			m_world.removeBody(entity->body());
		}


		delete entity;
	}
}


void Game::handleEvent(const sf::Event& Event)
{
		for(GamePad_it it = m_gamepads.begin(); it != m_gamepads.end();it++)
		{
			(*it)->handleEvent(Event);
		}
}

void Game::render(sf::RenderTarget* screen_surface)
{

	for(View_it it = m_views.begin(); it != m_views.end();it++)
	{
		(*it)->update();
		(*it)->render(*screen_surface);
	}
}

void Game::update(int elapsedTimeMS)
{
	for(GamePad_it it = m_gamepads.begin(); it != m_gamepads.end();it++)
	{
		(*it)->update();
	}
	for(Physic_it it = m_physics.begin(); it != m_physics.end();it++)
	{
		(*it)->update(m_world );
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

int Game::windowHeight() const
{
	return m_window_height;
}

int Game::windowWidth() const
{
	return m_window_width;
}



