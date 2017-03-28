#ifndef __KEMONO_FRIENDS_LIVE_WALLPAPER__VOLCANO_H__
#define __KEMONO_FRIENDS_LIVE_WALLPAPER__VOLCANO_H__


#include <vector>
#include <deque>
#include <memory>
#include <random>

#include <SFML/Graphics.hpp>

#include "Sandstar.h"
#include "ParticleEngine.h"




class Volcano
{
public:
	Volcano(const sf::Vector2f& position);


private:
	sf::Texture m_texBigSandstar;
	sf::Texture m_texVolcano;
	sf::Texture m_texSense;

	sf::Sprite m_sprVolcano;


private:
	std::vector<std::unique_ptr<Sandstar>> m_spreadTemplates;
	std::vector<std::unique_ptr<Sandstar>> m_flowTemplates;
	float m_spreadGage;
	float m_flowGage;
	const sf::Vector2f m_position;
	std::deque<std::unique_ptr<Sandstar>> m_sandstars;


private:
	ParticleEngine m_senseEngine1;
	ParticleEngine m_senseEngine2;
	ParticleEngine m_senseEngine3;
	ParticleEngine m_senseEngine4;


private:
	std::mt19937 m_randEngine;
	std::uniform_int_distribution<> m_randomSpread;
	std::uniform_int_distribution<> m_randomFlow;


public:
	void update(float framerate);
	void draw(sf::RenderTarget& target, sf::RenderStates states);
};


#endif