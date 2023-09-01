/*
 * ITUGames.h
 * simple library for
 * 
 * Supported terminals:
 * - win: cmd, PowerShell
 * - mac: ???
 * Namespaces
 * - `Console` contains simple and portable (as much as possible) functions for console rendering, without using external dependencie
 * - `Utils` contains common gamedev utilities
 * 
 * Known issues:
 * - `ITUGames::Console` functions may not work properly in emulated terminals.
 * - Printing/clearing at high frequency (ie, in a loop at 60FPS) at the same terminal coordinates may cause some of the characters to skip rendering. adding `std::cout << std::flush;` forces the terminal to print all the characters before moving forward.
 * 
 * author: Chris-Carvelli
 * 
 * 
 * MIT License
 * 
 * Copyright (c) 2023 Chris
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <iostream>
#include <chrono>

#include <stdio.h>

#define ESC '\033'

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#elif defined(__linux__) || defined(__APPLE__)
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

int kbhit(void)
{
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	/*tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);*/

	if (ch != EOF)
	{
		ungetc(ch, stdin);
		return 1;
	}

	return 0;
}

char getch()
{
	return getchar();
}

#endif

/// <summary>
/// A collection of simplified game programming utilities
/// </summary>
namespace ITUGames
{
	namespace Console
	{
		/// Fancy, old schoold console tricks.
		/// Works only with consoles that support ANSI escape codes.
		/// 
		/// References:
		/// - ANSI special characters: https://en.wikipedia.org/wiki/ANSI_escape_code
		/// - printf formatting: https://en.cppreference.com/w/c/io/fprintf
		///   (the table in the `Parameters` section exaplins how to build a formatting string)


		/// Input key Codes
		constexpr unsigned char KEY_W = 119;
		constexpr unsigned char KEY_A = 97;
		constexpr unsigned char KEY_S = 115;
		constexpr unsigned char KEY_D = 100;
		constexpr unsigned char KEY_1 = 49;
		constexpr unsigned char KEY_2 = 50;
		constexpr unsigned char KEY_3 = 51;

		inline unsigned char GetCharacter(bool bBlocking = true) {
			// `kbhit()` returns true if something is waiting in the input buffer
			// if we are not blocking and there is nothing to read, just return 0
			// otherwise, read a character (which will block execution if there is nothing to be read)
			if (!bBlocking && !kbhit())
			{
				return 0;
			}
			
			return getch();
		}

		/// <summary>
		/// Move the cursor at (x, y)
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		inline void GotoCoords(int x, int y) {
			// `\033[` is a special ANSI code that means "start to execute a control sequence"
			// `H` represents the "Cursor Position" control sequence, which requires two integers
			// for X and Y coordinates. (in between `\033[` an `H`, separated by a semicolumn)
			//
			// The command wants ROWS;COLUMNS, but this API is designed with a horizontal/vertical approach
			// so we have to swap them.
			printf("%c[%d;%dH", ESC, y, x);
		}

		/// <summary>
		/// Prints the character at the current cursor position
		/// </summary>
		/// <param name="c"></param>
		inline void RenderCharacter(char c) {
			// printf stands for "print formatted". Replaces %c with the given character
			printf("%c", c);
		}

		/// <summary>
		/// Moves the cursor at (x, y) and then prints the character `c`
		/// </summary>
		/// <param name="c"></param>
		/// <param name="x"></param>
		/// <param name="y"></param>
		inline void RenderCharacter(char c, int x, int y) {
			printf("%c[%d;%dH%c", ESC, y, x, c);
		}

		/// <summary>
		/// Moves to the initial position of the terminal (usually top-left)
		/// </summary>
		inline void GotoTop() {
			printf("%c[0;0H", ESC);
		}

		/// <summary>
		/// Deletes everything on the screen
		/// </summary>
		inline void ClearScreen() {
			printf("%c[2J", ESC);
		}

		/// <summary>
		/// Deletes everything on the current line
		/// </summary>
		inline void ClearLine() {
			printf("%c[2K", ESC);
		}

		/// <summary>
		/// Moves the cursor to the given line and clears it
		/// </summary>
		/// <param name="y"></param>
		inline void ClearLine(int y) {
			GotoCoords(0, y);
			printf("%c[2K", ESC);
		}

		/// <summary>
		/// Prints the string at the current cursor position
		/// </summary>
		/// <param name="s"></param>
		inline void PrintStr(std::string s) {
			printf("%s", s.c_str());
		}

