#pragma once

#include "Engine/Component.h"

class ComponentBackground : public MyEngine::Component {
	void Init(rapidjson::Value&) override;
};