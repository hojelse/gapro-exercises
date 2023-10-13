#pragma once

#include "Component.h"

class ComponentController : public MyEngine::Component {
	void Init(rapidjson::Value&) override;
	void Update(float deltaTime) override;
	void KeyEvent(SDL_Event&) override;
	void Render(sre::RenderPass&) override;
};