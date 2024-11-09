#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "WelcomeWindow.h"
#include "ResourceManager.h"

int main()
{
    ResourceManager::LoadConfig();
    ResourceManager::LoadFont("arial.ttf");
    ResourceManager::LoadTexture("face_happy.png");
    ResourceManager::LoadTexture("debug.png");
    ResourceManager::LoadTexture("pause.png");
    ResourceManager::LoadTexture("play.png");
    ResourceManager::LoadTexture("leaderboard.png"); 
    ResourceManager::LoadTexture("tile_up.png");
    ResourceManager::LoadTexture("tile_down.png");

    std::cout << ResourceManager::GetColumns() << std::endl;
    std::cout << ResourceManager::GetRows() << std::endl;

    WelcomeWindow welcomeWindow;

    return 0;
}