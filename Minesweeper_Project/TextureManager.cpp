#include "TextureManager.h"
#include <iomanip>
#include <iostream>
#include <sstream> 
#include <vector>
#include <fstream>
using namespace std;

unordered_map<string, sf::Texture> TextureManager::textures; //redeclare static variable

void TextureManager::LoadImage(string fileName)
{
	string filePath = "images/";
	filePath += fileName;
	filePath += ".png";
	textures[fileName].loadFromFile(filePath); 
}

sf::Texture& TextureManager::GetImage(string key) {
	if (textures.find(key) == textures.end()) {
		LoadImage(key);
	}
	return textures[key];
}

void TextureManager::Clear() {
	textures.clear();
}