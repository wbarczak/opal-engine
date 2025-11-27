#pragma once

#include "World.hpp"
#include "EntityManager.hpp"

struct GameContext
{
	World level;
	EntityManager entities;
};

namespace Systems
{
	void resolveWorldColisions(GameContext& context);
	void applyVelocity(GameContext& context, float dt);
	void displayView(GameContext& context, size_t currentEntity);
	void moveControlable(GameContext& context, float dt);
}