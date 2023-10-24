#include "ComponentController.h"

#include "glm/glm.hpp"
#include "SDL.h"

void ComponentController::Init(rapidjson::Value& serializedData) {
	mov_speed = serializedData["movSpeed"].GetFloat();
	rot_speed = serializedData["rotSpeed"].GetFloat();
}

void ComponentController::Update(float deltaTime) {
	// TODO
}

void ComponentController::KeyEvent(SDL_Event& event)
{
	// TODO
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