#include "ComponentFactory.h"

namespace MyEngine {
	std::map<std::string, std::shared_ptr<MyEngine::Component>> ComponentFactory::_componentMap = {};

	void ComponentFactory::RegisterComponentOfType(std::string typeId, std::shared_ptr<MyEngine::Component> component) {
		_componentMap[typeId] = component;
	}

	std::shared_ptr<MyEngine::Component> ComponentFactory::GetComponentOfType(std::string typeId) {
		return _componentMap[typeId];
	}
}