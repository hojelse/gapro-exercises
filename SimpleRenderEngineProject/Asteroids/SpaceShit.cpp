#include "SpaceShit.h"
#define MOD(a, b) ((a) % (b) + (b)) % (b)

sre::Sprite sprite_spaceshit;
sre::Sprite sprite_laser;

SpaceShit::SpaceShit(
	sre::Sprite sprite_spaceshit
) {
	this->sprite_spaceshit = sprite_spaceshit;
	pos = glm::vec2(200.0, 200.0);
	vel = glm::vec2(0.0, 5.0);
	turn_rate = 300;
}

void SpaceShit::Render(sre::SpriteBatch::SpriteBatchBuilder& spriteBatchBuilder)
{
	sprite_spaceshit.setPosition(pos);
	sprite_spaceshit.setRotation(vec2_to_degrees(vel)-90);
	spriteBatchBuilder.addSprite(sprite_spaceshit);
}

void SpaceShit::move_forward()
{
	pos += vel;
	pos = coord_mod(pos);
}

void SpaceShit::rotate_cw(float deltaTime)
{
	rotate(turn_rate * deltaTime);
}

void SpaceShit::rotate_ccw(float deltaTime)
{
	rotate(-turn_rate * deltaTime);
}

void SpaceShit::rotate(float degrees)
{
	vel = rotate_vec(vel, degrees);
};

void SpaceShit::move(glm::vec2 delta)
{
	pos += delta;
}