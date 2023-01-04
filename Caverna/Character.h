#pragma once
#include "Moveable.h"
#include "Updateable.h"
#include "Utils.cpp"
#include "Controllable.h"
#include "Drawable.h"

class Character :
	public Moveable, Updateable, Controllable, Drawable
{
public:
	Character(Params::Moveable base_params, Params::Character params);
	Character(Params::Moveable base_params, float speed);

	void SetSprite(sf::Texture& texture);

	void Update() override;

	void Draw(sf::RenderWindow& window) override;

	void Input(const sf::Event& e, const sf::Vector2f& mouse_position) override;

private:
	float min_speed;
	float max_speed;

	sf::Sprite sprite;
	sf::RectangleShape sq;
	sf::Vector2f facing_direction;

	enum innate_force {movement};


};

