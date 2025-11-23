#include <unordered_map>
#include <utility>
#include <fstream>
#include <vector>
#include <queue>
#include "Renderer.hpp"

#include "RayCore.hpp"

static std::queue<std::pair<std::string, Image>> s_LoadingQueue;
static std::unordered_map<std::string, TextureId> s_IntIds;
static std::vector<Texture> s_Textures;

void Renderer::beginDrawing() { BeginDrawing(); }
void Renderer::endDrawing() { EndDrawing(); }
void Renderer::clearBackground(Col color) { ClearBackground(toRay(color)); };

void Renderer::loadImages(const nlohmann::json& mapping)
{
	for (const auto& [key, path] : mapping.items())
	{
		s_LoadingQueue.push({ key, LoadImage(path.get<std::string>().c_str()) });
	}
}

bool Renderer::loadTexturesFromImages()
{
	if (s_LoadingQueue.empty()) return true;

	const auto& [stringId, image] = s_LoadingQueue.front();
	s_Textures.push_back(LoadTextureFromImage(image));
	s_IntIds[stringId] = s_Textures.size() - 1;
	UnloadImage(image);
	s_LoadingQueue.pop();

	return false;
}

void Renderer::unload()
{
	while (!s_Textures.empty())
	{
		UnloadTexture(s_Textures.back());
		s_Textures.pop_back();
	}
}

TextureId Renderer::getNumericalId(const std::string& stringId)
{
	if (!s_IntIds.count(stringId)) return NO_TEXTURE;
	return s_IntIds[stringId];
}

void Renderer::drawCeiling(Col color)
{
	DrawRectangle(
		0,
		0,
		GetScreenWidth(),
		GetScreenHeight() / 2,
		toRay(color)
	);
}

void Renderer::drawFloor(Col color)
{
	DrawRectangle(
		0,
		GetScreenHeight() / 2,
		GetScreenWidth(),
		GetScreenHeight() / 2,
		toRay(color)
	);
}

void Renderer::drawTexture(Rect rectangle, TextureId id, Col color)
{
	DrawTexturePro(
		s_Textures[id],
		Rectangle{0.0f,0.0f,(float)s_Textures[id].width, (float)s_Textures[id].height},
		toRay(rectangle),
		{ 0.0f,0.0f },
		0.0f,
		toRay(color)
	);
}

void Renderer::drawCollumn(int16_t index, float lineHeight, TextureId id, float point, bool darken, Col color)
{
	int32_t start = -lineHeight / 2 + GetScreenHeight() / 2;
	int32_t end = lineHeight / 2 + GetScreenHeight() / 2;
	float startWidth = (float)s_Textures[id].width * point;
	Rectangle destination{ (float)index, (float)start, 1, (float)end - start + 1 };

	DrawTexturePro(
		s_Textures[id],
		Rectangle{ startWidth,0.0f,1.0f, (float)s_Textures[id].height },
		destination,
		{0.0f,0.0f},
		0.0f,
		toRay(color)
	);

	if (darken)
	{
		DrawRectanglePro(
			destination,
			{0.0f,0.0f},
			0.0f,
			toRay(Colors::DarkTint)
		);
	}
}