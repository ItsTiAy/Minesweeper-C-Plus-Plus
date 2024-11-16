#pragma once
#include "Button.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include <fstream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <future>
class Tile : public Button
{
private:
    bool isFlagged = false;
    bool isRevealed = false;
    int adjacentMinesCount = 0;
    std::vector<Tile*> adjacentTiles;
    sf::Sprite numberSprite;
    sf::Sprite pausedSprite;
    sf::Sprite flagSprite;
    sf::Sprite mineSprite;
public:
    Tile(float, float, sf::Texture&);
    int GetAdjacentMinesCount() const;
    void IncreaseAdjacentMinesCount();
    void AddAdjacentTile(Tile*);
    void SetAsMine();
    void Draw(sf::RenderWindow& window) override;
    void ToggleFlagged();
};

