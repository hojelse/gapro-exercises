#pragma once

#include "sre/SpriteAtlas.hpp"
#include "sre/Sprite.hpp"

#include "Engine/Component.h"

namespace ExampleGame {
	class ComponentRendererSprite : public MyEngine::Component {
	public:
		sre::Sprite sprite;

		void Render(sre::SpriteBatch::SpriteBatchBuilder&) override;
	};
}