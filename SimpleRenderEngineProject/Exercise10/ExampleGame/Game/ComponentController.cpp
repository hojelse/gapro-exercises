#include "ComponentController.h"

#include "glm/glm.hpp"
#include "SDL.h"

void ComponentController::Init(rapidjson::Value& serializedData) {
	auto gameObject = GetGameObject().lock();
	if (!gameObject)
		return;

	_body = gameObject->FindComponent<ComponentPhysicsBody>();
	_sprite = gameObject->FindComponent<ComponentRendererSprite>();
}

void ComponentController::Update(float deltaTime) {
	auto sprite = _sprite.lock();
	if (!sprite)
		return;
	auto body = _body.lock();
	if (!body)
		return;

	auto linearVelocity = body->getLinearVelocity();
	linearVelocity.x = _mov.x * _movSpeed;
	body->setLinearVelocity(linearVelocity);

	if (_jump) {
		body->addImpulse(glm::vec2(0, _jumpStrength));
		_jump = false;
	}

	float walk_timing = 0.5;

	_time += deltaTime;
	if (_time > 0.5 * walk_timing) _time -= walk_timing;

	if (_grounded) {
		bool is_standing = linearVelocity.x == 0 && linearVelocity.y == 0;
		if (is_standing) {
			sprite->SetSprite("platformer-art-deluxe", "19.png");
		} else {
			if (_time > 0) {
				sprite->SetSprite("platformer-art-deluxe", "20.png"); // walk1
			} else {
				sprite->SetSprite("platformer-art-deluxe", "21.png"); // walk2
			}
		}
	} else {
		if (linearVelocity.y > 0)
			sprite->SetSprite("platformer-art-deluxe", "26.png"); // flyUp
		if (linearVelocity.y == 0)
			sprite->SetSprite("platformer-art-deluxe", "27.png"); // fly
		if (linearVelocity.y < 0)
			sprite->SetSprite("platformer-art-deluxe", "28.png"); // flyDown
	}

	glm::vec2 position = glm::vec2(-1, 1);
	if (linearVelocity.x < 0) {
		auto flip = sprite->_sprite.getFlip();
		sprite->_sprite.setFlip(glm::vec2(true, false));
	}

}

void ComponentController::KeyEvent(SDL_Event& event) {
	

	// movement
	switch (event.key.keysym.sym) {
		case SDLK_a: _mov.x = -(event.type == SDL_KEYDOWN); break;
		case SDLK_d: _mov.x = +(event.type == SDL_KEYDOWN); break;
	}

	// jump
	if (_grounded && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
		_jump = true;
	}

}

void ComponentController::OnCollisionStart(ComponentPhysicsBody* other, b2Manifold* manifold) {
	if (manifold->localNormal.y > .99)
		_grounded = true;
}

void ComponentController::OnCollisionEnd(ComponentPhysicsBody* other, b2Manifold* manifold) {
	if (manifold->localNormal.y > .99)
		_grounded = false;
}