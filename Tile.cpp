#include "Tile.h"

Tile::Tile(float x, float y, sf::Texture& tileUpTexture) : Button(x, y, tileUpTexture)
{
    // Sets textures and positions
    sprite.setTexture(tileUpTexture);
    sprite.setPosition(x, y);

    pausedSprite.setTexture(ResourceManager::GetTexture("tile_revealed.png"));
    pausedSprite.setPosition(x, y);

    flagSprite.setTexture(ResourceManager::GetTexture("flag.png"));
    flagSprite.setPosition(x, y);

    mineSprite.setTexture(ResourceManager::GetTexture("mine.png"));
    mineSprite.setPosition(x, y);

    numberSprite.setPosition(x, y);

    // For when a mine is clicked
    Click = [&]() -> bool
    {
        // A mutex to ensure thread-safe access to shared state
        static std::mutex mutex;

        if (isRevealed)
        {
            return true;
        }

        {
            std::lock_guard<std::mutex> lock(mutex);
            isRevealed = true;
            GameManager::IncreaseNumTilesRevealed();
        }

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

        // Use multithreading to process all adjacent tiles in parallel
        // Store futures representing asynchronous tasks
        std::vector<std::future<void>> futures;

        for (Tile* tile : adjacentTiles)
        {
            if (tile && !tile -> isRevealed)
            {
                // Spawn a new asynchronous task to click the adjacent tile
                futures.push_back(std::async(std::launch::async, [tile]()
                {
                    tile->Click();
                }));
            }
        }

        // Wait for all asynchronous tasks to complete before proceeding
        for (auto & future : futures)
        {
            // Synchronize each future, ensuring the task has completed
            future.get();
        }
        
        return true;
    };
}

// Increased the adjacent mines count by 1
void Tile::IncreaseAdjacentMinesCount()
{
    adjacentMinesCount++;
}

// Adds a tile to the vector of adjacent tiles
void Tile::AddAdjacentTile(Tile* tile)
{
    adjacentTiles.push_back(tile);
}

// Returns the number of adjacent mines
int Tile::GetAdjacentMinesCount() const
{
    return adjacentMinesCount;
}

// Sets a tile as a mine by settings its adjacent mine count to -1
void Tile::SetAsMine()
{
    adjacentMinesCount = -1;
}

// Renders the tile on the window
void Tile::Draw(sf::RenderWindow& window)
{
    // Draws the paused sprite
    if ((GameManager::GetState() == GameManager::GameState::Paused || 
         GameManager::GetState() == GameManager::GameState::LeaderboardOpen) &&
         GameManager::GetPreviousState() != GameManager::GameState::Win)
    {
        window.draw(pausedSprite);
    }
    // If the game is not in a paused state
    else
    {
        window.draw(sprite);
        window.draw(numberSprite);

        if (isFlagged)
        {
            window.draw(flagSprite);
        }

        if (adjacentMinesCount == -1 && GameManager::IsDebugOn())
        {
            window.draw(mineSprite);
        }
    }

    // If the game has been lost
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

// Toggles the flag sprite on the tile
void Tile::ToggleFlagged()
{
    if (!isRevealed)
    {
        isFlagged = !isFlagged;

        isFlagged ? GameManager::DecreaseFlagsRemaining() : GameManager::IncreaseFlagsRemaining();

        std::cout << GameManager::GetNumTilesFlagged() << std::endl;
    }
}