#pragma once

// vendors
// project headers
#include "../types.hpp"
#include "../Scene/Model.hpp"
// std library
#include <unordered_map>
#include <vector>
#include <string>

class Entity;

class Scene
{
public:
    Scene();
    ~Scene();

private: // methods

private: // members
    std::uint32_t m_ViewportWidth = 0;
    std::uint32_t m_ViewportHeight = 0;
    bool m_IsRunning = false;
    bool m_IsPaused = false;
    bool m_EnablePhysics = false;

    std::unordered_map<std::string, Entity> m_entityMap;

private: // friends
    friend class Entity;
};