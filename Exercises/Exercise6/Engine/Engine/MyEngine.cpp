#include "MyEngine.h"

#include <random>
#include <fstream>

#include "sre/RenderPass.hpp"
#include <sre/Inspector.hpp>

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/stringbuffer.h"

#include "rapidjson/writer.h"

namespace MyEngine {
	Engine* Engine::_instance = nullptr;

	Engine::Engine() {
		assert(_instance == nullptr && " Only one instance of MyEngine::Engine allowed!");
		_instance = this;

		_root = std::make_shared<GameObject>();
		_root->SetName("root");
	}

	glm::vec2 Engine::GetScreenSize() const
	{
		return WIN_SIZE;
	}

	void Engine::Init(std::string sceneFile) {
		// initializes random generator
		std::srand(std::time(nullptr));

		_renderer.frameRender = [this]() { Render(); };
		_renderer.frameUpdate = [this](float deltaTime) { Update(deltaTime); };
		_renderer.keyEvent = [this](SDL_Event& event) { ProcessEvents(event); };
		_renderer.setWindowSize(WIN_SIZE);
		_renderer.init();

		// load scene file
		std::ifstream fis(sceneFile);
		rapidjson::IStreamWrapper isw(fis);
		rapidjson::Document document;
		document.ParseStream(isw);

		_root = std::shared_ptr<GameObject>(CreateGameObject("root"));
		_root->_parent = std::shared_ptr<GameObject>(nullptr); // we make sure that the root has no parent
		_root->Init(document["root"]);
		_renderer.startEventLoop();
	}

	void Engine::ProcessEvents(SDL_Event& event) {
		if (event.key.keysym.sym == SDLK_F1 && event.type == SDL_KEYDOWN)
			showDebugWindow = !showDebugWindow;

		_root->KeyEvent(event);
	}

	void Engine::Update(float deltaTime) {
		++frame;
		time += deltaTime;
		_root->Update(deltaTime);
	}

	void Engine::Render()
	{
		sre::RenderPass renderPass = sre::RenderPass::create()
			.withCamera(_camera)
			.withClearColor(true, { .3f, .3f, 1, 1 })
			.build();

		_root->Render(renderPass);

		static sre::Inspector profiler;

		if (showDebugWindow)
		{
			profiler.update();
			profiler.gui(false);
		}
	}

	std::weak_ptr<GameObject> Engine::CreateGameObject(std::string name) {
		auto ret = std::make_shared<GameObject>();
		ret->_self = ret;
		ret->_parent = _root;
		ret->SetName(name);
		_root->AddChild(ret);

		return ret;
	}

	std::weak_ptr<GameObject> Engine::CreateGameObject(std::string name, std::weak_ptr<GameObject> p_parent) {
		auto parent = p_parent.lock();
		if (!parent)
			return std::shared_ptr<GameObject>(nullptr);

		auto ret = std::make_shared<GameObject>();
		ret->_self = ret;
		ret->_parent = p_parent;
		ret->SetName(name);
		parent->AddChild(ret);

		return ret;
	}

	void Engine::DestroyGameObject(GameObject* gameObject) {
		if (gameObject == nullptr)
			return;

		if (auto parent = gameObject->_parent.lock())
		{
			parent->_children.remove_if([gameObject](std::shared_ptr<GameObject> child) { return child.get() == gameObject; });
		}
	}
}