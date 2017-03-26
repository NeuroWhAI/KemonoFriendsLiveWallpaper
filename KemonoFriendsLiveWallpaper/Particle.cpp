#include "Particle.h"




Particle::Particle()
	: life(100)
	, vel(0, 0)
	, scale(1.0f)
	, scaleVel(0.0f)
	, angle(0.0f)
	, angleVel(0.0f)
{
	vertex.color = sf::Color(255, 255, 255, 255);
}

//###################################################################################################

void Particle::update()
{
	if (life > 0)
	{
		--life;
	}
	else
	{
		--vertex.color.a;
	}

	this->vertex.position += vel;

	scale += scaleVel;

	angle += angleVel;
	if (angle >= 360.0f)
		angle -= 360.0f;
	else if (angle < 0.0f)
		angle += 360.0f;
}

//###################################################################################################

bool Particle::isDead() const
{
	return (vertex.color.a <= 0);
}

