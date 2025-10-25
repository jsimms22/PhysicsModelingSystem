#pragma once

// vendors
// project headers
// std library
#include <cstdint>
#include <memory>
#include <string>

class Shader;

// Placeholder
class Texture
{
public:
    struct ImageData
    {
        std::int32_t width;
        std::int32_t height;
        std::int32_t channels; // color channels count
    };

    Texture(const std::string& file,
            std::uint32_t textureType, 
            std::uint32_t slotType,
            std::uint32_t m_formatType,
            std::uint32_t m_pixelType);
    
    ~Texture() { Destroy(); }
    
    void UpdateUniform(std::shared_ptr<Shader>& shader, const std::string& uniform, std::int32_t unit);

    void Bind();
    void Unbind();
    void Destroy();

private:
    std::uint32_t m_ID;
    std::uint32_t m_textureType;
};