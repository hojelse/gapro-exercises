#include "ComponentLevelLayout.h"
#include "ComponentRendererMesh.h"
#include "Engine/MyEngine.h"

#include "glm/gtx/transform.hpp"

void ComponentLevelLayout::Init(rapidjson::Value& serializedData) {
	// auto dimx = serializedData["dims"][0].GetInt();
	// auto dimy = serializedData["dims"][1].GetInt();
	
	// for (int x = 0; x < dimx; x++)
	// 	for (int y = 0; y < dimy; y++)
	// 		std::cout << serializedData["layout"][0][0].GetInt() << std::endl;

	auto engine = MyEngine::Engine::GetInstance();

	auto go_weak = engine->CreateGameObject("LayoutContainer");

	// go_weak.lock()->AddComponent(std::shared_ptr<ComponentRendererMesh>());
	go_weak.lock()->Init(serializedData);
}

void ComponentLevelLayout::Update(float deltaTime) {

}

void ComponentLevelLayout::Render(sre::RenderPass& renderPass) {

}