#include "GameManager.h"

GameManager::GameState GameManager::state;
GameManager::GameState GameManager::previousState;

std::chrono::steady_clock::time_point GameManager::start;

bool GameManager::debug = false;

int GameManager::tilesRevealed = 0;
int GameManager::flagsRemaining;
int GameManager::time;

// Sets the games state
void GameManager::SetState(GameState newState)
{
    state = newState;
}

// Returns the games current state
GameManager::GameState GameManager::GetState()
{
    return state;
}

// Stores a state to be accessed later
void GameManager::SetPreviousState(GameState newState)
{
    previousState = newState;
}

// Returns the stored state
GameManager::GameState GameManager::GetPreviousState()
{
    return previousState;
}

// Returns true if debug mode is on false otherwise
bool GameManager::IsDebugOn()
{
    return debug;
}

// Toggles the debug mode on and off
void GameManager::ToggleDebug()
{
    debug = !debug;
}

// Return the number of tiles that have been revealed
int GameManager::GetNumTilesRevealed()
{
    return tilesRevealed;
}

// Increase the number of tiles revealed by 1
void GameManager::IncreaseNumTilesRevealed()
{
    tilesRevealed++;
}

// Returns the number of tiles that have a flag 
int GameManager::GetNumTilesFlagged()
{
    return flagsRemaining;
}

// Increases the number of tiles flagged by 1
void GameManager::IncreaseFlagsRemaining()
{
    flagsRemaining++;
}

// Decreases the number of tiles flagged by 1
void GameManager::DecreaseFlagsRemaining()
{
    flagsRemaining--;
}

// Returns if the game state is one at the end of the game 
bool GameManager::IsGameOver()
{
    return state == GameState::Win || state == GameState::Lose;
}

// Starts the timer 
void GameManager::ResumeTimer()
{
    if (state != GameState::Playing)
    {
        start = std::chrono::high_resolution_clock::now();
    }
}

// Pauses the timer
void GameManager::PauseTimer()
{
    if (state != GameState::Paused)
    {
        auto now = std::chrono::high_resolution_clock::now();
        time += std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
    }
}

// Resets the timer to 0
void GameManager::ResetTimer()
{
    start = std::chrono::high_resolution_clock::now();
    time = 0;
}

// Returns the current value of the timer
int GameManager::GetTime()
{ 
    if ((state != GameState::Paused) && !IsGameOver())
    {
        auto now = std::chrono::high_resolution_clock::now();
        return time + std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
    }
    else
    {
        return time;
    }
}

// Resets all values used in the game
void GameManager::ResetData()
{
    tilesRevealed = 0;
    flagsRemaining = ResourceManager::GetMines();
    debug = false;

    state = GameState::Playing;
    ResetTimer();
}

// Sets text so that its position is central
void GameManager::SetTextPosition(sf::Text& text, float x, float y)
{
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x, y));
}