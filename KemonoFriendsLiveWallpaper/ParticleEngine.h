#ifndef __KEMONO_FRIENDS_LIVE_WALLPAPER__PARTICLE_ENGINE_H__
#define __KEMONO_FRIENDS_LIVE_WALLPAPER__PARTICLE_ENGINE_H__


#include <vector>
#include <memory>
#include <random>

#include <SFML/Graphics.hpp>

#include "Particle.h"




class ParticleEngine
{
public:
	ParticleEngine(const sf::Texture& texture, int birth, int birthOffset = 0);
	ParticleEngine(const ParticleEngine& org);


private:
	std::mt19937 m_randEngine;
	std::uniform_int_distribution<> m_rndDist;


private:
	const sf::Texture& m_texture;
	sf::Sprite m_sprite;


private:
	bool m_alive;
	std::vector<std::unique_ptr<Particle>> m_particles;
	int m_startLife;
	sf::Vector2f m_startPosition;
	sf::Vector2f m_startVelocity;
	sf::Vector2f m_accel;
	const int m_birth;
	int m_birthGage;
	float m_scale;
	float m_mulScale;
	sf::Vector2f m_randomPositionScale;


public:
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states);
	void drawBlend(sf::RenderTarget& target, sf::RenderStates states, const sf::Color& color);


private:
	void birthParticle();
	void updateParticles();
	void deleteDeadParticles();


public:
	void setStartLife(int life);
	void setStartPosition(const sf::Vector2f& pos);
	void setStartVelocity(const sf::Vector2f& vel);
	void setAcceleration(const sf::Vector2f& accel);
	void setMulScale(float scale);
	void setRandomPositionScale(const sf::Vector2f& scale);


public:
	void stopBirth();
	std::size_t getParticleCount() const;


private:
	float getRandomFloat();
};


#endif