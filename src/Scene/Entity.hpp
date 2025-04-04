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
    Entity(const vec3f& position = {0.0f, 0.0f, 0.0f})
        : m_position{position} {}

    // Destructors
    virtual ~Entity() = default;

    virtual void Update() = 0;

    void SetPosition(const vec3f& position) { m_position = position; }
    vec3f GetPosition() const { return m_position; };

private:
    GUID guid;
    vec3f m_position = {0.0f, 0.0f, 0.0f};
};