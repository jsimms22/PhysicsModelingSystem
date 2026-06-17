#pragma once

// vendors
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
// project headers
// std library
#include <cstdlib>
#include <cstdint>
#include <string>
#include <unordered_map>

class Shader
{
public:
    // Constructors
    Shader(const std::string& vertexFile, const std::string& fragmentFile);
    // Destructors
    ~Shader() { Destroy(); }

    std::uint32_t GetID() const;
    void Bind();
    void Unbind();
    void Destroy();
    void AddUniformTypeName(const std::string& /*name*/) {}

    // Single Value
    void SetInteger(const std::string& uniformName, const std::int32_t value);
    void SetUnsigned(const std::string& uniformName, const std::uint32_t value);
    void SetFloat(const std::string& uniformName, const float value);
    void SetDouble(const std::string& uniformName, const double value);
    // Vectors
    // TODO: ints, unsigned ints, bools
    void SetUniform2fv(const std::string& uniformName, const glm::vec2& values); // float
    void SetUniform3fv(const std::string& uniformName, const glm::vec3& values); // float
    void SetUniform4fv(const std::string& uniformName, const glm::vec4& values); // float
    void SetUniform2dv(const std::string& uniformName, const glm::dvec2& values); // double
    void SetUniform3dv(const std::string& uniformName, const glm::dvec3& values); // double
    void SetUniform4dv(const std::string& uniformName, const glm::dvec4& values); // double
    // Matrices
    // TODO: ints, unsigned ints, bools, 2x2mat
    void SetUniform3fm(const std::string& uniformName, const glm::mat3x3& values, bool transpose = false); // float
    void SetUniform4fm(const std::string& uniformName, const glm::mat4x4& values, bool transpose = false); // float
    void SetUniform3dm(const std::string& uniformName, const glm::dmat3x3& values, bool transpose = false); // double
    void SetUniform4dm(const std::string& uniformName, const glm::dmat4x4& values, bool transpose = false); // double

private:
    std::int32_t GetUniformLocation(const std::string& uniformName);
    std::string ReadFileContents(const std::string& filename);
    std::uint32_t CompileShader(std::uint32_t type, const std::string& fileText);

    std::uint32_t m_ID;
    std::unordered_map<std::string, std::int32_t> m_uniformLocationCache;
};