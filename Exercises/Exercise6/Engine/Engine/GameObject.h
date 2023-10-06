#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <list>
#include <memory>
#include <string>

#include "sre/SpriteBatch.hpp"

#include "rapidjson/document.h"

namespace MyEngine {
	class Component;

	class GameObject {
		friend class Engine;

		// public API
	public:
		glm::mat4 transform;
		float rotation;

		void Init(rapidjson::Value& data);
		void Update(float);
		void Render(sre::RenderPass&);
		void KeyEvent(SDL_Event&);

		void AddChild(std::shared_ptr<GameObject>);
		void AddComponent(std::shared_ptr<Component>);

		std::string GetName();
		void SetName(std::string);

		// private fields
	private:
		std::weak_ptr<GameObject> _parent;
		std::weak_ptr<GameObject> _self;
		std::list<std::shared_ptr<GameObject>> _children = {};
		std::list<std::shared_ptr<Component>> _components = {};
		std::string _name;

	public:
		glm::mat4 DeserializeTransform(rapidjson::Value& transformData);

		glm::vec3 DeserializeVector(rapidjson::Value& vectorData);
	};
}
