#include "ComponentController.h"

#include "glm/gtx/transform.hpp"
#include "glm/glm.hpp"
#include "SDL.h"

void ComponentController::Init(rapidjson::Value& serializedData) {
	mov_speed = serializedData["movSpeed"].GetFloat();
	rot_speed = serializedData["rotSpeed"].GetFloat();
}

bool key_down_w = false;
bool key_down_a = false;
bool key_down_s = false;
bool key_down_d = false;
bool key_down_j = false;
bool key_down_k = false;

void ComponentController::Update(float deltaTime) {
	auto delta_z = 0.0f;
	auto delta_x = 0.0f;
	if (key_down_w) delta_z -= 1.0f;
	if (key_down_s) delta_z += 1.0f;
	if (key_down_a) delta_x -= 1.0f;
	if (key_down_d) delta_x += 1.0f;

	auto delta_rot = 0.0f;
	if (key_down_j) delta_rot += 1.0f;
	if (key_down_k) delta_rot -= 1.0f;

	GetGameObject()->transform = glm::translate(
		glm::rotate(
			GetGameObject()->transform,
			delta_rot * deltaTime * rot_speed,
			glm::vec3(0, 1, 0)
		),
		glm::vec3(delta_x * deltaTime * mov_speed, 0, delta_z * deltaTime * mov_speed)
	);
}

void ComponentController::KeyEvent(SDL_Event& event)
{
	switch (event.key.keysym.sym)
	{
	case SDLK_w:
		key_down_w = event.type == SDL_KEYDOWN;
		break;
	case SDLK_a:
		key_down_a = event.type == SDL_KEYDOWN;
		break;
	case SDLK_s:
		key_down_s = event.type == SDL_KEYDOWN;
		break;
	case SDLK_d:
		key_down_d = event.type == SDL_KEYDOWN;
		break;
	case SDLK_j:
		key_down_j = event.type == SDL_KEYDOWN;
		break;
	case SDLK_k:
		key_down_k = event.type == SDL_KEYDOWN;
		break;
	}
}

void ComponentController::Render(sre::RenderPass&) {
	auto gameObject = GetGameObject();
	glm::vec3 position = gameObject->GetPosition();
	glm::vec3 rotation = gameObject->GetEulerAngles();
	glm::vec3 scale = gameObject->GetScale();

	ImGui::SetNextWindowPos(ImVec2(.0f, .0f), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(300, 75), ImGuiSetCond_Always);
	ImGui::Begin("", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	if (ImGui::DragFloat3("Position", &(position.x)))
		gameObject->SetPosition(position);
	if (ImGui::DragFloat3("Rotation", &(rotation.x)))
		gameObject->SetEulerAngles(rotation);
	if (ImGui::DragFloat3("Scale", &(scale.x)))
		gameObject->SetScale(scale);
	ImGui::End();
}