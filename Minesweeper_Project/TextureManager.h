#pragma once

#include <SFML/Graphics.hpp>
#include "Board.h"
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;

class TextureManager {
private:
	static unordered_map<string, sf::Texture> textures;
public:
	static void LoadImage(string fileName);
	static sf::Texture& GetImage(string textureKey);
	static void Clear();
};