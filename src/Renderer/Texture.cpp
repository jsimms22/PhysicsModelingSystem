// vendors
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wduplicated-branches"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic ignored "-Wuseless-cast"
#pragma GCC diagnostic ignored "-Wstringop-overflow="
#define STB_IMAGE_IMPLEMENTATION
#include "../../vendor/STB/include/stb_image.h"
#pragma GCC diagnostic pop
// project headers
#include "Texture.hpp"

#include "Shader.hpp"
// std library

Texture::Texture(const std::string& file,
                 std::uint32_t textureType,
                 std::uint32_t slot,
                 std::uint32_t m_formatType,
                 std::uint32_t m_pixelType)
    : m_textureType{textureType}
{
    Texture::ImageData image;

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

void Texture::UpdateUniform(std::shared_ptr<Shader>& shader, const std::string& uniform, std::int32_t unit)
{
    std::int32_t textureLocation = glGetUniformLocation(shader->GetID(), uniform.c_str());
    shader->Bind();
    glUniform1i(textureLocation,unit);
}

void Texture::Bind() { glBindTexture(m_textureType, m_ID); }

void Texture::Unbind() { glBindTexture(m_textureType, 0); }

void Texture::Destroy() { glDeleteTextures(1, &m_ID); }