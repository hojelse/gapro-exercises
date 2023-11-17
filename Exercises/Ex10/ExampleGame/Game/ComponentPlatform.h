#pragma once

#include "Engine/Component.h"

enum PlatformType {
	Platform,
	Wall
};

class ComponentPlatform : public MyEngine::Component {
	static constexpr float _tileSize = 21;

public:
	virtual void Init(rapidjson::Value& serializedData) override;

private:
	float _size;
	PlatformType _type;
};