/*
 * Asteroid.h
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

#ifndef ASTEROID_H_
#define ASTEROID_H_

#include <Engine/Entity.h>
#include <Engine/Body.h>

namespace sf{
	class CircleShape;
}


class Asteroid: public Entity, public CollisionHandler
{
public:
	Asteroid();
	virtual ~Asteroid();

	virtual bool HandleCollision(Body* body);
    virtual void update();


    void onHurt();

private:
    sf::CircleShape* m_shape;

};

#endif /* ASTEROID_H_ */
