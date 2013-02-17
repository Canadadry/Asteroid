/*
 * HUD.cpp
 *
 * Asteroid - Copyright (c) 18 févr. 2013 - Jerome Mourey
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
 *  Created on: 18 févr. 2013
 */

#include "HUD.h"
#include <Game/AsteroidGame.h>
#include <Engine/View.h>


extern std::string path;

HUD::HUD()
: Entity()
, m_text()
{

	m_font.loadFromFile(path+"/visitor1.ttf");
	setView(new View(this));
	view()->drawable=&m_text;
	m_text.setColor(sf::Color::White);
	m_text.setCharacterSize(20);
	m_text.setFont(m_font);
	m_text.move(10,0);
}

HUD::~HUD()
{
}

void HUD::update()
{
	char text[255] = {0};
	AsteroidGame* agame = (AsteroidGame*)game;
	sprintf(text,"health : %1d score : %03d",agame->shipHealth,agame->score);
	m_text.setString(text);

}


