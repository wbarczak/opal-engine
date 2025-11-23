#pragma once

#include <optional>
#include <unordered_map>
#include <string>
#include "nlohmann/json.hpp"
#include "Renderer.hpp"
#include "Core.hpp"
#include "Tile.hpp"

class World
{
public:

	World();
	World(const nlohmann::json& mapping);
	void load(const nlohmann::json& mapping);

	struct RaycastResult
	{
		float distance = 0.0f;
		TextureId textureId = Renderer::NO_TEXTURE;
		float point = 0.0f;
		bool sideways = false;
	};

	std::optional<RaycastResult> raycast(Vec2 origin, Vec2 direction) const;
	int32_t width() const { return m_Width; }
	int32_t height() const { return m_Height; }
	const Tile& tile(float y, float x) const { return m_Map.at(y * m_Width + x); }
	const Tile& tile(Vec2i pos) const { return m_Map.at(pos.y * m_Width + pos.x); }

	static void loadTiles(const nlohmann::json& mapping);
	static void unloadTiles();

private:

	std::vector<Tile> m_Map;
	int32_t m_Width;
	int32_t m_Height;

	static inline std::unordered_map<char, Tile> m_Tiles;
};