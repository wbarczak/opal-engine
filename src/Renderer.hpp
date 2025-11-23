#pragma once

#include <string>
#include "nlohmann/json.hpp"
#include "Core.hpp"

using TextureId = int16_t;

namespace Renderer
{
	constexpr TextureId NO_TEXTURE = -1;

	void beginDrawing();
	void endDrawing();
	void clearBackground(Col color = Colors::Black);

	void loadImages(const nlohmann::json& mapping);
	bool loadTexturesFromImages();
	void unload();
	TextureId getNumericalId(const std::string& stringId);
	void drawCeiling(Col color);
	void drawFloor(Col color);
	void drawTexture(Rect rectangle, TextureId id, Col color = Colors::White);
	void drawCollumn(int16_t index, float lineHeight, TextureId id, float point, bool darken = false, Col color = Colors::White);
}