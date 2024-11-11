#pragma once
#include "Button.h"
#include "LeaderboardWindow.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "LeaderBoardWindow.h"
#include "Tile.h"
#include <iostream>
#include <list>
#include <random>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
class GameWindow
{
private:
	std::vector<std::vector<Tile*>> tiles;
	std::vector<Tile*> mineTiles;
	LeaderboardWindow leaderboardWindow;
public:
	GameWindow();
	void GenerateGrid(int, int, int);
	void ResetGame();
};