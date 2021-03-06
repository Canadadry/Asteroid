/*
 * AsteroidGame.cpp
 *
 * Asteroid - Copyright (c) 12 f�vr. 2013 - Jerome Mourey
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
 *  Created on: 12 f�vr. 2013
 */

#include "AsteroidGame.h"
#include <Game/Ship.h>
#include <Game/IAShip.h>
#include <Game/MousePad.h>
#include <Game/Asteroid.h>
#include <Game/HUD.h>
#include <Game/EndScreen.h>
#include <INIReader/INIReader.h>

extern INIReader* appConf;

AsteroidGame::AsteroidGame(int window_width,int window_height)
: Game(window_width,window_height)
, score(0)
, shipHealth(5)
, ship(new Ship)
, m_asteroidCount(0)
{
	int asteroidCount = 30;
//	Entity* ship = new Ship();

	if(appConf->GetBoolean("KEY","useMouse",false))
	{
		ship->setGamepad(new MousePad(ship));
	}
	else
	{
		ship->setGamepad(new IAShip(ship));
	}
	addEntity(ship);
	ship->destroyed.Connect(this,&AsteroidGame::ending);
	this->entityRemoved.Connect(this,&AsteroidGame::ending);
	this->entityAdded.Connect(this,&AsteroidGame::asteroidAdded);

	for(int i = 0; i<asteroidCount;i++ )
	{
		 addEntity(new Asteroid());
	}
	addEntity(new HUD());
}

AsteroidGame::~AsteroidGame()
{
}

void AsteroidGame::asteroidAdded(Entity* entity)
{
	if(entity->name == "Asteroid")
	{
		m_asteroidCount++;
	}
}

void AsteroidGame::ending(Entity* entity)
{
	if(entity == ship)
	{
		setNextScreen(new EndScreen(score));
	}
	else if(entity->name == "Asteroid")
	{
		m_asteroidCount--;
	}

	if(m_asteroidCount == 0)
	{
		setNextScreen(new EndScreen(score*2));
	}

}


void AsteroidGame::handleEvent(const sf::Event& event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		if(event.key.code == sf::Keyboard::R)
		{
			setNextScreen(new AsteroidGame(windowWidth(),windowHeight()));
		}
	}
	Game::handleEvent(event);
}




