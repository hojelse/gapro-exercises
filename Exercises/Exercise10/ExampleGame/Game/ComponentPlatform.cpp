#include "ComponentPlatform.h"

#include "Engine/Components/ComponentPhysicsBody.h"
#include "Engine/Components/ComponentRendererSprite.h"

void ComponentPlatform::Init(rapidjson::Value& serializedData) {
	_size = serializedData["size"].GetFloat();
	_type = static_cast<PlatformType>(serializedData["type"].GetInt());

	float halfSize = _size / 2;
	float halfSizeBody = _tileSize / 2;

	glm::vec2 offset = glm::vec2(0, 0);
	if (_type == PlatformType::Platform)
		offset.x = 1;
	if (_type == PlatformType::Wall)
		offset.y = 1;
	
	// body
	glm::vec2 sizeBody = glm::vec2(_tileSize, _tileSize) + offset * _tileSize * (_size - 1);
	sizeBody /= 2;
	auto body = GetGameObject().lock()->CreateComponent<ComponentPhysicsBody>().lock();
	body->CreateBody(b2_kinematicBody, false, sizeBody);

	// sprites
	for (int i = -halfSize; i < halfSize; ++i) {
		auto sprite = GetGameObject().lock()->CreateComponent<ComponentRendererSprite>().lock();
		sprite->SetSprite("platformer-art-deluxe", "1.png");
		glm::vec2 pos = offset * _tileSize * (float)i;
		sprite->SetSpritePosition(pos);
	}
}