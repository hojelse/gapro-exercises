#include "ComponentRendererMesh.h"

#include "glm/gtx/transform.hpp"
#include <unistd.h>
#include <cmath>

void ComponentRendererMesh::Init(rapidjson::Value &serializedData)
{
	const int texture_id = serializedData.GetInt();

	const glm::vec2 textureSize = glm::vec2(1039, 389);
	const glm::vec2 tileSize = glm::vec2(64, 64);
	const glm::vec2 tileSizeWithBorder = glm::vec2(65, 65);

	const glm::vec2 min = glm::vec2(0, 6 * tileSizeWithBorder.y) / textureSize;
	const glm::vec2 max = min + tileSize / textureSize;

	const std::vector<glm::vec3> positions = {
		glm::vec3(-.5, -.5, .5),
		glm::vec3(-.5, .5, .5),
		glm::vec3(.5, .5, .5),
		glm::vec3(.5, -.5, .5)};

	const glm::vec2 a = tileSize / textureSize;

	const int tile_x = (texture_id)%16;
	const int tile_y = std::floor(texture_id/16);

	const glm::vec2 offset = (tileSize / textureSize) * glm::vec2(tile_x, tile_y);

	const std::vector<glm::vec4> uvs = {
		glm::vec4(min.x + offset.x, min.y + offset.y, 0, 0),
		glm::vec4(min.x + offset.x, max.y + offset.y, 0, 0),
		glm::vec4(max.x + offset.x, max.y + offset.y, 0, 0),
		glm::vec4(max.x + offset.x, min.y + offset.y, 0, 0)};

	const std::vector<uint16_t> idxs = {3, 1, 0, 3, 2, 1};

	_mesh = sre::Mesh::create()
				.withPositions(positions)
				.withUVs(uvs)
				.withIndices(idxs, sre::MeshTopology::Triangles, 0)
				.build();
	_material = sre::Shader::getUnlit()->createMaterial();

	_texture = sre::Texture::create().withFile("data/level0.png").withGenerateMipmaps(false).withFilterSampling(false).build();
	_material->setTexture(_texture);
}

void ComponentRendererMesh::Update(float deltaTime)
{
	// GetGameObject()->transform = glm::rotate(GetGameObject()->transform, glm::pi<float>() * deltaTime, glm::vec3(0, 1, 0));
}

void ComponentRendererMesh::Render(sre::RenderPass &renderPass)
{
	for (int i = 0; i < 4; i++)
	{
		renderPass.draw(
			_mesh,
			glm::rotate(
				GetGameObject()->transform,
				glm::pi<float>() / 2 * i,
				glm::vec3(0, 1, 0)),
			_material);
	}

	// usleep(10000000);

	// renderPass.draw(_mesh, GetGameObject()->transform, _material);
	// static auto cube = sre::Mesh::create().withCube(0.5f).build();
	// static std::vector<std::shared_ptr<sre::Material> > materials = {
	//         sre::Shader::getUnlit()->createMaterial(),
	//         sre::Shader::getUnlit()->createMaterial(),
	//         sre::Shader::getUnlit()->createMaterial()
	// };

	// std::vector<glm::vec3> positions = {
	//         {-1,0,-2},
	//         { 0,0,-3},
	//         { 1,0,-4}
	// };
	// std::vector<sre::Color> colors = {
	//         {1,0,0,1},
	//         {0,1,0,1},
	//         {0,0,1,1},
	// };
	// for (int i = 0; i < positions.size(); i++) {
	//     materials[i]->setColor(colors[i]);
	//     renderPass.draw(cube, glm::translate(positions[i]), materials[i]);
	// }
}