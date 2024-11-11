#pragma once
#include "ResourceManager.h"
#include "GameManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>
class LeaderboardWindow
{
private:
	sf::RenderWindow window;
public:
	LeaderboardWindow();
	void PollWindow();
};

