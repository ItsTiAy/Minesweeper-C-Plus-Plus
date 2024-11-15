#pragma once
#include "ResourceManager.h"
#include "GameManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <iomanip>
class LeaderboardWindow
{
private:
	sf::RenderWindow window;
	sf::Text leaderboardText;
	sf::Text content;
public:
	LeaderboardWindow();
	void OpenWindow();
	void PollWindow();
	void UpdateLeaderboard(int);
};

