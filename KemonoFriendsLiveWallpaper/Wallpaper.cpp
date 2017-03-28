#include "Wallpaper.h"




Wallpaper::Wallpaper()
	: m_cloudSpeed(0.03125f)

	, m_volcano({ 412.0f, 500.0f })
{
	m_texSky.loadFromFile("Res/Img/sky.png");
	m_texCloud.loadFromFile("Res/Img/cloud.png");

	m_texSky.setSmooth(true);
	m_texCloud.setSmooth(true);

	m_sprSky.setTexture(m_texSky);
	m_sprCloud.setTexture(m_texCloud);
	m_sprCloud2.setTexture(m_texCloud);

	m_sprCloud2.setPosition(-static_cast<float>(m_texCloud.getSize().x), 0);


	m_boardSize = m_texSky.getSize();
}

//###################################################################################################

void Wallpaper::update(float framerate)
{
	m_sprCloud.move(m_cloudSpeed * framerate, 0.0f);
	m_sprCloud2.move(m_cloudSpeed * framerate, 0.0f);

	if (m_sprCloud2.getPosition().x >= 0.0f)
	{
		m_sprCloud.move(-static_cast<float>(m_boardSize.x), 0);
		m_sprCloud2.move(-static_cast<float>(m_boardSize.x), 0);
	}


	m_volcano.update(framerate);
}


void Wallpaper::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	target.draw(m_sprSky, states);
	target.draw(m_sprCloud, states);
	target.draw(m_sprCloud2, states);

	m_volcano.draw(target, states);
}

//###################################################################################################

sf::Vector2u Wallpaper::getSize() const
{
	return m_boardSize;
}

