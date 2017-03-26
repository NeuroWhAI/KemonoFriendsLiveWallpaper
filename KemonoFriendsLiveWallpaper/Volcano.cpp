#include "Volcano.h"




Volcano::Volcano(const sf::Vector2f& position)
	: m_position(position)
	, m_gage(256)

	, m_senseEngine1(m_texSense, 700, 0)
	, m_senseEngine2(m_texSense, 700, 400)

	, m_randEngine(std::random_device()())
{
	m_texBigSandstar.loadFromFile("Res/Img/big_sandstar.png");
	m_texBigSandstar.setSmooth(true);

	m_texVolcano.loadFromFile("Res/Img/volcano.png");
	m_texVolcano.setSmooth(true);

	m_texSense.loadFromFile("Res/Img/sense.png");
	m_texSense.setSmooth(true);

	m_sprVolcano.setTexture(m_texVolcano);


	m_sandstarTemplates.emplace_back(std::make_unique<Sandstar>(m_texBigSandstar, 32));
	m_sandstarTemplates[0]->setParticleLife(60);
	m_sandstarTemplates[0]->shoot(m_position + sf::Vector2f(-60, 0),
	{ -0.4f, -0.2f }, { 0.002f, -0.001f });

	m_sandstarTemplates.emplace_back(std::make_unique<Sandstar>(m_texBigSandstar, 24));
	m_sandstarTemplates[1]->setParticleLife(120);
	m_sandstarTemplates[1]->shoot(m_position + sf::Vector2f(-30, 0),
	{ -0.2f, -0.3f }, { 0.0014f, -0.001f });

	m_sandstarTemplates.emplace_back(std::make_unique<Sandstar>(m_texBigSandstar, 32));
	m_sandstarTemplates[2]->setParticleLife(80);
	m_sandstarTemplates[2]->shoot(m_position + sf::Vector2f(30, 0),
	{ 0.01f, -0.2f }, { -0.0001f, -0.001f });

	m_sandstarTemplates.emplace_back(std::make_unique<Sandstar>(m_texBigSandstar, 24));
	m_sandstarTemplates[3]->setParticleLife(80);
	m_sandstarTemplates[3]->shoot(m_position + sf::Vector2f(60, 0),
	{ 0.8f, -0.2f }, { -0.004f, -0.001f });

	m_sandstarTemplates.emplace_back(std::make_unique<Sandstar>(m_texBigSandstar, 32));
	m_sandstarTemplates[4]->setParticleLife(120);
	m_sandstarTemplates[4]->shoot(m_position + sf::Vector2f(-30, 0),
	{ -0.002f, -0.02f }, { 0.0004f, -0.001f });

	m_sandstarTemplates.emplace_back(std::make_unique<Sandstar>(m_texBigSandstar, 32));
	m_sandstarTemplates[5]->setParticleLife(80);
	m_sandstarTemplates[5]->shoot(m_position + sf::Vector2f(30, 0),
	{ -0.003f, -0.02f }, { -0.0004f, -0.001f });

	m_sandstarTemplates.emplace_back(std::make_unique<Sandstar>(m_texBigSandstar, 32));
	m_sandstarTemplates[6]->setParticleLife(80);
	m_sandstarTemplates[6]->shoot(m_position,
	{ 0.0f, -0.002f }, { 0.0f, 0.0f });

	m_sandstarTemplates.emplace_back(std::make_unique<Sandstar>(m_texBigSandstar, 150));
	m_sandstarTemplates[7]->setParticleLife(200);
	m_sandstarTemplates[7]->shoot(m_position + sf::Vector2f(-20, 0),
	{ -0.008f, -0.002f }, { 0.0f, -0.0001f });

	m_sandstarTemplates.emplace_back(std::make_unique<Sandstar>(m_texBigSandstar, 150));
	m_sandstarTemplates[8]->setParticleLife(200);
	m_sandstarTemplates[8]->shoot(m_position + sf::Vector2f(20, 0),
	{ 0.008f, -0.002f }, { 0.0f, -0.0001f });


	m_senseEngine1.setStartLife(1124);
	m_senseEngine1.setStartPosition(m_position + sf::Vector2f(-25, 8));
	m_senseEngine1.setStartVelocity({ 0.0f, -0.06f });
	m_senseEngine1.setAcceleration({ 0.0f, 0.0f });
	m_senseEngine1.setRandomPositionScale({ 50.0f, 16.0f });

	m_senseEngine2.setStartLife(1124);
	m_senseEngine2.setStartPosition(m_position + sf::Vector2f(25, 8));
	m_senseEngine2.setStartVelocity({ 0.0f, -0.06f });
	m_senseEngine2.setAcceleration({ 0.0f, 0.0f });
	m_senseEngine2.setRandomPositionScale({ 50.0f, 16.0f });


	m_randomIndex = std::uniform_int_distribution<>(0, static_cast<int>(m_sandstarTemplates.size()) - 1);
}

//###################################################################################################

void Volcano::update()
{
	for (auto& star : m_sandstars)
	{
		star->update();
	}


	auto endItr = std::remove_if(m_sandstars.begin(), m_sandstars.end(),
		[](auto& particle)
	{
		return particle->isDead();
	});
	m_sandstars.erase(endItr, m_sandstars.end());


	++m_gage;
	if (m_gage >= 16)
	{
		m_gage = 0;


		const auto& templ = m_sandstarTemplates[m_randomIndex(m_randEngine)];
		m_sandstars.emplace_front(std::make_unique<Sandstar>(*templ));
	}


	m_senseEngine1.update();
	m_senseEngine2.update();
}


void Volcano::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	for (auto& star : m_sandstars)
	{
		star->draw(target, states);
	}


	target.draw(m_sprVolcano, states);


	m_senseEngine1.draw(target, states);
	m_senseEngine2.draw(target, states);
}

