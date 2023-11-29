#include "ComponentController.h"

#include "glm/glm.hpp"
#include "SDL.h"

#include "Engine/Components/ComponentPhysicsBody.h"

void ComponentController::Init(rapidjson::Value& serializedData) {
	// TODO load necessary data (linear velocity, inpulse strenght, etc) and add the to `scene.json`
	auto gameObject = GetGameObject().lock();
	if (!gameObject)
		return;

	_body = gameObject->FindComponent<ComponentPhysicsBody>();
}

void ComponentController::Update(float deltaTime) {
	// TODO, if you need to do anything here
	auto body = _body.lock();
	if (!body)
		return;

	auto linearVelocity = body->getLinearVelocity();
	linearVelocity.x = _mov.x * _movSpeed;
	body->setLinearVelocity(linearVelocity);

	std::cout << "hello" << std::endl;

	body->addImpulse(glm::vec2(0, _jumpStrength));

}

void ComponentController::KeyEvent(SDL_Event& event) {
	// TODO listen for spacebar
	switch (event.key.keysym.sym)
	{
		case SDLK_w:
			key_down_space = event.type == SDL_KEYDOWN;
			break;
	}
}

void ComponentController::OnCollisionStart(ComponentPhysicsBody* other) {
	// TODO gameOver on touching pipes, despawn coins
}