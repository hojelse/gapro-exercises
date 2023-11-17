#include "ComponentSpline.h"

void ComponentSpline::Init(rapidjson::Value& serializedData) {
	auto gameObject = GetGameObject().lock();
	if (!gameObject)
		return;
	auto pos = gameObject->GetPosition();

	_speed = serializedData["speed"].GetFloat();

	// apply transform to spline point offsets
	for(int i = 0; i < serializedData["points"].Size(); ++i)
		_points.emplace_back(MyEngine::GameObject::DeserializeVector(serializedData["points"][i]) + pos);

	// create point pairs, for debug purposes
	for (int i = 0; i < _points.size() - 1; ++i)
		_pairs.emplace_back(std::vector<glm::vec3> { _points[i], _points[i + 1]});
}

void ComponentSpline::Update(float delta) {
	auto gameObject = GetGameObject().lock();
	if (!gameObject)
		return;

	_t += delta;

	int segment = (int)fmod(_t, _points.size() - 1);
	float t = fmod(_t, 1.0f);

	// TODO use Quadratic Bézier spline instead
	gameObject->SetPosition(glm::mix(_points[segment], _points[segment + 1], t));
}

void ComponentSpline::Render(sre::RenderPass& renderPass) {
	for (auto& pair : _pairs)
		renderPass.drawLines(pair);
}