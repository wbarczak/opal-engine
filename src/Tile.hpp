#pragma once

#include <cstdint>
#include <string>
#include <cmath>
#include <memory>
#include "Renderer.hpp"
#include "Components.hpp"

class Tile
{
public:

	Tile(const std::string& stringTextureId) :
		m_TextureId(Renderer::getNumericalId(stringTextureId)),
		m_Health() {}

	Tile() :
		m_TextureId(Renderer::NO_TEXTURE),
		m_Health() {}

	TextureId textureId() const { return m_TextureId; }
	bool isSolid() const { return m_TextureId != Renderer::NO_TEXTURE; }

private:

	TextureId m_TextureId;
	Components::Health m_Health;
};