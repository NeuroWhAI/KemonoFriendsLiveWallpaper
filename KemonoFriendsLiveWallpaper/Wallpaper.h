#ifndef __KEMONO_FRIENDS_LIVE_WALLPAPER__WALLPAPER_H__
#define __KEMONO_FRIENDS_LIVE_WALLPAPER__WALLPAPER_H__


#include <SFML/Graphics.hpp>

#include "Volcano.h"




class Wallpaper
{
public:
	Wallpaper();


private:
	sf::Vector2u m_boardSize;


private:
	const float m_cloudSpeed;

	sf::Texture m_texSky;
	sf::Texture m_texCloud;

	sf::Sprite m_sprSky;
	sf::Sprite m_sprCloud;
	sf::Sprite m_sprCloud2;


private:
	Volcano m_volcano;


public:
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states);


public:
	sf::Vector2u getSize() const;
};


#endif