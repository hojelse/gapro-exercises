#pragma once

#include "ITUGames.h"
#include <list>

inline constexpr int mod(int a, int b) {
	return ((a % b) + b) % b;
}

class GameState
{
	public:
		std::chrono::time_point<std::chrono::steady_clock> time_of_last_tick;
		char character_symbol;
		int x;
		int y;
		int dir;
		int prev_dir;
		int dir_request;
		double player_speed;
		int player_body_length;
		std::list<std::pair<int, int>> player_body;

		int consumable_x;
		int consumable_y;

		int canvas_offset_x;
		int canvas_offset_y;
		int min_x;
		int max_x;
		int min_y;
		int max_y;

	void Init()
	{
		time_of_last_tick = std::chrono::steady_clock::now();
		character_symbol = '0';
		x = 0;
		y = 2;
		dir = 2;
		prev_dir = 2;
		dir_request = 2;
		player_speed = 1.0;
		player_body_length = 3;
		player_body = std::list<std::pair<int, int>>();

		for (int i = 0; i < player_body_length; i++)
			player_body.push_front(std::pair<int,int>{x, y-i});

		consumable_x = 20;
		consumable_y = 20;

		canvas_offset_x = 2;
		canvas_offset_y = 7;
		min_x = 0;
		max_x = 50;
		min_y = 0;
		max_y = 30;
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
				dir_request = 0;
				break;
			case ITUGames::Console::KEY_RIGHT:
			case ITUGames::Console::KEY_D:
				dir_request = 1;
				break;
			case ITUGames::Console::KEY_DOWN:
			case ITUGames::Console::KEY_S:
				dir_request = 2;
				break;
			case ITUGames::Console::KEY_LEFT:
			case ITUGames::Console::KEY_A:
				dir_request = 3;
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
		// tick rate
		auto now = std::chrono::steady_clock::now();
		if ((now - time_of_last_tick).count() <= 1000000000 / player_speed)
			return;
		time_of_last_tick = now;


		// character_symbol =
		// 	(character_symbol == '0')
		// 		? 'O'
		// 		: '0';

		int old_x = x;
		int old_y = y;

		if (prev_dir != (dir_request + 2) % 4) // if direction is not opposite
			dir = dir_request;

		switch (dir) {
			case 0:
				y = mod((y - 1), max_y);
				break;
			case 1:
				x = mod((x + 1), max_x);
				break;
			case 2:
				y = mod((y + 1), max_y);
				break;
			case 3:
				x = mod((x - 1), max_x);
				break;
			default:
				break;
		}


		bool out_of_bounds =
			x < min_x ||
			y < min_y ||
			x > max_x ||
			y > max_y;

		// if (out_of_bounds) Init();

		bool new_coordinate =
			x != old_x ||
			y != old_y;

		bool collision_between_consumable_and_head =
			consumable_x == x &&
			consumable_y == y;

		if (collision_between_consumable_and_head)
		{
			consumable_x = min_x + (std::rand() % (max_x - min_x));
			consumable_y = min_y + (std::rand() % (max_y - min_y));

			player_body_length++;
			player_speed++;
		}

		if (new_coordinate) {
			player_body.push_front(std::pair<int, int>{x, y});
			if (!collision_between_consumable_and_head)
				player_body.pop_back();
		}

		prev_dir = dir;
	}

	void Render()
	{
		ITUGames::Console::ClearScreen();
		ITUGames::Console::HideCursor();

		RenderChar('O', consumable_x, consumable_y);

		RenderChar('*', min_x-1, min_y-1);
		RenderChar('*', max_x+1, min_y-1);
		RenderChar('*', max_x+1, max_y+1);
		RenderChar('*', min_x-1, max_y+1);

		int i = 0x41;
		for (auto coord : player_body)
		{
			RenderChar(i++, coord.first, coord.second);
		}

		ITUGames::Console::RenderCharacter('\n'); // should be at the bottom, else no characters will be rendered
	}

	void RenderChar(char c, int x, int y)
	{
		ITUGames::Console::GotoCoords(canvas_offset_x + x, canvas_offset_y + y);
		ITUGames::Console::RenderCharacter(c);
	}
};

GameState game_state;