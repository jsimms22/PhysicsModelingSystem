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

class IModel
{
public:
    // Destructor
    virtual ~IModel() = default;

    // Methods
    virtual void DestroyMesh() = 0;
    virtual void Update() = 0;
};

class BaseModel : public IModel
{
public:
// Constructors
    BaseModel() = default;
    BaseModel(std::shared_ptr<Mesh> _sourceMesh)
        : m_modelMesh{_sourceMesh} {}
    BaseModel(std::shared_ptr<Mesh> _sourceMesh, float _scalar, unsigned int _renderMethod)
        : m_modelMesh{_sourceMesh}, m_scale{_scalar}, m_renderMethod{_renderMethod} {}
    BaseModel(std::shared_ptr<Mesh> _sourceMesh, float _scalar, unsigned int _renderMethod, bool _physics)
        : m_modelMesh{_sourceMesh}, m_scale{_scalar}, m_renderMethod{_renderMethod}, m_enablePhysics(_physics) {}

    // Destructor
    ~BaseModel() { DestroyMesh(); }

    // Overrides
    void DestroyMesh() override { m_modelMesh->VAO.Destroy(); }
    virtual void Update() override { std::cout << "I am a BaseModel.\n"; }

    // Data Member Methods
    std::shared_ptr<Mesh> GetMesh() const { return m_modelMesh; }
    void SetMesh(std::shared_ptr<Mesh> _mesh)
    { 
        if (!_mesh) { return; } 
        m_modelMesh= _mesh; 
    }

    std::shared_ptr<Shader> GetShader() const { return m_modelShader; }
    void SetShader(std::shared_ptr<Shader> _shader)
    { 
        if (!_shader) { return; } 
        m_modelShader= _shader; 
    }

    vec3f GetPosition() const { return m_position; }
    void SetPosition(const vec3f& _positionVec) { m_position = _positionVec; }

    vec3f GetRotation() const { return m_rotation; }
    void SetRotation(const vec3f& _rotationVec) { m_rotation = _rotationVec; }

    float GetScale() const { return m_scale; }
    void SetScale(float _scalarVec) { m_scale = _scalarVec; }

    unsigned int GetRenderMethod() const { return m_renderMethod; }
    void SetRenderMethod(unsigned int _rendMethod) { m_renderMethod = _rendMethod; }

    bool IsPhysicalized() const { return m_enablePhysics; }
    void SetIsPhysicalized(bool _enablePhysics) { m_enablePhysics = _enablePhysics; }

protected:
    std::shared_ptr<Mesh> m_modelMesh;
    std::shared_ptr<Shader> m_modelShader;
    vec3f m_position = {0.0f, 0.0f, 0.0f};
    vec3f m_rotation = {0.0f, 0.0f, 0.0f};
    float m_scale = 1.f;
    unsigned int m_renderMethod = GL_TRIANGLES;
    bool m_enablePhysics = false;
};

class Shape : public BaseModel
{
public:
    // Constructors
    Shape() = default;
    Shape(std::shared_ptr<Mesh> _sourceMesh, bool _physics = true)
        : BaseModel(_sourceMesh) { m_enablePhysics = _physics; }
    Shape(std::shared_ptr<Mesh> _sourceMesh, float _scalar, unsigned int _renderMethod, bool _physics = true)
        : BaseModel(_sourceMesh, _scalar, _renderMethod, _physics) {}
    // Destructor
    ~Shape() = default;

    // Overrides
    void Update() override {{ std::cout << "I am a Shape.\n"; }};

    // Methods
};

class Terrain : public BaseModel
{
public:
    // Constructors
    Terrain() = default;
    Terrain(std::shared_ptr<Mesh> _sourceMesh)
        : BaseModel(_sourceMesh) {}
    Terrain(std::shared_ptr<Mesh> _sourceMesh, float _scalar, unsigned int _renderMethod)
        : BaseModel(_sourceMesh, _scalar, _renderMethod) {}

    // Destructor
    ~Terrain() = default;

    // Overrides
    void Update() override {{ std::cout << "I am a Terrain.\n"; }};

    // Methods
};

class Light : public BaseModel
{
public:
    // Constructors
    Light() = default;
    Light(std::shared_ptr<Mesh> _sourceMesh)
        : BaseModel(_sourceMesh) {}
    Light(std::shared_ptr<Mesh> _sourceMesh, float _scalar, unsigned int _renderMethod)
        : BaseModel(_sourceMesh, _scalar, _renderMethod) {}

    // Destructors
    ~Light() = default;

    // Overrides
    void Update() override {{ std::cout << "I am a Light.\n"; }};

    // Methods
    void UpdatePosition(GLFWwindow* window); // Updates positon using arrow keys
    void UpdateUniform(const unsigned int& shaderID, const std::string& uniform); // Updates named shader uniform

    // Data Member Methods
    vec4f GetColor() const { return m_color; }
    void SetColor(const vec4f& _color) { m_color = _color; }

private:
    vec4f m_color = {0.9f, 0.9f, 0.8f, 1.0f};
};
