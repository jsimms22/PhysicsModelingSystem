#pragma once

// vendors
// project headers
// std library
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

class Entity;
class Terrain;
class BaseModel;
class Light;

class Scene
{
public:
    Scene() = default;
    ~Scene() = default;

    bool WriteAttributes();
    bool ReadAttributes();

private:
    std::uint32_t m_ViewportWidth = 0;
    std::uint32_t m_ViewportHeight = 0;
    bool m_IsRunning = false;
    bool m_IsPaused = false;
    bool m_EnablePhysics = false;

    std::unordered_map<std::string, Entity> m_entityMap;
    std::vector<Terrain> m_vTerrain;
    std::vector<BaseModel> m_vModels;
    std::vector<Light> m_vLights;

    // friends
    friend class Entity;
};