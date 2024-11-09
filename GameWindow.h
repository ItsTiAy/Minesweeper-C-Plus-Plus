#pragma once
#include "Tile.h"
#include <vector>
class GameWindow
{
private:
	std::vector<std::vector<Tile*>> tiles;
	std::vector<Tile*> mineTiles;
	sf::Texture tileUpTexture;
	sf::Texture tileDownTexture;
	sf::Font font;
	sf::Texture happyFaceTexture;
	sf::Texture debugTexture;
	sf::Texture pauseTexture;
	sf::Texture playTexture;
	sf::Texture leaderboardTexture;
public:
	GameWindow();
	void GenerateGrid(int, int, int);
};