/*
 * MousePad.cpp
 *
 * Asteroid - Copyright (c) 21 févr. 2013 - Jerome Mourey
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
 *  Created on: 21 févr. 2013
 */

#include "MousePad.h"
#include <Engine/Entity.h>
#include <Engine/Weapon.h>
#include <Engine/Body.h>
#include <Engine/Physics.h>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>

#define PI 3.1415926535

namespace sf {
class RenderWindow;
}
extern sf::RenderWindow* main_window;

MousePad::MousePad(Entity* entity)
: GamePad(entity)
{
}

MousePad::~MousePad()
{
}

void MousePad::handleEvent(const sf::Event& Event)
{
}

void MousePad::update()
{
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_entity->physics()->thrust(-0.4);
	}
	else  if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		m_entity->physics()->thrust(0.4);
	}
	float dx = sf::Mouse::getPosition(*(const sf::Window*)main_window).x - m_entity->body()->x;
	float dy = sf::Mouse::getPosition(*(const sf::Window*)main_window).y - m_entity->body()->y;

	float angle = atan2(dy,dx) + PI/2;///PI*180.0;

	m_entity->body()->angle = angle;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_entity->weapon()->fire();
	}


}


