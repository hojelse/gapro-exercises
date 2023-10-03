#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"

#include "Engine/MyEngine.h"

#include "Game/ComponentController.h"
#include "Game/ComponentRendererSprite.h"

void InitGame();
void ProcessEvents(SDL_Event& event);
void Update(float deltaTime);
void Render();

MyEngine::Engine engine;

glm::vec2 window_size = glm::vec2(800, 600);
sre::SDLRenderer renderer;
sre::Camera camera;
std::shared_ptr<sre::SpriteAtlas> atlas;

int main() {
	renderer.frameRender = Render;
	renderer.frameUpdate = Update;
	renderer.keyEvent = ProcessEvents;

	renderer.setWindowSize(window_size);
	renderer.init();
	camera.setWindowCoordinates();

	atlas = sre::SpriteAtlas::create("data/snake.json", "data/snake.png");

	auto gameObject = engine.CreateGameObject("GameObject");
	auto componentController = std::shared_ptr<ExampleGame::ComponentController>(new ExampleGame::ComponentController());
	auto componentRenderer = std::make_shared<ExampleGame::ComponentRendererSprite>();
	gameObject->AddComponent(componentController);
	gameObject->AddComponent(componentRenderer);

	componentRenderer->sprite = atlas->get("berry.png");

	engine.Init();

	renderer.startEventLoop();
}

void ProcessEvents(SDL_Event& event) { }

void Update(float deltaTime) {
	engine.Update(deltaTime);
}

void Render() {
	engine.Render();
}