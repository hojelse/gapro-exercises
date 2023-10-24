#pragma once
#include "sre/SDLRenderer.hpp"
#include "SpaceShit.h"
#include "MyUtil.h"
#include <list>
class GameObject
{
public:
	GameObject(
		sre::Sprite,
		sre::Sprite
	);
	sre::Sprite sprite_laser;
	sre::Sprite sprite_asteroid_lg;
	SpaceShit* spaceshit;
	std::list<std::tuple<glm::vec2, glm::vec2>> lasers;
	std::list<std::tuple<glm::vec2, glm::vec2, float>> asteroids;
	int asteroids_destroyed_count;
	void spawn_asteroid();
	void ProcessEvents(SDL_Event &event);
	void Update(float deltaTime);
	void Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder);
};