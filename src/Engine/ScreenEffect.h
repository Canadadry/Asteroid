/*
 * Transition.h
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

#ifndef TRANSITION_H_
#define TRANSITION_H_

#include <SFML/Graphics.hpp>

class Screen;

class ScreenEffect
{
public:
	ScreenEffect(Screen* screen,int duration, sf::Vector2f startPos=sf::Vector2f(0.5,0.5));
	virtual ~ScreenEffect();


	virtual void display(sf::RenderTarget* screen_surface);
    virtual void update(int elapsedTimeMS);

    void setFragmentProgram(const std::string& filename);

    bool isPlaying() const;

private:
    sf::RenderTexture m_texture;
    sf::Shader        m_shader;
    sf::Sprite        m_sprite;
    int               m_duration;
    sf::Clock         m_clock;
    Screen*           m_screen;
    sf::Vector2f      m_startPos;

};

#endif /* TRANSITION_H_ */
