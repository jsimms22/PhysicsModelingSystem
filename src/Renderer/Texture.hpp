#pragma once

// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/glew.h"
#include "../../vendor/GLFW/include/glfw3.h"
// project headers
#include "../types.hpp"
#include "../Renderer/Shader.hpp"
// std library
#include <string>
#include <memory>

// Placeholder
class Texture
{
public:
    Texture(const std::string& file,
            uint32_t textureType, 
            uint32_t slotType,
            uint32_t m_formatType,
            uint32_t m_pixelType);
    
    ~Texture() { Destroy(); }
    
    void UpdateUniform(std::shared_ptr<Shader>& shader, const std::string& uniform, uint32_t unit);

    void Bind() { glBindTexture(m_textureType, m_ID); }
    void Unbind() { glBindTexture(m_textureType, 0); }

    void Destroy() { glDeleteTextures(1, &m_ID); }

private:
    uint32_t m_ID;
    uint32_t m_textureType;
};