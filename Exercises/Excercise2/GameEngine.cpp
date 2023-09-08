#pragma once

#include "ITUGames.h"
#include "GameState.cpp"

class GameEngine
{
	public:
		std::chrono::time_point<std::chrono::steady_clock> frame_time_end = std::chrono::steady_clock::now();
		std::chrono::duration<double> render_time_elapsed = std::chrono::duration<double>(1.0);
		std::chrono::duration<double> frame_time_elapsed = std::chrono::duration<double>(1.0);
		static constexpr int target_fps = 60;

	void Init()
	{
		frame_time_end = std::chrono::steady_clock::now();
	}

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
		snprintf(buffer, 100, "x,y = (%f,%f) s= %f\n", floor(game_state.x), floor(game_state.y), game_state.player_speed);
		ITUGames::Console::PrintStr(buffer);
	}

	void SleepAndUpdatePerformanceInfo()
	{
		render_time_elapsed = std::chrono::steady_clock::now() - frame_time_end;

		ITUGames::Utils::PreciseSleep(std::chrono::duration<double, std::ratio<1, target_fps>>(1) - render_time_elapsed);

		frame_time_elapsed = std::chrono::steady_clock::now() - frame_time_end;
		frame_time_end = std::chrono::steady_clock::now();
	}
};

GameEngine game_engine;