		inline void HideCursor() {
			printf("%c[?25l", ESC);
		}

		inline void ShowCursor() {
			printf("%c[?25h", ESC);
		}

		/// <summary>
		/// Gets the cursor position using ANSI escape sequences (requires unblocking input)
		/// Will probably cause flickering if used in an high-frequency loop.
		/// </summary>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <returns>`false` if there was a problem retrieving the cursor position</returns>
		inline bool GetCursorPosition(int& x, int& y)
		{
			constexpr int SIZE = 50;
			char ch;
			char buffer[SIZE] = { 0 };
			int i = 0;


			printf("%c[6n", ESC);         // ask for cursor position
			while ((ch = GetCharacter(false)) != 'R')
			{
				if (ch == EOF) {
					break;
				}
				if (isprint(ch)) {
					printf("try format");
					buffer[i++] = ch;
					buffer[i + 1] = 0;
				}
			}

			printf("try format");
			int return_value = sscanf(buffer, "[%d;%d", &y, &x);

			return return_value == 2;
		}

		/// <summary>
		/// Gets the terminal size using ANSI escape sequences (requires unblocking input)
		/// Will probably cause flickering if used in an high-frequency loop.
		/// </summary>
		/// <param name="rows"></param>
		/// <param name="cols"></param>
		/// <returns>`false` if there was a problem retrieving the terminal size</returns>
		inline bool GetTerminalSize(int& rows, int& cols)
		{
			constexpr int SIZE = 50;
			char ch;
			char buffer[SIZE];
			int i = 0;
			
			// currect cursor position
			int x, y;

			if (!GetCursorPosition(x, y))
				return false;

			//printf("\033[2J");         //clear screen
			printf("%c[9999;9999H", ESC); // cursor should move as far as it can
			
			if (!GetCursorPosition(rows, cols))
				return false;

			// restore cursor position
			GotoCoords(x, y);

			return true;
		}

		/// <summary>
		/// Gets the terminal width using ANSI escape sequences.
		/// Will probably cause flickering if used in an high-frequency loop (requires unblocking input)
		/// </summary>
		/// <returns>the terminal width, or -1 in case of error</returns>
		inline int GetTerminalWidth()
		{
			int rows, cols;

			if (GetTerminalSize(rows, cols))
				return cols;
			return -1;
		}
		/// <summary>
		/// Gets the terminal height using ANSI escape sequences (requires unblocking input)
		/// Will probably cause flickering if used in an high-frequency loop.
		/// </summary>
		/// <returns>the terminal height, or -1 in case of error</returns>
		inline int GetTerminalHeight()
		{
			int rows, cols;

			if (GetTerminalSize(rows, cols))
				return rows;
			return -1;
		}

		// leave a clean (ish) environment after execution
#ifdef _WIN32
		BOOL WINAPI CleanupHandler(DWORD fdwCtrlType) {
			if (fdwCtrlType == CTRL_SHUTDOWN_EVENT)
			{
				int h = GetTerminalHeight();
				printf("\033[%dT", h);
				GotoTop();
			}
			return false;
		}
#elif defined(__linux__) || defined(__APPLE__)
		void CleanupHandler(int s) {
			int h = GetTerminalHeight();
			printf("\033[%dT", h);
			GotoTop();
			fflush(stdout);
			exit(0);
		}
#endif

		inline void InitScreenForRendering() {
			ClearScreen();
			GotoTop();

#ifdef _WIN32
			if (!SetConsoleCtrlHandler(CleanupHandler, TRUE))
			{
				printf("\nERROR: Could not register control handler");
				exit(1);
			}
#elif defined(__linux__) || defined(__APPLE__)
			struct sigaction sigIntHandler;

			sigIntHandler.sa_handler = CleanupHandler;
			sigemptyset(&sigIntHandler.sa_mask);
			sigIntHandler.sa_flags = 0;

			sigaction(SIGINT, &sigIntHandler, NULL);
#endif
		}
	}

	namespace Utils
	{
		/// <summary>
		/// Waits for the given amount of time as precisely as possible.
		/// </summary>
		/// <param name="computation_time"></param>
		inline void PreciseSleep(std::chrono::duration<double> sleep_time) {
			std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();

			// This is called busy waiting
			// It's not a good practice because it wastes a lot of computation time, but
			// - it's extremely simple
			// - it's incredibly precise
			while (std::chrono::steady_clock::now() - start < sleep_time);
		}
	}
}
