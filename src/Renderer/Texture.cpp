// vendors
#ifdef DEBUG
    #define STB_IMAGE_IMPLEMENTATION
    #include "../../vendor/STB/include/stb_image.h"
#else
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-but-set-variable" 
    #pragma GCC diagnostic ignored "-Wsign-compare"
    #pragma GCC diagnostic ignored "-Wstringop-overflow="
    #define STB_IMAGE_IMPLEMENTATION
    #include "../../vendor/STB/include/stb_image.h"
    #pragma GCC diagnostic pop
#endif
// project headers
#include "../Renderer/Texture.hpp"
// std library

Texture::Texture(const std::string& file,
                 uint32_t textureType, 
                 uint32_t slot,
                 uint32_t m_formatType,
                 uint32_t m_pixelType)
    : m_textureType{textureType}
{
    struct image
    {
        int32_t width;
        int32_t height;
        int32_t channels; // color channels count
    }image;
    
    // orient the image up
    stbi_set_flip_vertically_on_load(true);

    // read in the image from a file
    unsigned char* byteBuffer = stbi_load(file.c_str(), &image.width, &image.height, &image.channels, 0);

    glGenTextures(1,&m_ID);
    glActiveTexture(slot);
    Bind();

    // Configure the type of algorithm used for scaling the image
    glTexParameteri(m_textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(m_textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Configures the way the texture repeats (if it does at all)
	glTexParameteri(m_textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(m_textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Extra lines in case you choose to use GL_CLAMP_TO_BORDER
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

    // Assigns the image to the OpenGL Texture object
	glTexImage2D(m_textureType, 0, GL_RGBA, image.width, image.height, 0, m_formatType, m_pixelType, byteBuffer);
	// Generates MipMaps
	glGenerateMipmap(m_textureType);

    // free byte buffer here
    stbi_image_free(byteBuffer);

    // Unbind the OpenGL Texture object
    Unbind();
}

void Texture::UpdateUniform(std::shared_ptr<Shader>& shader, const std::string& uniform, uint32_t unit)
{
    uint32_t textureLocation = glGetUniformLocation(shader->GetID(), uniform.c_str());
    shader->Bind();
    glUniform1i(textureLocation,unit);
}