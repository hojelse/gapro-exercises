#include "ComponentController.h"

#include "Engine/MyEngine.h"

namespace ExampleGame {
	void ComponentController::Init() {
	}

	void ComponentController::Update(float deltaTime) {
		MyEngine::Engine* engine = MyEngine::Engine::GetInstance();
		MyEngine::GameObject* parent = GetGameObject();

		glm::vec2 basePos = engine->GetScreenSize() / 2.f;

		parent->rotation += RotSpeed * deltaTime;
		parent->position = basePos + MovDirection * MovAmount * glm::sin(MovSpeed * engine->GetTime());
	}
}