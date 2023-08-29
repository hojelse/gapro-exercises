#include <iostream>
#include <chrono>
#include <random>

#include "ITUGames.h"

#pragma region Engine State

std::chrono::time_point<std::chrono::steady_clock>	time_start;
std::chrono::time_point<std::chrono::steady_clock>	time_end;
std::chrono::duration<double>						time_elapsed;

#pragma endregion // Engine State

#pragma region Game State

/**
* If you are unsure how to organize the additional variables you will need for the exercise, just dump them here.We will address this in future lectures
* In the meantime, a good approach is to sort them and put the ones that relate to the same thing togheter
* - is this variable part of the game? Of the engine? ...
* - is it about input? Player state? Logging? ...
* And so on. Are some of those questions conflicting with each other? Yep, architecturing code is hard, but we'll get a hang of it.
*/

#pragma endregion // Game State

void LongComputation();

int main() {
	// initialize random generator
	std::srand(std::time(nullptr)); 

	// cleans the terminal and prepares it for interactive input
	ITUGames::Console::InitScreenForRendering();

	time_start = std::chrono::steady_clock::now();

	LongComputation();

	time_end = std::chrono::steady_clock::now();
	time_elapsed = time_end - time_start;
	
	std::cout << "Elapsed : " << time_elapsed.count() << std::endl;
	std::cout << "FPS     : " << 1.0 / time_elapsed.count() << std::endl;

	return 0;
}

void LongComputation()
{
	// get a random number between 0.01 and 0.016
	double sleep_time = (10 + std::rand() % 6) / 1000.0;

	ITUGames::Utils::PreciseSleep(std::chrono::duration<double>(sleep_time));
}