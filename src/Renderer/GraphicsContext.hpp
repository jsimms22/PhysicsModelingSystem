#pragma once

// vendors
// project headers
// std library
#include <memory>

class GraphicsContext
{
public:
    // Constructors
    GraphicsContext() = default;
    
    // Destructors
    virtual ~GraphicsContext() = default;

    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;

    static std::unique_ptr<GraphicsContext> Create(void* window);
};