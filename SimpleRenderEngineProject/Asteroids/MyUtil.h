#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

float vec2_to_degrees(glm::vec2 v);

glm::vec2 rotate_vec(glm::vec2 vectorToRotate, float degrees);

glm::vec2 coord_mod(glm::vec2);