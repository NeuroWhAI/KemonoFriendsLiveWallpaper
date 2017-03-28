#include "Particle.h"




Particle::Particle()
	: life(100)
	, position(0, 0)
	, color(255, 255, 255)
	, alpha(255.0f)
	, vel(0, 0)
	, scale(1.0f)
	, scaleVel(0.0f)
	, angle(0.0f)
	, angleVel(0.0f)
{
	
}

//###################################################################################################

void Particle::update(float framerate)
{
	if (life > 0.0f)
	{
		life -= framerate;
	}
	else
	{
		alpha -= framerate;

		if (alpha < 0.0f)
			alpha = 0.0f;
	}

	position += vel * framerate;

	scale += scaleVel * framerate;

	angle += angleVel * framerate;
	if (angle >= 360.0f)
		angle -= 360.0f;
	else if (angle < 0.0f)
		angle += 360.0f;
}

//###################################################################################################

bool Particle::isDead() const
{
	return (alpha <= 0.0f);
}

