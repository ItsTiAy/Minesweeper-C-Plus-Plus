#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
class Tile
{
private:
    bool isFlagged = false;
    bool isRevealed = false;
    int adjacentMinesCount = 0;
    std::vector<Tile*> adjacentTiles;
    sf::Sprite sprite;
    std::string name;
    sf::Texture tileUpTexture;
    sf::Texture tileDownTexture;
    sf::Text text;
public:
    Tile(float, float, sf::Texture&, sf::Texture&, sf::Font&);
    void IncreaseAdjacentMinesCount();
    void AddAdjacentTile(Tile*);
    void RevealTile();
    void SetAsMine();
    int GetAdjacentMinesCount();
    void Draw(sf::RenderWindow& window);
    std::string GetName();
    bool IsMouseOver(const sf::Vector2f&);
};

