#include "sre/SpriteAtlas.hpp"

#include "Engine/MyEngine.h"
#include "Engine/ComponentFactory.h"

#include "Game/ComponentController.h"
#include "Game/ComponentFollowTarget.h"
#include "Game/ComponentBackground.h"
#include "Game/ComponentSpawner.h"

MyEngine::Engine engine;

int main() {
	MyEngine::ComponentFactory::RegisterComponentOfType("CONTROLLER", []() { return std::make_shared<ComponentController>(); });
	MyEngine::ComponentFactory::RegisterComponentOfType("FOLLOW_TARGET", []() { return std::make_shared<ComponentFollowTarget>(); });
	MyEngine::ComponentFactory::RegisterComponentOfType("BACKGROUND", []() { return std::make_shared<ComponentBackground>(); });
	MyEngine::ComponentFactory::RegisterComponentOfType("SPAWNER", []() { return std::make_shared<ComponentSpawner>(); });
	
	engine.Init("data/scene.json");
}
