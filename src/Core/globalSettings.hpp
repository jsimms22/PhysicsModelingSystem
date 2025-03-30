#pragma once

// vendors
// project headers
#include "../fwd_math.hpp"
// std library
#include <cstdint>

// TODO: Rework settings to be something better than a singleton at some point
// TODO: Until then the members should probably be static

class GlobalSettings
{
public:
    // Public access to the instance
    static GlobalSettings& Instance()
    {
        static GlobalSettings instance; // Guaranteed to be destroyed.
        return instance;
    }

    // Global settings variables

    // Window Settings
    uint32_t WIDTH {1280};
    uint32_t HEIGHT {1280};

    // Rendering Settings
    int STRIDE {8};
    int INSTANCE_STRIDE {3};

    // Model Settings
    float CONTAINER_RADIUS {6.0f};
    float VERLET_RADIUS {0.15f};
    vec3f TERRAIN_FLOOR {0.0f, -(CONTAINER_RADIUS * 2.0f + VERLET_RADIUS * 3.0f), 0.0f};

    // Game Loop Settings
    uint32_t TARGET_FPS {30};
    std::size_t MAX_INSTANCES {300};
    uint32_t ADDITION_SPEED {1};
    //int VERTEX_LIMIT {2000};

    // Force Calculation Settings
    // TODO: properly calculate forces
    vec3f GRAVITY = {0.0f,-9.8f,0.0f};

    // Delete copy constructor and assignment operator to prevent copying the singleton
    GlobalSettings(const GlobalSettings&) = delete;
    void operator=(const GlobalSettings&) = delete;

private:
    // Private constructor to prevent instantiation outside the class
    GlobalSettings() {}
};