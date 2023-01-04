#pragma once
#include <vector>
#include <string>
#include <SFML\Graphics.hpp>
class TextureList
{
public:
	static void AddTexture(std::string texture_name);
	static sf::Texture& GetTexture(std::string texture_name);
private:
	static std::vector<sf::Texture> textures;
	static std::vector<std::string> texture_names;

	TextureList();
};

