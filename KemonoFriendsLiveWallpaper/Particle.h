#ifndef __KEMONO_FRIENDS_LIVE_WALLPAPER__PARTICLE_H__
#define __KEMONO_FRIENDS_LIVE_WALLPAPER__PARTICLE_H__


#include <SFML/Graphics.hpp>




class Particle
{
public:
	Particle();


public:
	unsigned int life;
	sf::Vertex vertex;
	sf::Vector2f vel;
	float scale;
	float scaleVel;
	float angle;
	float angleVel;


public:
	void update();


public:
	bool isDead() const;
};


#endif