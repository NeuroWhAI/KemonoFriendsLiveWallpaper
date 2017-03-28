#ifndef __KEMONO_FRIENDS_LIVE_WALLPAPER__PARTICLE_ENGINE_H__
#define __KEMONO_FRIENDS_LIVE_WALLPAPER__PARTICLE_ENGINE_H__


#include <list>
#include <memory>
#include <random>

#include <SFML/Graphics.hpp>

#include "Particle.h"




class ParticleEngine
{
public:
	ParticleEngine(const sf::Texture& texture, int birth, int birthOffset = 0.0f);
	ParticleEngine(const ParticleEngine& org);


private:
	const sf::Texture& m_texture;
	sf::Sprite m_sprite;


private:
	bool m_alive;
	std::list<std::unique_ptr<Particle>> m_particles;
	int m_startLife;
	sf::Vector2f m_startPosition;
	sf::Vector2f m_startVelocity;
	sf::Vector2f m_accel;
	const float m_birth;
	float m_birthGage;
	float m_scale;
	float m_mulScale;
	float m_minScale;
	sf::Vector2f m_randomPositionScale;


public:
	void update(float framerate);
	void draw(sf::RenderTarget& target, sf::RenderStates states);
	void drawBlend(sf::RenderTarget& target, sf::RenderStates states, const sf::Color& color);


private:
	void birthParticle(float framerate);
	void updateParticles(float framerate);
	void deleteDeadParticles();


public:
	void setStartLife(int life);
	void setStartPosition(const sf::Vector2f& pos);
	void setStartVelocity(const sf::Vector2f& vel);
	void setAcceleration(const sf::Vector2f& accel);
	void setMulScale(float scale);
	void setMinScale(float limit);
	void setRandomPositionScale(const sf::Vector2f& scale);


public:
	void stopBirth();
	std::size_t getParticleCount() const;
};


#endif