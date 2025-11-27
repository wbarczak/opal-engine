#include <unordered_map>
#include <utility>
#include <fstream>
#include <vector>
#include <queue>
#include "Renderer.hpp"
#include "Window.hpp"
#include "Systems.hpp"

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

static void drawCeiling(Col color)
{
	DrawRectangle(
		0,
		0,
		GetScreenWidth(),
		GetScreenHeight() / 2,
		toRay(color)
	);
}

static void drawFloor(Col color)
{
	DrawRectangle(
		0,
		GetScreenHeight() / 2,
		GetScreenWidth(),
		GetScreenHeight() / 2,
		toRay(color)
	);
}

void drawCollumn(int16_t index, float lineHeight, TextureId id, float point, bool darken, Col color = Colors::White)
{
	int32_t start = -lineHeight / 2 + Window::getHeight() / 2;
	int32_t end = lineHeight / 2 + Window::getHeight() / 2;
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

constexpr float k_Fov = std::numbers::pi / 180.0f * 90.0f;

void Systems::displayView(GameContext& context, size_t entityId)
{
	const int32_t width = Window::getWidth();
	const int32_t height = Window::getHeight();

	auto playerTransform = context.entities.get<Comp::Transform>(entityId);;
	auto position = playerTransform.position;
	auto angle = playerTransform.angle;
	const float angleIncrement = k_Fov / (float)width;
	float angleStart = angle - (k_Fov * 0.5f);

	drawCeiling(Colors::Gray);
	drawFloor(Colors::LightGray);

	for (size_t column = 0; column < width; ++column)
	{
		float rayAngle = angleStart + column * angleIncrement;
		Vec2 direction = Vec2::direction(rayAngle);

		auto hit = context.level.raycast(position, direction);

		if (!hit) continue;

		float perpendicularDistance = hit.value().distance * cosf(rayAngle - angle);
		int32_t lineHeight = (int)(height / perpendicularDistance);

		drawCollumn(
			column,
			lineHeight,
			hit.value().textureId,
			hit.value().point,
			hit.value().sideways
		);
	}
}