#ifndef __KEMONO_FRIENDS_LIVE_WALLPAPER__PARTICLE_H__
#define __KEMONO_FRIENDS_LIVE_WALLPAPER__PARTICLE_H__


#include <SFML/Graphics.hpp>




class Particle
{
public:
	Particle();


public:
	float life;
	sf::Vector2f position;
	sf::Color color;
	float alpha;
	sf::Vector2f vel;
	float scale;
	float scaleVel;
	float angle;
	float angleVel;


public:
	void update(float framerate);


public:
	bool isDead() const;
};


#endif