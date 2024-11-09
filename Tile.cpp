#include "Tile.h"

Tile::Tile(float x, float y, sf::Texture& tileUpTexture) : Button(x, y, tileUpTexture)
{
    sprite.setTexture(tileUpTexture);
    sprite.setPosition(x, y);

    text.setFont(ResourceManager::GetFont("arial.ttf"));
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(20);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x + 8, y + 8));

    name = "(" + std::to_string(x) + ", " + std::to_string(y) + ")";

    Click = [&]()
    {
        if (isRevealed)
        {
            return;
        }

        isRevealed = true;

        sprite.setTexture(ResourceManager::GetTexture("tile_down.png"));

        if (adjacentMinesCount > 0)
        {
            text.setString(std::to_string(adjacentMinesCount));
            return;
        }

        for (Tile* tile : adjacentTiles)
        {
            tile -> Click();
        }
    };
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

int Tile::GetAdjacentMinesCount() const
{
    return adjacentMinesCount;
}

void Tile::SetAsMine()
{
    adjacentMinesCount = -1;
}

void Tile::Draw(sf::RenderWindow& window) const
{
    window.draw(sprite);
    window.draw(text);
}