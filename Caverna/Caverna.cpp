#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "TextureList.h"
#include "Character.h"
#include "CircleCollider.h"
#include "Collision.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
	TextureList::AddTexture("test.png");
	Params::Moveable p{ 1.0f, 0.95f, 1.0f };

	Character man(p, 0.5f);
	man.SetSprite(TextureList::GetTexture("test.png"));

	sf::RectangleShape rec(sf::Vector2f(50, 50));
	rec.setPosition(300, 300);
	rec.setOrigin(25, 25);
	rec.setFillColor(sf::Color::Red);
	CircleCollider circ2(25.0f, rec.getPosition());

	sf::RectangleShape rec2(sf::Vector2f(50, 50));
	rec2.setPosition(500, 100);
	rec2.setOrigin(25, 25);
	rec2.setFillColor(sf::Color::Red);
	CircleCollider circ3(25.0f, rec2.getPosition());

	CircleCollider circ(20.0f, man.sprite.getPosition());

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
			//std::cout << circ.GetPos().x << " " << circ.GetPos().y << std::endl;
			elapsed_time -= 3333;
		}

		window.clear();
		man.Draw(window);
		window.draw(rec);
		window.draw(rec2);
		circ.DebugCollider(window);
		circ2.DebugCollider(window);
		circ3.DebugCollider(window);
		Collision::TestCollisions(window);
		window.display();
	}


	return 0;
}