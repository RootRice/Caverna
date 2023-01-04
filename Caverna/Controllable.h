#pragma once
#include <SFML/Graphics.hpp>
class Controllable
{
public:
	virtual void Input(const sf::Event&, const sf::Vector2f&) = 0;
	Controllable();
private:

protected:
	enum keys
	{
		w, a, s, d, num_keys = d
	};
	bool keys_pressed[5];


	
};

