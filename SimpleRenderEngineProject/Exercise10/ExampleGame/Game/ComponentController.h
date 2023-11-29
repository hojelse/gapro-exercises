#pragma once

#include "Engine/Component.h"

#include "../../Engine/Engine/Components/ComponentPhysicsBody.h"
#include "../../Engine/Engine/Components/ComponentRendererSprite.h"

class ComponentController : public MyEngine::Component {
	void Init(rapidjson::Value&) override;
	void Update(float deltaTime) override;
	void KeyEvent(SDL_Event&) override;
	void OnCollisionStart(ComponentPhysicsBody* other, b2Manifold* manifold) override;
	void OnCollisionEnd(ComponentPhysicsBody* other, b2Manifold* manifold) override;

private:
	std::weak_ptr<ComponentPhysicsBody> _body;
	std::weak_ptr<ComponentRendererSprite> _sprite;
	glm::vec3 _mov;
	bool _jump;
	bool _grounded;

	float _movSpeed = 2;
	float _jumpStrength = 5;
	float _time = 0.0;
};