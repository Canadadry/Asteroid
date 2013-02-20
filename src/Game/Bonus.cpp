/*
 * Bonus.cpp
 *
 * Asteroid - Copyright (c) 20 fŽvr. 2013 - Jerome Mourey
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
 *  Created on: 20 fŽvr. 2013
 */

#include "Bonus.h"


Bonus::Bonus(int duration_time,int type,int value)
: m_clock()
, m_duration_time(duration_time)
, m_type(type)
, m_value(value)
{
	m_clock.restart();
}

Bonus::~Bonus(){}

bool Bonus::update()
{
	bool ret = false;
	if(m_clock.getElapsedTime().asMilliseconds() > m_duration_time)
	{
		m_type =0;
		m_value =0;
		ret = true;
	}
	return ret;
}

int Bonus::type() {	return m_type; }
int Bonus::value(){	return m_value; }

