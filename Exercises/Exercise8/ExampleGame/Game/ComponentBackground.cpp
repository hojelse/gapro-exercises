#include "ComponentBackground.h"

#include "Engine/MyEngine.h"
#include "Engine/Components/ComponentRendererSprite.h"

void ComponentBackground::Init(rapidjson::Value&) {
	auto gameObject = GetGameObject().lock();
	if (!gameObject)
		return;

	auto p_spriteComp = gameObject->FindComponent<ComponentRendererSprite>();

	if (auto spriteComp = p_spriteComp.lock()) {
		sre::Sprite* sprite = spriteComp->GetSprite();
		float scale = MyEngine::Engine::GetInstance()->GetScreenSize().y / sprite->getSpriteSize().y;
		sprite->setScale({ scale, scale });
	}
}