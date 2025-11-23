#pragma once

#include <algorithm>
#include <numeric>
#include "Core.hpp"

namespace Components
{
	struct Transform
	{
		float angle;
		Vec2 position;

		Transform(Vec2 position = {}, float angle = 0) :
			angle(angle),
			position(position) {}
	};

	struct Velocity
	{
		float max;
		float acceleration;
		float deceleration;
		Vec2 current;

		Velocity(float max = 20.0f, float acceleration = 40.0f, float deceleration = 60.0f, Vec2 starting = {}) :
			max(max),
			acceleration(acceleration),
			deceleration(deceleration),
			current(starting) {}

		Vec2 update(float dt, Vec2 direction);
	};

	struct Collider
	{
		float radius;

		Collider(float radius = 0.0f) :
			radius(radius) {}

		Vec2 colideAgainstWorld(Vec2 position, Vec2 deltaDistance);
		Cir getCurrent(Vec2 v) const { return Cir(v, radius); }
	};

	class Health
	{
	public:

		Health(float max) :
			m_Invincible(false),
			m_Max(max > 0? max : 1.0f),
			m_Current(max > 0? max : 1.0f) {}

		Health(float max, float current) :
			m_Invincible(false),
			m_Max(max > 0? max : 1.0f),
			m_Current(current > 0? max : 1.0f) {}

		Health() :
			m_Invincible(true),
			m_Max(std::numeric_limits<float>::max()),
			m_Current(std::numeric_limits<float>::max()) {}

		void damage(float health) { m_Current = std::max(m_Current - health, 0.0f); }
		void heal(float health) { m_Current = std::min(m_Current + health, m_Max); }
		float procentage() const { return m_Current / m_Max; }
		bool isAlive() const { return m_Current > 0.0f; }

	private:

		bool m_Invincible;
		float m_Max;
		float m_Current;
	};

	class Display
	{

	};
}