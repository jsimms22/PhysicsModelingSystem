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
    Entity(GUID id)
        : m_handle{id} {}

    // Destructors
    ~Entity() = default;

    const GUID& GetGUID() const { return m_handle; }

private:
    GUID m_handle;
};