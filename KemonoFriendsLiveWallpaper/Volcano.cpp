#include "Volcano.h"




Volcano::Volcano(const sf::Vector2f& position)
	: m_position(position)
	, m_spreadGage(256.0f)
	, m_flowGage(256.0f)

	, m_senseEngine1(m_texSense, 700, 0)
	, m_senseEngine2(m_texSense, 700, 400)
	, m_senseEngine3(m_texSense, 400, 100)
	, m_senseEngine4(m_texSense, 400, 100)

	, m_randEngine(std::random_device()())
{
	m_texBigSandstar.loadFromFile("Res/Img/big_sandstar.png");
	m_texBigSandstar.setSmooth(true);

	m_texVolcano.loadFromFile("Res/Img/volcano.png");
	m_texVolcano.setSmooth(true);

	m_texSense.loadFromFile("Res/Img/sense.png");
	m_texSense.setSmooth(true);

	m_sprVolcano.setTexture(m_texVolcano);


	m_spreadTemplates.emplace_back(std::make_unique<Sandstar>(m_texBigSandstar, 32));
	m_spreadTemplates.back()->setParticleLife(60);
	m_spreadTemplates.back()->shoot(m_position + sf::Vector2f(-60, 0),
	{ -0.5f, -0.2f }, { 0.002f, -0.001f });

	m_spreadTemplates.emplace_back(std::make_unique<Sandstar>(m_texBigSandstar, 250));
	m_spreadTemplates.back()->setParticleLife(200);
	m_spreadTemplates.back()->shoot(m_position + sf::Vector2f(-45, 0),
	{ -0.09f, -0.16f }, { 0.0f, 0.0f });
	m_spreadTemplates.back()->setMulScale(0.9f);

	m_spreadTemplates.emplace_back(std::make_unique<Sandstar>(m_texBigSandstar, 48));
	m_spreadTemplates.back()->setParticleLife(120);
	m_spreadTemplates.back()->shoot(m_position + sf::Vector2f(-20, 0),
	{ -0.4f, -0.3f }, { 0.0024f, -0.001f });
	m_spreadTemplates.back()->setMulScale(0.9f);

	m_spreadTemplates.emplace_back(std::make_unique<Sandstar>(m_texBigSandstar, 32));
	m_spreadTemplates.back()->setParticleLife(80);
	m_spreadTemplates.back()->shoot(m_position + sf::Vector2f(30, 0),
	{ 0.01f, -0.2f }, { -0.0001f, -0.001f });

	m_spreadTemplates.emplace_back(std::make_unique<Sandstar>(m_texBigSandstar, 56));
	m_spreadTemplates.back()->setParticleLife(80);
	m_spreadTemplates.back()->shoot(m_position + sf::Vector2f(30, 0),
	{ 0.2f, -0.1f }, { -0.0003f, -0.0003f });
	m_spreadTemplates.back()->setMulScale(0.7f);

	m_spreadTemplates.emplace_back(std::make_unique<Sandstar>(m_texBigSandstar, 48));
	m_spreadTemplates.back()->setParticleLife(80);
	m_spreadTemplates.back()->shoot(m_position + sf::Vector2f(60, 0),
	{ 0.8f, -0.2f }, { -0.004f, -0.001f });

	m_spreadTemplates.emplace_back(std::make_unique<Sandstar>(m_texBigSandstar, 32));
	m_spreadTemplates.back()->setParticleLife(80);
	m_spreadTemplates.back()->shoot(m_position + sf::Vector2f(30, 0),
	{ -0.003f, -0.02f }, { -0.0004f, -0.001f });


	m_flowTemplates.emplace_back(std::make_unique<Sandstar>(m_texBigSandstar, 32));
	m_flowTemplates.back()->setParticleLife(80);
	m_flowTemplates.back()->shoot(m_position,
	{ 0.0f, -0.002f }, { 0.0f, 0.0f });

	m_flowTemplates.emplace_back(std::make_unique<Sandstar>(m_texBigSandstar, 150));
	m_flowTemplates.back()->setParticleLife(200);
	m_flowTemplates.back()->shoot(m_position + sf::Vector2f(-30, 0),
	{ -0.008f, -0.002f }, { 0.0f, -0.0001f });

	m_flowTemplates.emplace_back(std::make_unique<Sandstar>(m_texBigSandstar, 150));
	m_flowTemplates.back()->setParticleLife(200);
	m_flowTemplates.back()->shoot(m_position + sf::Vector2f(30, 0),
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

	m_senseEngine3.setStartLife(1424);
	m_senseEngine3.setStartPosition(m_position + sf::Vector2f(16, 8));
	m_senseEngine3.setStartVelocity({ 0.0f, -0.08f });
	m_senseEngine3.setAcceleration({ 0.0f, 0.0f });
	m_senseEngine3.setRandomPositionScale({ 50.0f, 16.0f });

	m_senseEngine4.setStartLife(1424);
	m_senseEngine4.setStartPosition(m_position + sf::Vector2f(-70, 0));
	m_senseEngine4.setStartVelocity({ -0.06f, -0.06f });
	m_senseEngine4.setAcceleration({ 0.00004f, 0.0f });
	m_senseEngine4.setRandomPositionScale({ 24.0f, 16.0f });


	m_randomSpread = std::uniform_int_distribution<>(0, static_cast<int>(m_spreadTemplates.size()) - 1);
	m_randomFlow = std::uniform_int_distribution<>(0, static_cast<int>(m_flowTemplates.size()) - 1);
}

//###################################################################################################

void Volcano::update(float framerate)
{
	for (auto& star : m_sandstars)
	{
		star->update(framerate);
	}


	auto endItr = std::remove_if(m_sandstars.begin(), m_sandstars.end(),
		[](auto& particle)
	{
		return particle->isDead();
	});
	m_sandstars.erase(endItr, m_sandstars.end());


	m_spreadGage += framerate;
	if (m_spreadGage >= 32)
	{
		m_spreadGage = 0;


		const auto& templ = m_spreadTemplates[m_randomSpread(m_randEngine)];
		m_sandstars.emplace_front(std::make_unique<Sandstar>(*templ));
	}


	m_flowGage += framerate;
	if (m_flowGage >= 16)
	{
		m_flowGage = 0;


		const auto& templ = m_flowTemplates[m_randomFlow(m_randEngine)];
		m_sandstars.emplace_front(std::make_unique<Sandstar>(*templ));
	}


	m_senseEngine1.update(framerate);
	m_senseEngine2.update(framerate);
	m_senseEngine3.update(framerate);
	m_senseEngine4.update(framerate);
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
	m_senseEngine3.draw(target, states);
	m_senseEngine4.draw(target, states);
}

