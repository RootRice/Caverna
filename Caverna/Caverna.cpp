#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "TextureList.h"
#include "Character.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
	TextureList::AddTexture("test.png");
	Params::Moveable p{ 1.0f, 0.95f, 1.0f };

	Character man(p, 0.5f);
	man.SetSprite(TextureList::GetTexture("test.png"));

	sf::Clock clock;
	float elapsed_time = 0.0f;
	while (window.isOpen())
	{
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			const sf::Vector2f mouse_pos(sf::Mouse::getPosition(window));
			if (event.type == sf::Event::Closed)
				window.close();

			man.Input(event, mouse_pos);
		}


		elapsed_time += clock.getElapsedTime().asMicroseconds();
		clock.restart();
		if (elapsed_time > 3333)
		{
			man.Update();
			elapsed_time -= 3333;
		}

		window.clear();
		man.Draw(window);
		window.display();
	}


	return 0;
}