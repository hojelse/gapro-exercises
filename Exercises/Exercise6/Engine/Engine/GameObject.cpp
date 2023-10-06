#include "GameObject.h"

#include "sre/RenderPass.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include "MyEngine.h"
#include "Component.h"
#include "ComponentFactory.h"
#include "Logger.h"

namespace MyEngine {
	// public API
	void GameObject::Init(rapidjson::Value& data) {
		auto engine = Engine::GetInstance();

		_name = data["name"].GetString();
		transform = DeserializeTransform(data["transform"]);

		for (auto& componentData : data["components"].GetArray())
		{
			auto TMP_id = componentData["typeId"].GetString();
			auto component = ComponentFactory::GetComponentOfType(componentData["typeId"].GetString());
			AddComponent(component);
			component->Init(componentData["serializedData"]);
		}
		
		for (auto& childData : data["children"].GetArray())
		{
			auto child = engine->CreateGameObject(childData["name"].GetString(), _self);
			child.lock()->Init(childData);
		}
	}

	void GameObject::Update(float deltaTime) {
		for (auto& component : _components)
			component->Update(deltaTime);

		for (auto& child : _children)
			child->Update(deltaTime);
	}

	void GameObject::Render(sre::RenderPass& renderPass) {
		for (auto& component : _components)
			component->Render(renderPass);

		for (auto& child : _children)
			child->Render(renderPass);
	}

	void GameObject::KeyEvent(SDL_Event& e) {
		for (auto& component : _components)
			component->KeyEvent(e);

		for (auto& child : _children)
			child->KeyEvent(e);
	}

	void GameObject::AddChild(std::shared_ptr<GameObject> p_object) {
		p_object->_parent = _self;
		_children.push_back(p_object);
	}

	void GameObject::AddComponent(std::shared_ptr<Component> p_component) {
		p_component->SetGameObject(_self);
		_components.push_back(p_component);
	}

	std::string GameObject::GetName() {
		return _name;
	}

	void GameObject::SetName(std::string p_name) {
		_name = p_name;
	}

	glm::mat4 GameObject::DeserializeTransform(rapidjson::Value& transformData) {
		auto pos = DeserializeVector(transformData["position"]);
		auto rot = DeserializeVector(transformData["rotation"]);
		auto scl = DeserializeVector(transformData["scale"]);

		return
			glm::scale(scl) *
			glm::translate(pos) *
			glm::mat4_cast(glm::quat(glm::radians(rot)));
	}

	rapidjson::Value GameObject::SerializeTransform(glm::mat4& transform) {
		rapidjson::Value ret(rapidjson::kObjectType);
		rapidjson::Document::AllocatorType& allocator = rapidjson::Document::AllocatorType::MemoryPoolAllocator();

		glm::vec3 position, scale;
		glm::quat rotation;

		// we don't really care about these for gameObjects, but we need to matck glm::decompose() signature
		glm::vec3 skew; glm::vec4 perspective;

		glm::decompose(transform, scale, rotation, position, skew, perspective);

		ret["position"] = SerializeVector(position);
		ret["rotation"] = SerializeVector(glm::degrees(glm::eulerAngles(rotation)));
		ret["scale"] = SerializeVector(scale);
		return ret;
	}

	glm::vec3 GameObject::DeserializeVector(rapidjson::Value& vectorData) {
		assert(vectorData.IsArray() && "Trying to deserialize a vector from non-vector json value");
		assert(vectorData.Size() == 3 && "Trying to deserialize a vector from vector json value that doesn't have 3 elements (only 3d vectors supported ATM)");

		glm::vec3 ret;
		for (int i = 0; i < vectorData.Size(); ++i)
			ret[i] = vectorData[i].GetFloat();

		return ret;
	}

	rapidjson::Value GameObject::SerializeVector(glm::vec3& vector) {
		rapidjson::Value ret(rapidjson::kArrayType);
		//rapidjson::Document d;
		//rapidjson::Document::AllocatorType& allocator = d.GetAllocator();
		rapidjson::Document::AllocatorType& allocator = rapidjson::Document::AllocatorType::MemoryPoolAllocator();

		for (int i = 0; i < vector.length(); ++i)
			ret.PushBack(vector[i], allocator);

		return ret;
	}
}