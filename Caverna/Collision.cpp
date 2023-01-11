#include "Collision.h"
#include <iostream>

std::vector<std::reference_wrapper<Collider>> Collision::colliders;

void Collision::AddCollidable(Collider& collider)
{
	colliders.push_back(collider);
}

void Collision::RemoveCollidable(Collider& collider)
{
	const int num_colliders = colliders.size();
	for (int i = 0; i < num_colliders; i++)
	{
		if (&collider == &colliders[i].get())
		{
			std::swap(colliders[i], colliders[num_colliders - 1]);
			colliders.pop_back();
			return;
		}
	}
}



void Collision::TestCollisions(sf::RenderWindow& _window)
{
	float mean = 0;
	const int num_colliders = colliders.size();
	for (int i = 0; i < num_colliders; i++)
	{
		Collider& col_to_test = colliders[i].get();
		mean += col_to_test.GetPosition().x;
	}
	mean /= num_colliders;
	KD(mean, colliders, 0, _window);
}

void Collision::KD(float mean, std::vector<std::reference_wrapper<Collider>>& cols,  int depth, sf::RenderWindow& _window)
{
	const int num_cols = cols.size();

	float lesser_mean = 0;
	std::vector<std::reference_wrapper<Collider>> lesser_cols;
	lesser_cols.reserve(num_cols / 2);
	int num_lesser_cols = 0;

	float greater_mean = 0;
	std::vector<std::reference_wrapper<Collider>> greater_cols;
	greater_cols.reserve(num_cols / 2);
	int num_greater_cols = 0;


	if (depth % 2 == 0)
	{
		sf::RectangleShape s(sf::Vector2f((5*depth)+5, 100000));
		s.setPosition(mean, 0);
		s.setFillColor(sf::Color(10, 10, (255 * depth) + 50));
		s.setOrigin(5, 100000 / 2);
		_window.draw(s);
		for (int i = 0; i < num_cols; i++)
		{
			Collider& col_to_test = cols[i].get();
			if (col_to_test.GetPosition().x - col_to_test.GetRadius() < mean)
			{
				lesser_cols.push_back(col_to_test);
				lesser_mean += col_to_test.GetPosition().y;
			}
			if (col_to_test.GetPosition().x + col_to_test.GetRadius() > mean)
			{
				greater_cols.push_back(col_to_test);
				greater_mean += col_to_test.GetPosition().y;
			}
		}
		num_lesser_cols = lesser_cols.size();
		num_greater_cols = greater_cols.size();

		lesser_mean /= num_lesser_cols;
		greater_mean /= num_greater_cols;
	}
	else
	{
		sf::RectangleShape s(sf::Vector2f(100000, (5 * depth) + 5));
		s.setPosition(0, mean);
		s.setFillColor(sf::Color(10,10, (255 * depth) + 50));
		s.setOrigin(100000 / 2, 5);
		_window.draw(s);
		for (int i = 0; i < num_cols; i++)
		{
			Collider& col_to_test = cols[i].get();
			if (col_to_test.GetPosition().y - col_to_test.GetRadius() < mean)
			{
				greater_cols.push_back(col_to_test);
				greater_mean += col_to_test.GetPosition().x;
			}
			if (col_to_test.GetPosition().y + col_to_test.GetRadius() > mean)
			{
				lesser_cols.push_back(col_to_test);
				lesser_mean += col_to_test.GetPosition().x;
			}
		}
		num_lesser_cols = lesser_cols.size();
		num_greater_cols = greater_cols.size();

		lesser_mean /= num_lesser_cols;
		greater_mean /= num_greater_cols;
	}

	//Exit conditions
	//if (num_cols == num_lesser_cols && num_cols == num_greater_cols)
	//{
	//	Collider& x = cols[0].get();
	//	Collider& t = cols[1].get();
	//	std::cout << "COLLISION HAPPENED" << std::endl;
	//	//Do collisions
	//	return;
	//}
	//else
	//{
	//	std::cout << "NO COLLISION HAPPENED" << std::endl;
	//}
	if (Compare(lesser_cols, cols) && Compare(greater_cols, cols) && lesser_cols.size() > 1)
	{
		std::cout << "COLLISION HAPPENED" << std::endl; //DOESNT WORK
		return;
	}
	else
	{
		std::cout << "NO COLLISION HAPPENED" << std::endl;
	}
	if (num_lesser_cols > 1)
	{
		KD(lesser_mean, lesser_cols, depth + 1, _window);
	}
	if (num_greater_cols > 1)
	{
		KD(greater_mean, greater_cols, depth + 1, _window);
	}
}

bool Collision::Compare(std::vector<std::reference_wrapper<Collider>> a, std::vector<std::reference_wrapper<Collider>> b)
{
	const int num_a = a.size();
	const int num_b = b.size();
	int matches = 0;
	for (int i = 0; i < num_a; i++)
	{
		for (int j = 0; j < num_b; j++)
		{
			if (&a[i].get() == &b[j].get())
			{
				matches++;
			}
		}
	}

	return matches == num_a;
		
}
