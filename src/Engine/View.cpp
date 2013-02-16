/*
 * View.cpp
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

#include "View.h"
#include <Engine/Entity.h>
#include <Engine/Body.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/CircleShape.hpp>


#define PI 3.14151
//#define __DEBUG_DRAW__

View::View(Entity* entity)
: drawable(0)
, m_entity(entity)
, m_transformable()
, m_debugDraw(new sf::CircleShape(10))
{
	m_debugDraw->setFillColor(sf::Color::Red);
}

View::~View()
{

}

void View::update()
{
	m_transformable.setRotation(m_entity->body()->angle/PI*180.0 );
	m_transformable.setPosition(m_entity->body()->x,m_entity->body()->y);
	m_debugDraw->setRadius(m_entity->body()->radius);
	m_debugDraw->setOrigin(m_entity->body()->radius,m_entity->body()->radius);
}

void View::render(sf::RenderTarget& screen)
{
	sf::RenderStates states;
	states.transform = m_transformable.getTransform();
#ifdef __DEBUG_DRAW__
	screen.draw(*m_debugDraw,states);
#else
	screen.draw(*drawable,states);
#endif
}


