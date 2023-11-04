#include "ComponentController.h"

#include "glm/glm.hpp"
#include "SDL.h"

#include "Engine/Components/ComponentPhysicsBody.h"

void ComponentController::Init(rapidjson::Value& serializedData) {
	// TODO load necessary data (linear velocity, inpulse strenght, etc) and add the to `scene.json`
}

void ComponentController::Update(float deltaTime) {
	// TODO, if you need to do anything here
}

void ComponentController::KeyEvent(SDL_Event& event)
{
	// TODO listen for spacebar
	
}

void ComponentController::OnCollisionStart(ComponentPhysicsBody* other) {
	// TODO gameOver on touching pipes, despawn coins
}