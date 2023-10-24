#include "sre/SpriteAtlas.hpp"

#include "Engine/MyEngine.h"
#include "Engine/ComponentFactory.h"

#include "Game/ComponentCamera.h"
#include "Game/ComponentRendererMesh.h"
#include "Game/ComponentController.h"
// #include "Game/ComponentLevelLayout.h"

MyEngine::Engine engine;

int main() {
	MyEngine::ComponentFactory::RegisterComponentOfType("CONTROLLER", std::make_shared<ComponentController>());
	MyEngine::ComponentFactory::RegisterComponentOfType("CAMERA", std::make_shared<ComponentCamera>());
	MyEngine::ComponentFactory::RegisterComponentOfType("CUBE_RENDERER", std::make_shared<ComponentRendererMesh>());
	// MyEngine::ComponentFactory::RegisterComponentOfType("LEVEL_LAYOUT", std::make_shared<ComponentLevelLayout>());
	engine.Init("data/scene.json");
}
