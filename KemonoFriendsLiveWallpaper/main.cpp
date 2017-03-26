#include <iostream>

#include <SFML/Graphics.hpp>

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
		"Kemono Friends Live Wallpaper");
	window.setFramerateLimit(120); // 120fps


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		wallpaper.update();


		window.clear();
		
		wallpaper.draw(window, sf::RenderStates::Default);

		window.display();
	}


	return 0;
}

