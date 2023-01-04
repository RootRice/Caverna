#ifndef TEXTURES
#define TEXTURES

#include "TextureList.h"
#include <iostream>

std::vector<sf::Texture> TextureList::textures;
std::vector<std::string> TextureList::texture_names;

void TextureList::AddTexture(std::string texture_name)
{
	const std::string file_path = "Resources/";
	texture_names.push_back(std::string(texture_name));

	const sf::Texture t;
	textures.push_back(t);

	if (!textures[textures.size() - 1].loadFromFile(file_path + texture_name))
	{
		std::cout << "ERROR: FAILED TO LOAD TEXTURE";
	}
}

sf::Texture& TextureList::GetTexture(std::string texture_name)
{
	const int texture_count = texture_names.size();
	int i = 0;
	for (i; i < texture_count; i++)
	{
		if (texture_names[i] == texture_name)
		{
			return textures[i];
		}
	}
}
#endif // !Textures
