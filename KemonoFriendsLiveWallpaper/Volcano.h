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
	std::vector<std::unique_ptr<Sandstar>> m_sandstarTemplates;
	const sf::Vector2f m_position;
	std::deque<std::unique_ptr<Sandstar>> m_sandstars;
	int m_gage;


private:
	ParticleEngine m_senseEngine1;
	ParticleEngine m_senseEngine2;


private:
	std::mt19937 m_randEngine;
	std::uniform_int_distribution<> m_randomIndex;


public:
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states);
};


#endif