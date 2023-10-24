#pragma once
#include "sre/SDLRenderer.hpp"
#include "MyUtil.h"
class SpaceShit
{
public:
	SpaceShit(sre::Sprite);
	sre::Sprite sprite_spaceshit;
	glm::vec2 pos;
	glm::vec2 vel;
	float turn_rate;
	void Render(sre::SpriteBatch::SpriteBatchBuilder &spriteBatchBuilder);
	void move_forward();
	void rotate_cw(float deltaTime);
	void rotate_ccw(float deltaTime);
private:
	void rotate(float degrees);
	void move(glm::vec2 delta);
};