#include <SFML\Graphics.hpp>
#ifndef UTILS
#define UTILS


class Math
{
public:
	template<typename T>
	inline static T clamp(T pred, T min, T max)
	{
		const T t = pred < min ? min : pred;
		return t > max ? max : t;
	}

	inline static float lerp(float a, float b, float t)
	{
		return a + t * (b - a);
	}
	template<typename T>
	inline static float v_magnitude(const sf::Vector2<T>& vec)
	{
		const T vec_x = vec.x, vec_y = vec.y;
		return sqrt(vec_x*vec_x + vec_y * vec_y);
	}

	template<typename T>
	inline static sf::Vector2<T> v_normalise(const sf::Vector2<T>& vec)
	{
		const float magnitude = v_magnitude(vec);
		if (magnitude != 0)
		{
			return vec / magnitude;
		}
		return sf::Vector2<T>(0,0);
	}

	template<typename T>
	inline static float v_dot(const sf::Vector2<T>& a, const sf::Vector2<T>& b)
	{
		return a.x * b.x + a.y * b.y;
	}

	template<typename T>
	inline static bool v_non_zero(const sf::Vector2<T>& vec)
	{
		return v_magnitude(vec) > 0;
	}

private:
	Math() {};
};

namespace Params
{
	struct Moveable
	{
		float weight;
		float friction;
		float absorption;
	};

	struct Character
	{
		float min_speed;
		float max_speed;
	};
}
#endif // !Utils