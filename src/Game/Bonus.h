/*
 * Bonus.h
 *
 * Asteroid - Copyright (c) 20 févr. 2013 - Jerome Mourey
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
 *  Created on: 20 févr. 2013
 */

#ifndef BONUS_H_
#define BONUS_H_

#include  <Signal/Signal.h>
#include <SFML/System/Clock.hpp>

class Bonus
{
public:
	Bonus(int duration_time,int type,int value = 0);
	virtual ~Bonus();


	// return true if has expired
	virtual bool update();
	int type();
	int value();

private:
	sf::Clock m_clock;
	int m_duration_time;
	int m_type;
	int m_value;

};

#endif /* BONUS_H_ */
