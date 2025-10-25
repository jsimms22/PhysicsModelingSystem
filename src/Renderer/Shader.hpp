#pragma once

// vendors
// project headers
#include "../types.hpp"
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
    void SetUniform2fv(const std::string& uniformName, const vec2f& values); // float
    void SetUniform3fv(const std::string& uniformName, const vec3f& values); // float
    void SetUniform4fv(const std::string& uniformName, const vec4f& values); // float
    void SetUniform2dv(const std::string& uniformName, const vec2d& values); // double
    void SetUniform3dv(const std::string& uniformName, const vec3d& values); // double
    void SetUniform4dv(const std::string& uniformName, const vec4d& values); // double
    // Matrices
    // TODO: ints, unsigned ints, bools, 2x2mat
    void SetUniform3fm(const std::string& uniformName, const mat3x3f& values, bool transpose = false); // float
    void SetUniform4fm(const std::string& uniformName, const mat4x4f& values, bool transpose = false); // float
    void SetUniform3dm(const std::string& uniformName, const mat3x3d& values, bool transpose = false); // double
    void SetUniform4dm(const std::string& uniformName, const mat4x4d& values, bool transpose = false); // double

private:
    std::int32_t GetUniformLocation(const std::string& uniformName);
    std::string ReadFileContents(const std::string& filename);
    std::uint32_t CompileShader(std::uint32_t type, const std::string& fileText);

    std::uint32_t m_ID;
    std::unordered_map<std::string, std::int32_t> m_uniformLocationCache;
};