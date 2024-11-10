#include "GameManager.h"

GameManager::GameState GameManager::state;
bool GameManager::debug = false;
int GameManager::tilesRevealed = 0;
int GameManager::flagsRemaining;

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