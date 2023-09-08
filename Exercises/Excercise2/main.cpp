#include <iostream>
#include <chrono>
#include <random>

#include "ITUGames.h"
#include "GameEngine.cpp"
#include "GameState.cpp"

void LongComputation();
void ProcessEvents();
void Update();
void Render();

int main() {
	// initialize random generator
	std::srand(std::time(nullptr)); 

	// cleans the terminal and prepares it for interactive input
	ITUGames::Console::InitScreenForRendering();

	// initialize engine engine and game state
	game_engine.Init();
	game_state.Init();

	// fixed game loop
	while (true)
	{
		game_state.ProcessEvents();
		game_state.Update(game_engine.frame_time_elapsed.count());
		game_state.Render();

		game_engine.PrintPerformanceInfo();

		game_engine.SleepAndUpdatePerformanceInfo();
	}

	return 0;
}

void LongComputation()
{
	// get a random number between 0.01 and 0.016
	double sleep_time = (10 + std::rand() % 6) / 1000.0;

	ITUGames::Utils::PreciseSleep(std::chrono::duration<double>(sleep_time));
}
