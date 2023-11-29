#include "ComponentPlatformMove.h"

#include "Engine/MyEngine.h"
#include "Engine/Components/ComponentPhysicsBody.h"

void ComponentPlatformMove::Init(rapidjson::Value& serializedData) {
	auto gameObject = GetGameObject().lock();
	if (!gameObject)
		return;

	auto pos = gameObject->GetPosition();

	_yoyo = serializedData["yoyo"].GetBool();
	_duration = serializedData["duration"].GetFloat();
	_str = pos + MyEngine::GameObject::DeserializeVector(serializedData["start"]);
	_end = pos + MyEngine::GameObject::DeserializeVector(serializedData["end"]);
	_easing = static_cast<EasingType>(serializedData["easing"].GetInt());

	_body = gameObject->FindComponent<ComponentPhysicsBody>();
}

void ComponentPlatformMove::Update(float delta) {
	auto gameObject = GetGameObject().lock();
	if (!gameObject)
		return;

	_t = std::fmod(_t + delta, _duration);

	float t = _t / _duration;
	if (_yoyo) {
		t *= 2;
		if (t > 1)
			t = 2 - t;
	}

	float v = Easing(t);

	glm::vec3 pos = _str * (1 - v) + _end * v;


	glm::vec2 d = pos - gameObject->GetPosition();

	auto a = d * (1 / MyEngine::Engine::GetInstance()->PHYSICS_SCALE);
	_body.lock()->setLinearVelocity(d);
	//gameObject->SetPosition(pos);
}

double lerp(double a, double b, double t) {
	return a + t * (b - a);
}

float ComponentPlatformMove::Easing(float t) {
	switch (_easing) {
		case Constant: return 0;
		case Linear: return t;
		case Sin: return glm::sin(t);
		// TODO add your easing functions here
		case Sigmoid: return 1.0 / (1.0 + exp(-t));
		case EaseInOut: {
			double p0 = 0.0;
			double p1 = 0.4;
			double p2 = 0.6;
			double p3 = 1.0;

			double term1 = lerp(p0, p1, t);
			double term2 = lerp(p1, p2, t);
			double term3 = lerp(p2, p3, t);

			double result1 = lerp(term1, term2, t);
			double result2 = lerp(term2, term3, t);

			return lerp(result1, result2, t);
		}
	}
}