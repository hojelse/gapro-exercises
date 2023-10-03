#pragma once

#include <memory>

#include "sre/RenderPass.hpp"

#include "GameObject.h"

namespace MyEngine {
	class Engine;

	class Component {
		friend class GameObject;

	private:

	public:
		virtual void Init() {};
		virtual void Update(float) {};
		virtual void Render(sre::SpriteBatch::SpriteBatchBuilder&) {};
		virtual void KeyEvent(SDL_Event&) {};

		// interface used by gameplay components
	protected:
		GameObject* GetGameObject();

	private:
		std::weak_ptr<GameObject> _gameObject;

		void SetGameObject(std::weak_ptr<GameObject>);
	};
}