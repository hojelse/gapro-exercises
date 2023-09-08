#pragma once

#include "ITUGames.h"
#include <list>

class GameState
{
	public:
		std::chrono::time_point<std::chrono::steady_clock> time_of_last_blink;
		char character_symbol;

		int min_x;
		int max_x;
		int min_y;
		int max_y;

		int x;
		int y;
		int dir;

		double player_speed;

		std::list<std::pair<int, int>> player_body;
	
	void Init()
	{
		time_of_last_blink = std::chrono::steady_clock::now();
		character_symbol = '0';
		x = 0;
		y = 8;
		dir = 2;

		min_x = 0;
		max_x = 50;
		min_y = 6;
		max_y = 35;

		player_speed = 1.0;

		player_body.push_back(std::pair<int,int>{x, y-2});
		player_body.push_back(std::pair<int,int>{x, y-1});
		player_body.push_back(std::pair<int,int>{x, y  });
	}

	void ProcessEvents()
	{
		auto c = ITUGames::Console::GetCharacter(false);

		if (c == '\033') { // arrow key
			ITUGames::Console::GetCharacter(false); // throw away '['
			c = ITUGames::Console::GetCharacter(false);
		}

		switch (c) {
			case ITUGames::Console::KEY_UP:
			case ITUGames::Console::KEY_W:
				if (dir != 2) dir = 0;
				break;
			case ITUGames::Console::KEY_RIGHT:
			case ITUGames::Console::KEY_D:
				if (dir != 3) dir = 1;
				break;
			case ITUGames::Console::KEY_DOWN:
			case ITUGames::Console::KEY_S:
				if (dir != 0) dir = 2;
				break;
			case ITUGames::Console::KEY_LEFT:
			case ITUGames::Console::KEY_A:
				if (dir != 1) dir = 3;
				break;
			case ITUGames::Console::KEY_1:
				player_speed *= 2;
				break;
			case ITUGames::Console::KEY_2:
				if (player_speed > 1) player_speed /= 2;
				break;
			default:
				break;
		}
	}

	void Update(double delta_time)
	{
		// Make cursor blink every second
		auto now = std::chrono::steady_clock::now();

		if ((now - time_of_last_blink).count() > 1000000000)
		{
			time_of_last_blink = now;
			character_symbol =
				(character_symbol == '0')
					? 'O'
					: '0';
		}

		double delta_dist = player_speed * delta_time;
		int delta_dist_discrete = floor(delta_dist);
		double delta_dist_residual = delta_dist - (1.0 * delta_dist_discrete);

		int old_x = x;
		int old_y = y;

		switch (dir) {
			case 0:
				y -= delta_dist_discrete;
				break;
			case 1:
				x += delta_dist_discrete;
				break;
			case 2:
				y += delta_dist_discrete;
				break;
			case 3:
				x -= delta_dist_discrete;
				break;
			default:
				break;
		}
		
		// if (x < min_x || y < min_y || x > max_x || y > max_y)
		// 	Init();

		if (
			x != old_x ||
			y != old_y
		) {
			player_body.push_back(std::pair<double, double>{x, y});
			player_body.pop_front();
		}
	}

	void Render()
	{
		ITUGames::Console::ClearScreen();
		ITUGames::Console::HideCursor();

		for (auto coord : player_body)
		{
			ITUGames::Console::GotoCoords(coord.first, coord.second);
			ITUGames::Console::RenderCharacter(character_symbol);
		}

		ITUGames::Console::RenderCharacter('\n'); // should be at the bottom, else no characters will be rendered
	}
};

GameState game_state;