#ifndef __KEMONO_FRIENDS_LIVE_WALLPAPER__SANDSTAR_H__
#define __KEMONO_FRIENDS_LIVE_WALLPAPER__SANDSTAR_H__


#include <SFML/Graphics.hpp>

#include "ParticleEngine.h"




class Sandstar
{
public:
	Sandstar(const sf::Texture& texture, int birth);
	Sandstar(const Sandstar& org);


private:
	ParticleEngine m_particle;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_accel;
	int m_life;


public:
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states);


public:
	void setParticleLife(int life);
	void shoot(const sf::Vector2f& startPosition, const sf::Vector2f& startVelocity,
		const sf::Vector2f& accel);
	bool isDead() const;
};


#endif