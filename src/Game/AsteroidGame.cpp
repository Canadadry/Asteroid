/*
 * AsteroidGame.cpp
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

#include "AsteroidGame.h"
#include <Game/Ship.h>
#include <Game/IAShip.h>
#include <Game/Asteroid.h>
#include <Game/HUD.h>
#include <Game/EndScreen.h>

AsteroidGame::AsteroidGame(int window_width,int window_height)
: Game(window_width,window_height)
, score(0)
, shipHealth(5)
{
	int asteroidCount = 15;
	Entity* ship = new Ship();
	ship->setGamepad(new IAShip(ship));
	addEntity(ship);
	ship->destroyed.Connect(this,&AsteroidGame::loose);

	for(int i = 0; i<asteroidCount;i++ )
	{
		addEntity(new Asteroid());
	}
	addEntity(new HUD());
}

AsteroidGame::~AsteroidGame()
{
}

void AsteroidGame::loose(Entity* entity)
{
	setNextScreen(new EndScreen(score));
}




