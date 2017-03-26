#include "Sandstar.h"




Sandstar::Sandstar(const sf::Texture& texture, int birth)
	: m_particle(texture, birth, birth)
	, m_position(0, 0)
	, m_velocity(0, 0)
	, m_accel(0, 0)
	, m_life(100)
{
	m_particle.setStartLife(100);
	m_particle.setMulScale(0.84f);
	m_particle.setRandomPositionScale({ 10.0f, 10.0f });
}


Sandstar::Sandstar(const Sandstar& org)
	: m_particle(org.m_particle)
	, m_position(org.m_position)
	, m_velocity(org.m_velocity)
	, m_accel(org.m_accel)
	, m_life(org.m_life)
{

}

//###################################################################################################

void Sandstar::update()
{
	m_position += m_velocity;
	m_velocity += m_accel;

	m_particle.setStartPosition(m_position);
	m_particle.setStartVelocity(m_velocity * 0.01f);


	m_particle.update();


	if (m_life > 0)
	{
		--m_life;

		if (m_life <= 0)
		{
			m_particle.stopBirth();
		}
	}
}


void Sandstar::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	m_particle.draw(target, states);
	m_particle.drawBlend(target, states, sf::Color(255, 242, 10, 4));
}

//###################################################################################################

void Sandstar::setParticleLife(int life)
{
	m_particle.setStartLife(life);

	m_life = life + 255;
}


void Sandstar::shoot(const sf::Vector2f& startPosition, const sf::Vector2f& startVelocity,
	const sf::Vector2f& accel)
{
	m_position = startPosition;
	m_velocity = startVelocity;
	m_accel = accel;
}


bool Sandstar::isDead() const
{
	return (m_life <= 0 && m_particle.getParticleCount() <= 0);
}

