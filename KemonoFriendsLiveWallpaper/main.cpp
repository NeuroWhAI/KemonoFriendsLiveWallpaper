#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#ifndef _DEBUG
#include <Windows.h>
#endif

#include "Wallpaper.h"




int main()
{
#ifndef _DEBUG
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif


	Wallpaper wallpaper;


	sf::RenderWindow window(sf::VideoMode(wallpaper.getSize().x, wallpaper.getSize().y),
		"Kemono Friends Live Wallpaper", sf::Style::None);
	window.setFramerateLimit(60); // 60fps


	sf::Clock clock;


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		float framerate = static_cast<float>(clock.restart().asMilliseconds()) * 0.06f;

		if (framerate > 2.0f)
			framerate = 2.0f;


		wallpaper.update(framerate);


		window.clear();
		
		wallpaper.draw(window, sf::RenderStates::Default);

		window.display();
	}


	return 0;
}

