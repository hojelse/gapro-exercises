#include "MyUtil.h"

float vec2_to_degrees(glm::vec2 v)
{
	float radians = glm::atan(v.y, v.x);
	float degrees = glm::degrees(radians);
	return degrees;
}

glm::vec2 rotate_vec(glm::vec2 vectorToRotate, float degrees)
{
	float dir_rad = glm::radians(degrees);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), dir_rad, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::vec4 rotatedVector = rotationMatrix * glm::vec4(vectorToRotate, 0.0f, 1.0f);
	glm::vec2 rotatedVec2(rotatedVector);
	return rotatedVec2;
}

glm::vec2 coord_mod(glm::vec2 pos) {
	glm::vec2 window_size(1000,1000);

	while (pos.x < 0) pos.x += window_size.x;
	while (pos.x > window_size.x) pos.x -= window_size.x;
	while (pos.y < 0) pos.y += window_size.y;
	while (pos.y > window_size.y) pos.y -= window_size.y;

	return pos;
}