#include "ComponentLevelLayout.h"

#include "glm/gtx/transform.hpp"

void ComponentLevelLayout::Init(rapidjson::Value& serializedData) {
	// auto dimx = serializedData["dims"][0].GetInt();
	// auto dimy = serializedData["dims"][1].GetInt();
	
	// for (int x = 0; x < dimx; x++)
	// 	for (int y = 0; y < dimy; y++)
	// 		std::cout << serializedData["layout"][0][0].GetInt() << std::endl;

}

void ComponentLevelLayout::Update(float deltaTime) {

}

void ComponentLevelLayout::Render(sre::RenderPass& renderPass) {

}