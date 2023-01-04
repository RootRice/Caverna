#include "Character.h"
#include <iostream>

sf::Vector2f ClosestCardinalVector(sf::Vector2f vec);

Character::Character(Params::Moveable base_params, Params::Character params)
	: Moveable(base_params), min_speed(params.min_speed),max_speed(params.max_speed)
{
	static_forces.push_back(ConstantForce(sf::Vector2f(), 0));
}

Character::Character(Params::Moveable base_params, float speed)
	: Moveable(base_params), min_speed(speed/2),max_speed(speed)
{
	static_forces.push_back(ConstantForce(sf::Vector2f(), 0));
}

void Character::SetSprite(sf::Texture& texture)
{
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

void Character::Update()
{
	ApplyForces();
	sprite.setPosition(position);
}

void Character::Draw(sf::RenderWindow& window)
{

	sq.setSize(sf::Vector2f(5.0f, 5.0f));
	sq.setPosition(sf::Vector2f(position + (facing_direction * 100.0f)));
	sq.setFillColor(sf::Color::Red);
	window.draw(sprite);
	window.draw(sq);
}

void Character::Input(const sf::Event& e, const sf::Vector2f& mouse_position)
{
	bool should_dodge = false;
	if (e.type == sf::Event::KeyPressed)
	{
		const sf::Keyboard::Key pressed_key = e.key.code;
		
		switch (pressed_key)
		{
		case sf::Keyboard::Space:
			should_dodge = true;// AddActiveForce(facing_direction, 5.0f);
			break;
		case sf::Keyboard::W:
			keys_pressed[keys(w)] = true;
			break;
		case sf::Keyboard::A:
			keys_pressed[keys(a)] = true;
			break;
		case sf::Keyboard::S:
			keys_pressed[keys(s)] = true;
			break;
		case sf::Keyboard::D:
			keys_pressed[keys(d)] = true;
			break;
		default:
			break;
		}
	}
	if (e.type == sf::Event::KeyReleased)
	{
		const sf::Keyboard::Key released_key = e.key.code;

		switch (released_key)
		{
		case sf::Keyboard::W:
			keys_pressed[keys(w)] = false;
			break;
		case sf::Keyboard::A:
			keys_pressed[keys(a)] = false;
			break;
		case sf::Keyboard::S:
			keys_pressed[keys(s)] = false;
			break;
		case sf::Keyboard::D:
			keys_pressed[keys(d)] = false;
			break;
		default:
			break;
		}
	}
	
	
	sf::Vector2f movement_direction;
	const sf::Vector2f directions[4]{ sf::Vector2f(0.0f, -1.0f), sf::Vector2f(-1.0f, 0.0f), sf::Vector2f(0.0f, 1.0f), sf::Vector2f(1.0f, 0.0f) };
	for (int i = 0; i <= keys(num_keys); i++)
	{
		movement_direction += directions[i] * keys_pressed[i];
	}
	movement_direction = Math::v_normalise(movement_direction);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		facing_direction = ClosestCardinalVector(Math::v_normalise(mouse_position - position));
	else
		facing_direction = movement_direction;

	const float movedir_dot_facedir = Math::v_dot(movement_direction, facing_direction);
	const float adjusted_speed = Math::lerp(min_speed, max_speed, (movedir_dot_facedir+1)/2);
	static_forces[innate_force(movement)].SetForce(movement_direction, adjusted_speed);

	if(should_dodge)
		AddActiveForce(facing_direction, 5.0f);
}

sf::Vector2f ClosestCardinalVector(sf::Vector2f vec)
{
	
	const sf::Vector2f cardinal_directions[8]
	{
		sf::Vector2f(0.0f, 1.0f),//N
		sf::Vector2f(0.707f, 0.707f),//NE
		sf::Vector2f(1.0f, 0.0f), //E
		sf::Vector2f(0.707f, -0.707f), //SE
		sf::Vector2f(0.0f, -1.0f),//S
		sf::Vector2f(-0.707f, -0.707f),//SW
		sf::Vector2f(-1.0f, 0.0f), //W
		sf::Vector2f(-0.707f, 0.707f),//NW
	};
	//https://stackoverflow.com/questions/1437790/how-to-snap-a-directional-2d-vector-to-a-compass-n-ne-e-se-s-sw-w-nw
	const float x = vec.x;
	const float y = vec.y;
	double t = 0.392699082; // tan(M_PI/8.0);

	if (x >= 0)
	{
		if (y >= 0)
		{
			if (x > y) { if (y < t * x) return cardinal_directions[2]; }
			else { if (x < t * y) return cardinal_directions[0]; }
			return cardinal_directions[1];
		}
		else
		{
			if (-y < t * x) return cardinal_directions[2];
			if (x < -t * y) return cardinal_directions[4];
			return cardinal_directions[3];
		}
	}
	else
	{
		if (y >= 0)
		{
			if (y < -t * x) return cardinal_directions[6];
			if (-x < t * y) return cardinal_directions[0];
			return cardinal_directions[7];
		}
		else
		{
			if (-y < -t * x) return cardinal_directions[6];
			if (-x < -t * y) return cardinal_directions[4];
			return cardinal_directions[5];
		}
	}
	return cardinal_directions[2];

}

