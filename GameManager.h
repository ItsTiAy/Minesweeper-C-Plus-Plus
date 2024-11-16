#pragma once
#include "ResourceManager.h"
#include <chrono>
class GameManager
{
public:
	enum GameState { Playing, Paused, LeaderboardOpen, Win, Lose };
	static void SetState(GameState);
	static GameState GetState();
	static void SetPreviousState(GameState);
	static GameState GetPreviousState();
	static bool IsDebugOn();
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
	static void SetTextPosition(sf::Text&, float, float);
	static void ResetData();

private:
	static GameState state;
	static GameState previousState;
	static bool debug;
	static int tilesRevealed;
	static int flagsRemaining;
	static int time;
	static std::chrono::steady_clock::time_point start;
};

