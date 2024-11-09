#pragma once
#include "GameWindow.h"
#include "ResourceManager.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
class WelcomeWindow
{
public:
	WelcomeWindow();
	void SetTextPosition(sf::Text&, float, float);
};