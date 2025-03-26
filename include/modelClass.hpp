#pragma once

// std library
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <memory>
// project headers
#include "meshClass.hpp"
#include "fwd_math.hpp"
#include "utility.hpp"
// vendors
#define GLFW_INCLUDE_NONE
#include "../vendor/GL/include/glew.h"
#include "../vendor/GLFW/include/glfw3.h"

class Model
{
public:
    // Constructor
    Model() = default;
    Model(std::shared_ptr<Mesh> _sourceMesh, unsigned int _renderMethod = GL_TRIANGLES);
    Model(std::shared_ptr<Mesh> _sourceMesh, float _scalar, unsigned int _renderMethod);
    
    // Destructor
    ~Model() { DestroyMesh(); }
    
    void DestroyMesh();
    
    // Getter and Setter for m_modelMesh
    std::shared_ptr<Mesh> GetMesh() const { return m_modelMesh; }
    void SetMesh(std::shared_ptr<Mesh> _mesh) { m_modelMesh = _mesh; }

    // Getter and Setter for m_modelShader
    std::shared_ptr<Shader> GetShader() const { return m_modelShader; }
    void SetShader(std::shared_ptr<Shader> _shader) { m_modelShader = _shader; }

    // Getter and Setter for m_position
    vec3f GetPosition() const { return m_position; }
    vec3f& GetPosition() { return m_position; }
    void SetPosition(const vec3f& _positionVec) { m_position = _positionVec; }

    // Getter and Setter for m_rotation
    vec3f GetRotation() const { return m_rotation; }
    vec3f& GetRotation() { return m_rotation; }
    void SetRotation(const vec3f& _rotationVec) { m_rotation = _rotationVec; }

    // Getter and Setter for m_scale
    float GetScale() const { return m_scale; }
    void SetScale(float _scalarVec) { m_scale = _scalarVec; }

    // Getter and Setter for m_renderMethod
    unsigned int GetRenderMethod() const { return m_renderMethod; }
    void SetRenderMethod(unsigned int _rendMethod) { m_renderMethod = _rendMethod; }

    // Getter and Setter for m_renderMethod
    bool IsPhysicalized() const { return m_enablePhysics; }
    void SetIsPhysicalized(bool _enablePhysics) { m_enablePhysics = _enablePhysics; }

protected:
    std::shared_ptr<Mesh> m_modelMesh;
    std::shared_ptr<Shader> m_modelShader;
    float m_scale = 1.f;
    unsigned int m_renderMethod = GL_POINTS;
    vec3f m_position = {0.0f, 0.0f, 0.0f};
    vec3f m_rotation = {0.0f, 0.0f, 0.0f};
    bool m_enablePhysics = true;
};

class Light : public Model
{
public:
    Light(std::shared_ptr<Mesh> _sourceMesh,
        float _scalar, 
        unsigned int _renderMethod);

    vec4f GetColor() const { return m_color; }
    void SetColor(const vec4f& _color) { m_color = _color; }

    // Updates positon using arrow keys
    void UpdatePosition(GLFWwindow* window);

    // Updates named shader uniform
    void UpdateUniform(const unsigned int& shaderID, const std::string& uniform);

protected:
    vec4f m_color = {0.9f, 0.9f, 0.8f, 1.0f};
};
