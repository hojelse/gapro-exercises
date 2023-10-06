#include "ComponentController.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/transform.hpp"
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
	glm::vec3 position, scale;
	glm::quat rotation;
	// we don't really care about these for gameObjects, but we need to matck glm::decompose() signature
	glm::vec3 skew; glm::vec4 perspective;

	glm::decompose(GetGameObject()->transform, scale, rotation, position, skew, perspective);

	glm::vec3 display_rot = glm::degrees(glm::eulerAngles(rotation));
	ImGui::SetNextWindowPos(ImVec2(.0f, .0f), ImGuiSetCond_Always);
	ImGui::SetNextWindowSize(ImVec2(300, 75), ImGuiSetCond_Always);
	ImGui::Begin("", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	ImGui::DragFloat3("Position", glm::value_ptr(position));
	ImGui::DragFloat("Rotation", &display_rot.y);
	ImGui::End();

	GetGameObject()->transform =
		glm::scale(scale) *
		glm::translate(position) *
		glm::mat4_cast(glm::quat(glm::radians(display_rot)));
}