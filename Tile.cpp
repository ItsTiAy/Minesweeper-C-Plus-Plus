#include "Tile.h"

Tile::Tile(float x, float y, sf::Texture& tileUpTexture) : Button(x, y, tileUpTexture)
{
    sprite.setTexture(tileUpTexture);
    sprite.setPosition(x, y);

    pausedSprite.setTexture(ResourceManager::GetTexture("tile_revealed.png"));
    pausedSprite.setPosition(x, y);

    flagSprite.setTexture(ResourceManager::GetTexture("flag.png"));
    flagSprite.setPosition(x, y);

    mineSprite.setTexture(ResourceManager::GetTexture("mine.png"));
    mineSprite.setPosition(x, y);

    numberSprite.setPosition(x, y);

    Click = [&]() -> bool
    {
        if (isRevealed)
        {
            return true;
        }

        GameManager::IncreaseNumTilesRevealed();

        isRevealed = true;

        sprite.setTexture(ResourceManager::GetTexture("tile_revealed.png"));

        if (adjacentMinesCount > 0)
        {
            numberSprite.setTexture(ResourceManager::GetTexture("number_" + std::to_string(adjacentMinesCount) + ".png"));
            return true;
        }
        
        if (adjacentMinesCount == -1)
        {
            return false;
        }

        for (Tile* tile : adjacentTiles)
        {
            tile -> Click();
        }
        
        return true;
    };
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

void Tile::Draw(sf::RenderWindow& window)
{
    if ((GameManager::GetState() == GameManager::GameState::Paused || 
         GameManager::GetState() == GameManager::GameState::LeaderboardOpen) &&
         GameManager::GetPreviousState() != GameManager::GameState::Win)
    {
        window.draw(pausedSprite);
    }
    else
    {
        window.draw(sprite);
        window.draw(numberSprite);

        if (isFlagged)
        {
            window.draw(flagSprite);
        }

        if (adjacentMinesCount == -1 && GameManager::DebugOn())
        {
            window.draw(mineSprite);
        }
    }

    if (GameManager::GetState() == GameManager::GameState::Lose)
    {
        if (adjacentMinesCount == -1)
        {
            window.draw(mineSprite);
            sprite.setTexture(ResourceManager::GetTexture("tile_revealed.png"));
            isRevealed = true;
        }
    }
}

void Tile::ToggleFlagged()
{
    if (!isRevealed)
    {
        isFlagged = !isFlagged;

        isFlagged ? GameManager::DecreaseFlagsRemaining() : GameManager::IncreaseFlagsRemaining();

        std::cout << GameManager::GetNumTilesFlagged() << std::endl;
    }
}