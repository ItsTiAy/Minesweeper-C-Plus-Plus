#include "Tile.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

Tile::Tile(float x, float y, sf::Texture& tileUpTexture, sf::Texture& tileDownTexture, sf::Font& font)
{
    this->tileUpTexture = tileUpTexture;
    this->tileDownTexture = tileDownTexture;

    sprite.setTexture(this->tileUpTexture);
    sprite.setPosition(x, y);

    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(20);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x + 8, y + 8));

    name = "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

std::string Tile::GetName()
{
    return name;
}

void Tile::IncreaseAdjacentMinesCount()
{
    adjacentMinesCount++;
}

void Tile::AddAdjacentTile(Tile* tile)
{
    adjacentTiles.push_back(tile);
}

int Tile::GetAdjacentMinesCount()
{
    return adjacentMinesCount;
}

void Tile::SetAsMine()
{
    adjacentMinesCount = -1;
}

void Tile::RevealTile()
{
    if (isRevealed)
    {
        return;
    }

    isRevealed = true;

    sprite.setTexture(tileDownTexture);

    if (adjacentMinesCount > 0)
    {
        text.setString(std::to_string(adjacentMinesCount));
        return;
    }

    for (Tile* tile : adjacentTiles)
    {
        tile->RevealTile();
    }
}

void Tile::Draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    window.draw(text);
}

bool Tile::IsMouseOver(const sf::Vector2f& mousePos)
{
    return sprite.getGlobalBounds().contains(mousePos);
}