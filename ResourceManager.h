#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <sstream>

class ResourceManager
{
public:
	static bool LoadTexture(const std::string&);
	static bool LoadFont(const std::string&);
	static bool LoadConfig();
	static sf::Texture& GetTexture(const std::string&);
	static sf::Font& GetFont(const std::string&);
	static int GetColumns();
	static int GetRows();
	static int GetMines();
	static bool LoadScores();
	static bool WriteScores(std::vector<std::pair<std::string, std::string>>);
	static std::vector<std::pair<std::string, std::string>> GetScores();
	static std::string GetPlayerName();
	static void SetPlayerName(std::string&);

private:
	static std::unordered_map<std::string, sf::Texture> textures;
	static std::unordered_map<std::string, sf::Font> fonts;
	static std::vector<std::pair<std::string, std::string>> scores;
	static int columns;
	static int rows;
	static int mines;
	static std::string playerName;
};

