#pragma once
#include "ResourceManager.h"
#include <chrono>
class GameManager
{
public:
	static void Initialize();
	enum GameState { Playing, Paused, LeaderboardOpen, Win, Lose };
	static void SetState(GameState);
	static GameState GetState();
	static void SetPreviousState(GameState);
	static GameState GetPreviousState();
	static bool DebugOn();
	static void ToggleDebug();
	static int GetNumTilesRevealed();
	static void IncreaseNumTilesRevealed();
	static int GetNumTilesFlagged();
	static void IncreaseFlagsRemaining();
	static void DecreaseFlagsRemaining();
	static bool IsGameOver();
	static void ResumeTimer();
	static void PauseTimer();
	static void ResetTimer();
	static int GetTime();

private:
	static GameState state;
	static GameState previousState;
	static bool debug;
	static int tilesRevealed;
	static int flagsRemaining;
	static int time;
	static std::chrono::steady_clock::time_point start;
};

