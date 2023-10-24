#include "Component.h"

#include "Logger.h"

namespace MyEngine {
	GameObject* Component::GetGameObject() {
		if (_gameObject.expired())
		{
			Logger::Log("Invalid game object");
			return nullptr;
		}

		return _gameObject.lock().get();
	}

	void Component::SetGameObject(std::weak_ptr<GameObject> p_gameObject) {
		_gameObject = p_gameObject;
	}
}