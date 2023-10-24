#include "ComponentLevelLayout.h"
#include "ComponentRendererMesh.h"
#include "Engine/MyEngine.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "glm/gtx/transform.hpp"

void ComponentLevelLayout::Init(rapidjson::Value& serializedData) {
	auto dimx = serializedData["dims"][0].GetInt();
	auto dimz = serializedData["dims"][1].GetInt();
	
	auto engine = MyEngine::Engine::GetInstance();

	for (int x = 0; x < dimx; x++) {
		for (int z = 0; z < dimz; z++) {
			auto texture_id = serializedData["layout"][x][z].GetInt();
			if (texture_id < 0) continue;
			if (texture_id > 6*16-1) continue;

			auto go = engine->CreateGameObject("boxes");
			auto r = std::make_shared<ComponentRendererMesh>();
			r->Init(serializedData["layout"][x][z]);
			go.lock()->AddComponent(r);

			auto pos = glm::vec3(x, 0, z);
			auto rot = glm::vec3(0, 0, 0);
			auto scl = glm::vec3(1, 1, 1);

			go.lock()->transform =
				glm::translate(pos) *
				glm::mat4_cast(glm::quat(glm::radians(rot))) * 
				glm::scale(scl);

			
		}
	}
}

void ComponentLevelLayout::Update(float deltaTime) {

}

void ComponentLevelLayout::Render(sre::RenderPass& renderPass) {

}