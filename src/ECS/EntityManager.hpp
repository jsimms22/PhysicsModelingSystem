#pragma once

// vendors
// project headers
#include "Components.hpp"
// std library
#include <array>
#include <cstdint>
#include <vector>

class Entity;

class EntityManager
{
    static constexpr std::uint64_t MAX_ENTITIES = 5001;
public:
    EntityManager();

    Entity CreateEntity();

    void DestroyEntity(Entity entity);

    void SetComponentFlags(Entity entity, Signature flag);

    Signature GetComponentFlags(Entity entity);

private:
    std::vector<Entity> m_availableEntities;
    std::array<Signature, MAX_ENTITIES> m_componentFlags;
};