#pragma once

#include <map>
#include <string>

#include "Component.h"

namespace MyEngine {
	class ComponentFactory {
	private:
		ComponentFactory() = delete;

		static std::map<std::string, std::shared_ptr<MyEngine::Component>> _componentMap;

	public:
		static void RegisterComponentOfType(std::string typeId, std::shared_ptr<MyEngine::Component> component);
		static std::shared_ptr<MyEngine::Component> GetComponentOfType(std::string typeId);
	};
}