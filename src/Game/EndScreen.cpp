/*
 * EndScreen.cpp
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

#include "EndScreen.h"
#include <SFML/Window/Keyboard.hpp>
#include <Game/AsteroidGame.h>


extern int window_width;
extern int window_height;
extern std::string path;


EndScreen::EndScreen(int score)
:Screen()
, m_text()
, m_font()
, m_clock()
{
	m_font.loadFromFile(path+"visitor1.ttf");
	m_text.setColor(sf::Color::White);
	m_text.setCharacterSize(90);
	m_text.setFont(m_font);
	m_text.move(100,100);

	char text[255] = {0};
	sprintf(text,"score : %04d",score);
	m_text.setString(text);

	m_clock.restart();

}

EndScreen::~EndScreen()
{
}

void EndScreen::render(sf::RenderTarget* screen_surface)
{
	screen_surface->draw(m_text);
}

void EndScreen::update(int elapsedTimeMS)
{

}

void EndScreen::handleEvent(const sf::Event& event)
{
	if(m_clock.getElapsedTime().asMilliseconds() >  3000)
	{
		if(event.type == sf::Event::KeyPressed)
		{
			setNextScreen(new AsteroidGame(window_width,window_height));
		}
	}
}
