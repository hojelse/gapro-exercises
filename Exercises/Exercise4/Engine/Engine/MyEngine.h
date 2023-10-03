#pragma once

#include <chrono>

#include "sre/Camera.hpp"
#include "sre/SpriteAtlas.hpp"
#include "SDL.h"

#include "GameObject.h"


class GameObject;

namespace MyEngine {
	class Engine {
	private:
		static Engine* _instance;
	public:
		static Engine* GetInstance() { return _instance; }
	public:
		const glm::vec2 WIN_SIZE = glm::vec2(800, 600);
		const std::chrono::duration<double> MAX_FRAME_TIME = std::chrono::duration<double>(1 / 60.0);

		Engine();

		void Init();
		void ProcessEvents(SDL_Event& event);
		void Update(float);
		void Render();

		float GetFPS() const { return 1.0 / time_elapsed.count(); }
		float GetTimeElapsedMs() const { return 1000 * time_elapsed.count(); }
		float GetTimeComputationMs() const { return 1000 * time_computation.count(); }

		glm::vec2 GetScreenSize() const;

		int GetFrame() const { return frame; }
		float GetTime() const { return time; }

		GameObject* CreateGameObject(std::string name);

	private:
		std::shared_ptr<GameObject> _root;

		std::chrono::time_point<std::chrono::steady_clock>	time_start;
		std::chrono::time_point<std::chrono::steady_clock>	time_end;
		std::chrono::time_point<std::chrono::steady_clock>	time_end_computation;
		std::chrono::duration<double>						time_elapsed;
		std::chrono::duration<double>						time_computation;
		int frame;
		float time;

		unsigned char input = -1;
		bool b_show_debug_window = false;

		sre::Camera _camera;
	};
}