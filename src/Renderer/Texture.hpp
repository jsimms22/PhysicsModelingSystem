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
            std::uint32_t textureType, 
            std::uint32_t slotType,
            std::uint32_t m_formatType,
            std::uint32_t m_pixelType);
    
    ~Texture() { Destroy(); }
    
    void UpdateUniform(std::shared_ptr<Shader>& shader, const std::string& uniform, std::uint32_t unit);

    void Bind() { glBindTexture(m_textureType, m_ID); }
    void Unbind() { glBindTexture(m_textureType, 0); }

    void Destroy() { glDeleteTextures(1, &m_ID); }

private:
    std::uint32_t m_ID;
    std::uint32_t m_textureType;
};