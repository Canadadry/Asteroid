/*
 * Transition.cpp
 *
 * TileGame - Copyright (c) 6 févr. 2013 - Jerome Mourey
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
 *  Created on: 6 févr. 2013
 */

#include "ScreenEffect.h"
#include "Screen.h"

extern int screen_width;
extern int screen_height;
extern int tile_size;

extern std::string path;

ScreenEffect::ScreenEffect(Screen* screen,int duration, sf::Vector2f startPos)
: m_texture()
, m_shader()
, m_sprite()
, m_duration(duration)
, m_clock()
, m_screen(screen)
, m_startPos(startPos)
{
	m_texture.create(screen_width*tile_size,screen_height*tile_size,false);
	m_sprite.setTexture(m_texture.getTexture());
	m_clock.restart();
	m_duration = 1000;
}

ScreenEffect::~ScreenEffect()
{

}

void ScreenEffect::setFragmentProgram(const std::string& filename)
{
	m_shader.loadFromFile(filename,sf::Shader::Fragment);
}

bool ScreenEffect::isPlaying() const
{
	return (m_clock.getElapsedTime().asMilliseconds()<m_duration);
}

void ScreenEffect::display(sf::RenderTarget* screen_surface)
{
	m_screen->render(&m_texture);
	m_texture.display();

	sf::RenderStates states;
	states.shader = &m_shader;
	screen_surface->draw(m_sprite,states);
}

void ScreenEffect::update(int elapsedTimeMS)
{
	if(isPlaying())
	{
		float factor =(float) m_clock.getElapsedTime().asMilliseconds()/(float)m_duration*1.2;
		m_shader.setParameter("texture",sf::Shader::CurrentTexture);
		m_shader.setParameter("factor",factor);
		m_shader.setParameter("center",m_startPos);
	}
}

