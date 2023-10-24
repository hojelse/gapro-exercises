#include "main.h"
glm::vec2 window_size = glm::vec2(500, 500);
sre::SDLRenderer renderer;
sre::Camera camera;
std::shared_ptr<sre::SpriteAtlas> atlas;

GameObject* rootobject;
SpaceShit* spaceshit;

int main()
{
	renderer.frameRender = Render;
	renderer.frameUpdate = Update;
	renderer.keyEvent = ProcessEvents;
	renderer.setWindowSize(window_size);
	renderer.init();
	camera.setWindowCoordinates();

	// Sprites
	atlas = sre::SpriteAtlas::create("data/spriteatlas.json",
									 "data/spriteatlas.png");

	sre::Sprite sprite_spaceshit = atlas->get("playerShip1_blue.png");
	sre::Sprite sprite_laser = atlas->get("laserBlue01.png");

	sre::Sprite sprite_asteroid_sm = atlas->get("meteorBrown_small1.png");
	sre::Sprite sprite_asteroid_md = atlas->get("meteorBrown_med1.png");
	sre::Sprite sprite_asteroid_lg = atlas->get("meteorBrown_big1.png");

	rootobject = new GameObject(
		sprite_laser,
		sprite_asteroid_lg
	);

	rootobject->spaceshit = new SpaceShit(sprite_spaceshit);

	renderer.startEventLoop();
}

void ProcessEvents(SDL_Event& event)
{
	rootobject->ProcessEvents(event);
}

void Update(float deltaTime)
{
	rootobject->Update(deltaTime);
}

void Render()
{
	sre::RenderPass renderPass = sre::RenderPass::create()
									 .withCamera(camera)
									 .withClearColor(true, {.3f, .3f, 1, 1})
									 .build();
	sre::SpriteBatch::SpriteBatchBuilder spriteBatchBuilder = sre::SpriteBatch::create();
	// send spriteBatchBuilder to your game elements, so that
	// they can add their sprites for rendering
	rootobject->Render(spriteBatchBuilder);
	auto spriteBatch = spriteBatchBuilder.build();
	renderPass.draw(spriteBatch);
}
