#include <iostream>
#include <map>
#include <memory>
#include <cmath>

#include <SFML/Graphics.hpp>
#include <Engine/Screen.h>
#include <Game/AsteroidGame.h>
#include <cmath>
#include <INIReader/INIReader.h>

int window_width = 800;
int window_height = 600;

std::string path ;

Screen* currentScreen = 0;
sf::RenderWindow* main_window = 0;
INIReader* appConf;

int main(int argc, char** argv)
{

	bool hasFocus = true;
	srand(time(NULL));
	printf("build time %s\n",__TIME__);

	path = argv[0];
	path = path.substr(0,path.rfind("/"));
	path = path.substr(0,path.rfind("/"));
	path += "/Resources/";

	appConf = new INIReader(path+"settings.ini");

	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Asteroid",sf::Style::Titlebar | sf::Style::Close);
	main_window = &window;
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);
	sf::Clock clock;

	AsteroidGame game(800,600);
	currentScreen = &game;

	int elapsedTimeMS = 0;
	while (window.isOpen() && currentScreen != 0)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if(event.type == sf::Event::GainedFocus)
			{
				hasFocus = true;
			}
			else if(event.type == sf::Event::LostFocus)
			{
				hasFocus = false;
			}
			else
			{
				if(hasFocus)
				{
					currentScreen->handleEvent(event);
				}
			}
		}
		if(elapsedTimeMS >0)
		{
			if(hasFocus)
			{
				currentScreen->update(elapsedTimeMS);
			}
		}

		window.setActive(true);
		window.clear(sf::Color::Black);
		currentScreen->display(&window);
		window.display();
		elapsedTimeMS = clock.restart().asMilliseconds();

		if(currentScreen->isScreenFinished())
		{
			currentScreen = currentScreen->getNextScreen();
		}

	}

	return 0;
}
