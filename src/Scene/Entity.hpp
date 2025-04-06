#pragma once

// vendors
// project headers
#include "../types.hpp"
// std library

class Entity
{
public:
    // Constructors
    Entity() = default;
    Entity(const vec3d& position = {0.0, 0.0, 0.0})
        : m_position{position} {}

    // Destructors
    virtual ~Entity() = default;

    virtual void Update() = 0;

    void SetPosition(const vec3d& position) { m_position = position; }
    vec3d GetPosition() const { return m_position; };

private:
    GUID guid;
    vec3d m_position = {0.0, 0.0, 0.0};
};