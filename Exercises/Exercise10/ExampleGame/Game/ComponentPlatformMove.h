#pragma once

#include "Engine/Component.h"

enum EasingType {
	Constant,
	Linear,
	Sin
	// add your easings here
};

class ComponentPlatformMove : public MyEngine::Component {
private:
	bool _yoyo;
	float _duration;
	glm::vec3 _str;
	glm::vec3 _end;
	EasingType _easing;

	// interpolation time, always betwee 0 and 1.
	// called `t` as a convention
	float _t = 0;

	std::weak_ptr<ComponentPhysicsBody> _body;

	virtual void Init(rapidjson::Value& serializedData) override;
	virtual void Update(float) override;

	float Easing(float t);
};