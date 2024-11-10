#pragma once
#include "ResourceManager.h"
class GameManager
{
public:
	static void Initialize();
	enum GameState { Playing, Paused, LeaderboardOpen, Win, Lose };
	static void SetState(GameState);
	static GameState GetState();
	static bool DebugOn();
	static void ToggleDebug();
	static int GetNumTilesRevealed();
	static void IncreaseNumTilesRevealed();
	static int GetNumTilesFlagged();
	static void IncreaseFlagsRemaining();
	static void DecreaseFlagsRemaining();
	static bool IsGameOver();

private:
	static GameState state;
	static bool debug;
	static int tilesRevealed;
	static int flagsRemaining;
};

