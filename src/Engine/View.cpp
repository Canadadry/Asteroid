/*
 * View.cpp
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

#include "View.h"
#include <Engine/Entity.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>

View::View(Entity* entity)
: drawable(0)
, m_entity(entity)
{

}

View::~View()
{

}

void View::update()
{

}

void View::render(sf::RenderTarget& screen)
{
	screen.draw(*drawable);
}


