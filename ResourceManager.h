#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>
#include <fstream>

class ResourceManager
{
public:
	enum GameState {Playing, Paused};
	static bool LoadTexture(const std::string&);
	static bool LoadFont(const std::string&);
	static bool LoadConfig();
	static sf::Texture& GetTexture(const std::string&);
	static sf::Font& GetFont(const std::string&);
	static int GetColumns();
	static int GetRows();
	static int GetMines();
	static void SetState(GameState);
	static GameState GetState();

private:
	static std::unordered_map<std::string, sf::Texture> textures;
	static std::unordered_map<std::string, sf::Font> fonts;
	static int columns;
	static int rows;
	static int mines;
	static GameState state;
};

