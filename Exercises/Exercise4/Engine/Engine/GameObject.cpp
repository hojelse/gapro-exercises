#include "GameObject.h"

#include "sre/RenderPass.hpp"

#include "MyEngine.h"
#include "Component.h"
#include "Logger.h"

namespace MyEngine {
	// public API
	void GameObject::Init() {
		for (auto& component : _components)
			component->Init();

		for (auto& child : _children)
			child->Init();
	}

	void GameObject::Update(float deltaTime) {
		for (auto& component : _components)
			component->Update(deltaTime);

		for (auto& child : _children)
			child->Update(deltaTime);
	}

	void GameObject::Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder) {
		for (auto& component : _components)
			component->Render(spriteBatchBuilder);

		for (auto& child : _children)
			child->Render(spriteBatchBuilder);
	}

	void GameObject::KeyEvent(SDL_Event& e) {
		for (auto& component : _components)
			component->KeyEvent(e);

		for (auto& child : _children)
			child->KeyEvent(e);
	}

	void GameObject::AddChild(std::shared_ptr<GameObject> p_object) {
		_children.push_back(p_object);
	}

	void GameObject::AddComponent(std::shared_ptr<Component> p_component) {
		p_component->SetGameObject(_self);
		_components.push_back(p_component);
	}

	std::string GameObject::GetName() {
		return _name;
	}

	void GameObject::SetName(std::string p_name) {
		_name = p_name;
	}
}