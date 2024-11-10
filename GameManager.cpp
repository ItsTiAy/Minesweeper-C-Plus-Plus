#include "GameManager.h"

GameManager::GameState GameManager::state;
bool GameManager::debug = false;
int GameManager::tilesRevealed = 0;
int GameManager::flagsRemaining;
int GameManager::time;
std::chrono::steady_clock::time_point GameManager::start;

void GameManager::Initialize()
{
    flagsRemaining = ResourceManager::GetMines();
}

void GameManager::SetState(GameState newState)
{
    state = newState;
}

GameManager::GameState GameManager::GetState()
{
    return state;
}

bool GameManager::DebugOn()
{
    return debug;
}

void GameManager::ToggleDebug()
{
    debug = !debug;
}

int GameManager::GetNumTilesRevealed()
{
    return tilesRevealed;
}

void GameManager::IncreaseNumTilesRevealed()
{
    tilesRevealed++;
}

int GameManager::GetNumTilesFlagged()
{
    return flagsRemaining;
}

void GameManager::IncreaseFlagsRemaining()
{
    flagsRemaining++;
}

void GameManager::DecreaseFlagsRemaining()
{
    flagsRemaining--;
}

bool GameManager::IsGameOver()
{
    return state == GameState::Win || state == GameState::Lose;
}

void GameManager::ResumeTimer()
{
    start = std::chrono::high_resolution_clock::now();
}

void GameManager::PauseTimer()
{
    auto now = std::chrono::high_resolution_clock::now();
    time += std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
}

void GameManager::ResetTimer()
{
    start = std::chrono::high_resolution_clock::now();
    time = 0;
}

int GameManager::GetTime()
{ 
    if (state != GameState::Paused)
    {
        auto now = std::chrono::high_resolution_clock::now();
        return time + std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
    }
    else
    {
        return time;
    }
}