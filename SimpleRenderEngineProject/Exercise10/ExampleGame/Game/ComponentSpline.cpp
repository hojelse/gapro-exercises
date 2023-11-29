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

glm::vec3 lerp2(glm::vec3 a, glm::vec3 b, double t) {
	return glm::vec3(
		a.x + t * (b.x - a.x),
		a.y + t * (b.y - a.y),
		0
	);
}

void ComponentSpline::Update(float delta) {
	auto gameObject = GetGameObject().lock();
	if (!gameObject)
		return;

	_t += delta;

	int segment = (int)fmod(_t, _points.size() - 1);
	float t = fmod(_t, 1.0f);

	auto p0 = _points[segment];
	auto p1 = _points[segment] + glm::vec3(40, 0, 0);
	auto p2 = _points[segment + 1] + glm::vec3(-40, 0, 0);
	auto p3 = _points[segment + 1];

	auto term1 = lerp2(p0, p1, t);
	auto term2 = lerp2(p1, p2, t);
	auto term3 = lerp2(p2, p3, t);

	auto result1 = lerp2(term1, term2, t);
	auto result2 = lerp2(term2, term3, t);

	auto point = lerp2(result1, result2, t);

	// TODO use Quadratic B�zier spline instead
	// gameObject->SetPosition(glm::mix(_points[segment], _points[segment + 1], y));
	gameObject->SetPosition(point);
}

void ComponentSpline::Render(sre::RenderPass& renderPass) {
	for (auto& pair : _pairs)
		renderPass.drawLines(pair);
}