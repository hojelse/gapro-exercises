#include <iostream>
#include <chrono>
#include <random>

#include "ITUGames.h"

#pragma region Engine State

class GameEngine
{
	public:
		std::chrono::time_point<std::chrono::steady_clock> frame_time_end = std::chrono::steady_clock::now();
		std::chrono::duration<double> render_time_elapsed = std::chrono::duration<double>(1.0);
		std::chrono::duration<double> frame_time_elapsed = std::chrono::duration<double>(1.0);
		static constexpr int target_fps = 60;

	void PrintPerformanceInfo()
	{
		ITUGames::Console::GotoTop();

		char buffer [100];

		snprintf(buffer, 100, "theoretical fps: %f\n", 1.0 / render_time_elapsed.count());
		ITUGames::Console::PrintStr(buffer);
		snprintf(buffer, 100, "utilization: %.1f%%\n", (render_time_elapsed.count() / frame_time_elapsed.count()) * 100.0);
		ITUGames::Console::PrintStr(buffer);
		snprintf(buffer, 100, "Render Time: %f\n", render_time_elapsed.count() / frame_time_elapsed.count());
		ITUGames::Console::PrintStr(buffer);
		snprintf(buffer, 100, "Actual FPS: %f (target: %d)\n", 1.0 / frame_time_elapsed.count(), target_fps);
		ITUGames::Console::PrintStr(buffer);
	}
};

GameEngine game_engine;

#pragma endregion // Engine State

#pragma region Game State

/**
* If you are unsure how to organize the additional variables you will need for the exercise, just dump them here.We will address this in future lectures
* In the meantime, a good approach is to sort them and put the ones that relate to the same thing togheter
* - is this variable part of the game? Of the engine? ...
* - is it about input? Player state? Logging? ...
* And so on. Are some of those questions conflicting with each other? Yep, architecturing code is hard, but we'll get a hang of it.
*/

class GameState
{
	public:
		char character_symbol = '0';
		int x = 10;
		int y = 10;
		std::chrono::time_point<std::chrono::steady_clock> time_of_last_blink = std::chrono::steady_clock::now();
};

GameState game_state;

#pragma endregion // Game State

void LongComputation();
void ProcessEvents();
void Update();
void Render();

int main() {
	// initialize random generator
	std::srand(std::time(nullptr)); 

	// cleans the terminal and prepares it for interactive input
	ITUGames::Console::InitScreenForRendering();

	// initialize engine state
	game_engine.frame_time_end = std::chrono::steady_clock::now();

	// fixed game loop
	while (true)
	{
		ProcessEvents();
		Update();
		Render();

		game_engine.PrintPerformanceInfo();

		game_engine.render_time_elapsed = std::chrono::steady_clock::now() - game_engine.frame_time_end;
		ITUGames::Utils::PreciseSleep(std::chrono::duration<double, std::ratio<1, game_engine.target_fps>>(1) - game_engine.render_time_elapsed);
		game_engine.frame_time_elapsed = std::chrono::steady_clock::now() - game_engine.frame_time_end;
		game_engine.frame_time_end = std::chrono::steady_clock::now();
	}

	return 0;
}

void ProcessEvents()
{
	auto c = ITUGames::Console::GetCharacter(false);

	if (c == '\033') { // arrow key
		ITUGames::Console::GetCharacter(false); // throw away '['
		c = ITUGames::Console::GetCharacter(false);
	}

	switch (c) {
		case ITUGames::Console::KEY_LEFT:
		case ITUGames::Console::KEY_A:
			game_state.x--;
			break;
		case ITUGames::Console::KEY_RIGHT:
		case ITUGames::Console::KEY_D:
			game_state.x++;
			break;
		case ITUGames::Console::KEY_DOWN:
		case ITUGames::Console::KEY_S:
			game_state.y++;
			break;
		case ITUGames::Console::KEY_UP:
		case ITUGames::Console::KEY_W:
			game_state.y--;
			break;
		default:
			break;
   }
}

void Update()
{
	// Make cursor blink every second
	auto now = std::chrono::steady_clock::now();

	if ((now - game_state.time_of_last_blink).count() > 1000000000)
	{
		game_state.time_of_last_blink = now;
		game_state.character_symbol =
			(game_state.character_symbol == '0')
				? 'O'
				: '0';
	}
}

void Render()
{
	ITUGames::Console::ClearScreen();
	ITUGames::Console::HideCursor();

	ITUGames::Console::GotoCoords(game_state.x, game_state.y);
	ITUGames::Console::RenderCharacter(game_state.character_symbol);

	ITUGames::Console::RenderCharacter('\n'); // should be at the bottom, else no characters will be rendered
}

void LongComputation()
{
	// get a random number between 0.01 and 0.016
	double sleep_time = (10 + std::rand() % 6) / 1000.0;

	ITUGames::Utils::PreciseSleep(std::chrono::duration<double>(sleep_time));
}
