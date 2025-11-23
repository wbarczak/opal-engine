#include "World.hpp"

World::World() :
    m_Width(0),
    m_Height(0) {}

World::World(const nlohmann::json& mapping) :
    m_Width(0),
    m_Height(0)
{
    load(mapping);
}

void World::load(const nlohmann::json& mapping)
{
    size_t length = -1;
    size_t size = 0;
    for (const auto& line : mapping["map"])
    {
        if (length == -1)
        {
            length = line.get<std::string>().length();
        }

        if (length != line.get<std::string>().length())
        {
            std::cerr << "The amount of columns is not equal in each row.";
        }

        ++size;
    }

    m_Width = length;
    m_Height = size;

    for (const auto& line : mapping["map"])
    {
        for (const auto& ch : line.get<std::string>())
        {
            if (ch == ' ')
            {
                m_Map.emplace_back();
            }
            else if (m_Tiles.count(ch))
            {
                m_Map.push_back(m_Tiles[ch]);
            }
        }
    }
}

std::optional<World::RaycastResult> World::raycast(Vec2 origin, Vec2 direction) const
{
    Vec2 rayUnitStepSize = {
        sqrtf(1 + (direction.y / direction.x) * (direction.y / direction.x)),
        sqrtf(1 + (direction.x / direction.y) * (direction.x / direction.y))
    };
    Vec2i mapCheck = static_cast<Vec2i>(origin);
    Vec2 rayLength1D;
    Vec2i step;

    if (direction.x < 0)
    {
        step.x = -1;
        rayLength1D.x = (origin.x - (float)mapCheck.x) * rayUnitStepSize.x;
    }
    else
    {
        step.x = 1;
        rayLength1D.x = ((float)(mapCheck.x + 1) - origin.x) * rayUnitStepSize.x;
    }
    if (direction.y < 0)
    {
        step.y = -1;
        rayLength1D.y = (origin.y - (float)mapCheck.y) * rayUnitStepSize.y;
    }
    else
    {
        step.y = 1;
        rayLength1D.y = ((float)(mapCheck.y + 1) - origin.y) * rayUnitStepSize.y;
    }

    std::optional<RaycastResult> out;
    float distance = 0.0f;
    float const maxDistance = 100.0f;
    while (distance < maxDistance)
    {
        bool sideways = false;
        if (rayLength1D.x < rayLength1D.y)
        {
            mapCheck.x += step.x;
            distance = rayLength1D.x;
            rayLength1D.x += rayUnitStepSize.x;
            sideways = true;
        }
        else
        {
            mapCheck.y += step.y;
            distance = rayLength1D.y;
            rayLength1D.y += rayUnitStepSize.y;
        }

        if (mapCheck.x >= 0 && mapCheck.y >= 0 &&
            mapCheck.x < m_Width && mapCheck.y < m_Height &&
            tile(mapCheck).isSolid())
        {
            auto finalHit = origin + direction * distance;
            float point = 0.0f;
            //fix slices not being calculated correctly
            if (sideways)
            {
                if (step.x == 1) point = finalHit.y - floorf(finalHit.y);
                else point = 1.0f - finalHit.y - floorf(finalHit.y);
            }
            else
            {
                if (step.y == 1) point = 1.0f - finalHit.x - floorf(finalHit.x);
                else point = finalHit.x - floorf(finalHit.x);
            }

            out = RaycastResult{
                distance,
                tile(mapCheck).textureId(),
                point,
                sideways
            };

            break;
        }
    }
    
    return out;
}

void World::loadTiles(const nlohmann::json& mapping)
{
    for (const auto& [key, value] : mapping.items())
    {
        m_Tiles[key[0]] = Tile(value.get<std::string>());
    }
}

void World::unloadTiles() { m_Tiles.clear(); }