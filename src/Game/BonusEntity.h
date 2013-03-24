/*
 * BonusEntity.h
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

#ifndef BONUSENTITY_H_
#define BONUSENTITY_H_

#include <Engine/Entity.h>
#include <Engine/Body.h>
namespace sf{
	class Sprite;
	class Texture;
}

class Attraction;

class Bonus;
class BonusEntity: public Entity, public CollisionHandler
{
public:

	enum BonusType{
			HealthBonus   =0,
			RayBonus        ,
			PiercingBonus   ,
			LenghtBonus     ,
			BonusCount
	};

	static const std::string bonusName[BonusCount];

	BonusEntity();
	virtual ~BonusEntity();

	int type() const;

	virtual bool HandleCollision(Body* body);
	virtual void update();

private:
    sf::Sprite*  m_shape;
    sf::Texture* m_texture;
	int          m_age;
	int          m_type;

	static Attraction* m_shipAttraction;

};

#endif /* BONUSENTITY_H_ */
