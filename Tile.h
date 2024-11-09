#pragma once
#include "Button.h"
#include "ResourceManager.h"
#include <fstream>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
class Tile : public Button
{
private:
    bool isFlagged = false;
    bool isRevealed = false;
    int adjacentMinesCount = 0;
    std::vector<Tile*> adjacentTiles;
    std::string name;
    sf::Text text;
    sf::Sprite pausedSprite;
public:
    Tile(float, float, sf::Texture&);
    void IncreaseAdjacentMinesCount();
    void AddAdjacentTile(Tile*);
    void SetAsMine();
    int GetAdjacentMinesCount() const;
    void Draw(sf::RenderWindow& window) const override;
    std::string GetName();
    void ToggleFlagged();
};

