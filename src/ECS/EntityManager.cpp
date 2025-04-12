// vendors
// project headers
#include "../ECS/EntityManager.hpp"
// std library
#include <algorithm>

EntityManager::EntityManager()
{
    for (GUID id = 1; m_availableEntities.size() < MAX_ENTITIES; ++id) {
        m_availableEntities.push_back(Entity(id));
    }
}

Entity EntityManager::CreateEntity()
{
    if (m_availableEntities.size() != 1) {
        Entity newEntity = m_availableEntities.back();
        m_availableEntities.pop_back();
        
        return newEntity;
    }

    return Entity(0);
}

void EntityManager::DestroyEntity(Entity entity)
{
    if (m_availableEntities.size() > MAX_ENTITIES) { return; }

    m_componentFlags[entity.GetGUID()].reset();

    m_availableEntities.push_back(entity.GetGUID());
}

void EntityManager::SetComponentFlags(Entity entity, Signature flag)
{
    m_componentFlags[entity.GetGUID()] = flag;
}

Signature EntityManager::GetComponentFlags(Entity entity)
{
    return m_componentFlags[entity.GetGUID()];
}