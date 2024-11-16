#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "WelcomeWindow.h"
#include "ResourceManager.h"
#include "GameManager.h"

int main()
{
    // Loads data
    ResourceManager::LoadConfig();
    ResourceManager::LoadScores();
    ResourceManager::LoadFont("font.ttf");
    ResourceManager::LoadTexture("face_happy.png");
    ResourceManager::LoadTexture("debug.png");
    ResourceManager::LoadTexture("pause.png");
    ResourceManager::LoadTexture("play.png");
    ResourceManager::LoadTexture("leaderboard.png"); 
    ResourceManager::LoadTexture("tile_hidden.png");
    ResourceManager::LoadTexture("tile_revealed.png");
    ResourceManager::LoadTexture("mine.png");
    ResourceManager::LoadTexture("digits.png");

    for (int i = 0; i < 8; i++)
    {
        ResourceManager::LoadTexture("number_" + std::to_string(i + 1) + ".png");
    }

    GameManager::ResetData();

    // Opens the welcome window
    WelcomeWindow welcomeWindow;

    return 0;
}