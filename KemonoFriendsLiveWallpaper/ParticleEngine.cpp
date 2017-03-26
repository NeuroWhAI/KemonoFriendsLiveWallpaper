#include "ParticleEngine.h"

#include <algorithm>




ParticleEngine::ParticleEngine(const sf::Texture& texture, int birth, int birthOffset)
	: m_randEngine(std::random_device()())
	
	, m_texture(texture)
	
	, m_alive(true)
	, m_startLife(100)
	, m_startPosition(0, 0)
	, m_startVelocity(0, 0)
	, m_accel(0, 0)
	, m_birth(birth)
	, m_birthGage(birthOffset)
	, m_scale(1.0f)
	, m_mulScale(1.0f)
	, m_randomPositionScale(8.0f, 8.0f)
{
	
}


ParticleEngine::ParticleEngine(const ParticleEngine& org)
	: m_randEngine(org.m_randEngine)
	, m_rndDist(org.m_rndDist)

	, m_texture(org.m_texture)
	, m_sprite(org.m_sprite)

	, m_alive(org.m_alive)
	, m_startLife(org.m_startLife)
	, m_startPosition(org.m_startPosition)
	, m_startVelocity(org.m_startVelocity)
	, m_accel(org.m_accel)
	, m_birth(org.m_birth)
	, m_birthGage(org.m_birthGage)
	, m_scale(org.m_scale)
	, m_mulScale(org.m_mulScale)
{

}

//###################################################################################################

void ParticleEngine::update()
{
	if (m_alive)
	{
		birthParticle();
	}

	updateParticles();
	deleteDeadParticles();
}


void ParticleEngine::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(static_cast<float>(m_texture.getSize().x) / 2.0f,
		static_cast<float>(m_texture.getSize().y) / 2.0f);

	for (auto& particle : m_particles)
	{
		m_sprite.setPosition(particle->vertex.position);
		m_sprite.setScale(particle->scale, particle->scale);
		m_sprite.setColor(particle->vertex.color);
		m_sprite.setRotation(particle->angle);

		target.draw(m_sprite, states);
	}
}


void ParticleEngine::drawBlend(sf::RenderTarget& target, sf::RenderStates states, const sf::Color& color)
{
	states.blendMode = sf::BlendAdd;

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(static_cast<float>(m_texture.getSize().x) / 2.0f,
		static_cast<float>(m_texture.getSize().y) / 2.0f);

	for (auto& particle : m_particles)
	{
		m_sprite.setPosition(particle->vertex.position);
		m_sprite.setScale(particle->scale, particle->scale);
		m_sprite.setColor(color);
		m_sprite.setRotation(particle->angle);

		target.draw(m_sprite, states);
	}
}

//###################################################################################################

void ParticleEngine::birthParticle()
{
	++m_birthGage;
	if (m_birthGage >= m_birth)
	{
		m_birthGage = 0;


		auto particle = std::make_unique<Particle>();
		particle->life = m_startLife;
		particle->vertex.position = m_startPosition;
		particle->vertex.position += m_randomPositionScale * getRandomFloat();
		particle->scale = m_scale + m_scale * 0.3f * getRandomFloat();
		particle->scaleVel = -0.0001f * std::abs(getRandomFloat());
		particle->angle = 360.0f * std::abs(getRandomFloat());
		particle->angleVel = 0.08f * getRandomFloat();
		particle->vel = m_startVelocity;


		std::uniform_int_distribution<> idxDist{ 0, static_cast<int>(m_particles.size()) };
		int index = idxDist(m_randEngine);

		m_particles.insert(m_particles.begin() + index, std::move(particle));


		m_scale *= m_mulScale;
	}
}


void ParticleEngine::updateParticles()
{
	for (auto& particle : m_particles)
	{
		particle->update();
		
		particle->vel += m_accel;
	}
}


void ParticleEngine::deleteDeadParticles()
{
	auto endItr = std::remove_if(m_particles.begin(), m_particles.end(),
		[](auto& particle)
	{
		return particle->isDead();
	});
	m_particles.erase(endItr, m_particles.end());
}

//###################################################################################################

void ParticleEngine::setStartLife(int life)
{
	m_startLife = life;
}


void ParticleEngine::setStartPosition(const sf::Vector2f& pos)
{
	m_startPosition = pos;
}


void ParticleEngine::setStartVelocity(const sf::Vector2f& vel)
{
	m_startVelocity = vel;
}


void ParticleEngine::setAcceleration(const sf::Vector2f& accel)
{
	m_accel = accel;
}


void ParticleEngine::setMulScale(float scale)
{
	m_mulScale = scale;
}


void ParticleEngine::setRandomPositionScale(const sf::Vector2f& scale)
{
	m_randomPositionScale = scale;
}

//###################################################################################################

void ParticleEngine::stopBirth()
{
	m_alive = false;
}


std::size_t ParticleEngine::getParticleCount() const
{
	return m_particles.size();
}

//###################################################################################################

float ParticleEngine::getRandomFloat()
{
	int randInt = m_rndDist(m_randEngine) - m_rndDist.max() / 2;

	return (static_cast<float>(randInt) / static_cast<float>(m_rndDist.max() / 2));
}

