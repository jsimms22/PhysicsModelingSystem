#pragma once

// vendors
#define GLFW_INCLUDE_NONE
#include "GL/glew.h"
#include "GLFW/glfw3.h"
// project headers
#include "../fwd_math.hpp"
#include "../Renderer/Mesh.hpp"
#include "../Renderer/Shader.hpp"
// std library
#include <iostream>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

class IModel;
class BaseModel;
class Shape;
class Terrain;
class Light;

enum class ModelType
{
    Shape,
    Terrain,
    Light
};

template <typename T, typename... Args>
std::enable_if_t<std::is_constructible<T, Args...>::value, std::shared_ptr<T>>
Create(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

template <class... Args>
std::shared_ptr<IModel> CreateModelFactory(ModelType type, Args&&... args)
{switch (type)
    {   
        case ModelType::Shape:
        {
            return Create<Shape>(std::forward<Args>(args)...);
        }
        case ModelType::Terrain:
        {
            return  Create<Terrain>(std::forward<Args>(args)...);
        }
        case ModelType::Light:
        {
            return  Create<Light>(std::forward<Args>(args)...);
        }
        default:
        {
            throw std::invalid_argument("Unknown ModelType");
        }
    }
}

class IModel
{
public:
    // Destructor
    virtual ~IModel() = default;

    // Methods
    virtual void DestroyMesh() = 0;
    virtual bool SupportsType(const ModelType type) const = 0;
    virtual void AddMesh(std::shared_ptr<Shader> shader, std::string uniformName) = 0;
    virtual void Update() = 0;

    virtual std::shared_ptr<Mesh> GetMesh() const = 0;
    virtual void SetMesh(std::shared_ptr<Mesh> mesh) = 0;

    virtual std::shared_ptr<Shader> GetShader() const = 0;
    virtual void SetShader(std::shared_ptr<Shader> shader) = 0;

    virtual vec3d GetPosition() const = 0;
    virtual void SetPosition(const vec3d& position) = 0;

    virtual vec3d GetRotation() const = 0;
    virtual void SetRotation(const vec3d& rotation) = 0;

    virtual float GetScale() const = 0;
    virtual void SetScale(float scalarVec) = 0;

    virtual std::uint32_t GetRenderMethod() const = 0;
    virtual void SetRenderMethod(std::uint32_t rendMethod) = 0;
    
    virtual bool IsPhysicalized() const = 0;
    virtual void SetIsPhysicalized(bool enablePhysics) = 0;

    virtual vec4f GetColor() const = 0;
    virtual void SetColor(const vec4f& color) = 0;
};

class BaseModel : public IModel
{
public:
// Constructors
    BaseModel() = default;
    BaseModel(std::shared_ptr<Mesh> mesh)
        : m_modelMesh{mesh} {}
    BaseModel(std::shared_ptr<Mesh> mesh, float scalar, std::uint32_t renderMethod)
        : m_modelMesh{mesh}, m_scale{scalar}, m_renderMethod{renderMethod} {}
    BaseModel(std::shared_ptr<Mesh> mesh, float scalar, std::uint32_t renderMethod, bool isPhysicalized)
        : m_modelMesh{mesh}, m_scale{scalar}, m_renderMethod{renderMethod}, m_isPhysicalized(isPhysicalized) {}

    // Destructor
    ~BaseModel() { DestroyMesh(); }

    // Overrides from interface
    virtual void DestroyMesh() override { m_modelMesh->m_VA0.Destroy(); }
    virtual bool SupportsType(const ModelType type) const override = 0;
    virtual void AddMesh(std::shared_ptr<Shader> shader, std::string uniformName) override = 0;
    virtual void Update() override { /*std::cout << "I am a BaseModel.\n";*/ }

    // Data Member Methods
    std::shared_ptr<Mesh> GetMesh() const override { return m_modelMesh; }
    void SetMesh(std::shared_ptr<Mesh> mesh) override
    { 
        if (!mesh) { return; } 
        m_modelMesh= mesh; 
    }

    std::shared_ptr<Shader> GetShader() const override { return m_modelShader; }
    void SetShader(std::shared_ptr<Shader> shader) override
    { 
        if (!shader) { return; } 
        m_modelShader= shader; 
    }

    vec3d GetPosition() const override { return m_position; }
    void SetPosition(const vec3d& position) override { m_position = position; }

    vec3d GetRotation() const override { return m_rotation; }
    void SetRotation(const vec3d& rotation) override { m_rotation = rotation; }

    float GetScale() const override { return m_scale; }
    void SetScale(float scalar) override { m_scale = scalar; }

    std::uint32_t GetRenderMethod() const override { return m_renderMethod; }
    void SetRenderMethod(std::uint32_t renderMethod) override { m_renderMethod = renderMethod; }

    bool IsPhysicalized() const override { return m_isPhysicalized; }
    void SetIsPhysicalized(bool isPhysicalized) override { m_isPhysicalized = isPhysicalized; }

    virtual vec4f GetColor() const override = 0;
    virtual void SetColor(const vec4f& color) override = 0;

protected:
    std::shared_ptr<Mesh> m_modelMesh;
    std::shared_ptr<Shader> m_modelShader;
    vec3d m_position = {0.0, 0.0, 0.0};
    vec3d m_rotation = {0.0, 0.0, 0.0};
    float m_scale = 1.0f;
    std::uint32_t m_renderMethod = GL_TRIANGLES;
    bool m_isPhysicalized = false;
};

class Shape : public BaseModel
{
public:
    // Constructors
    Shape() = default;
    Shape(std::shared_ptr<Mesh> mesh, bool isPhysicalized = true)
        : BaseModel(mesh) { m_isPhysicalized = isPhysicalized; }
    Shape(std::shared_ptr<Mesh> mesh, float scalar, std::uint32_t renderMethod, bool isPhysicalized = true)
        : BaseModel(mesh, scalar, renderMethod, isPhysicalized) {}
    // Destructor
    ~Shape() = default;

    // Overrides
    bool SupportsType(const ModelType type) const override { return type == ModelType::Shape; };
    void AddMesh(std::shared_ptr<Shader> shader, std::string uniformName) override { if (shader) { } };
    void Update() override { /*std::cout << "I am a Shape.\n";*/ };

    vec4f GetColor() const override { return {}; };
    void SetColor(const vec4f& color) override {};

    // Methods
};

class Terrain : public BaseModel
{
public:
    // Constructors
    Terrain() = default;
    Terrain(std::shared_ptr<Mesh> mesh)
        : BaseModel(mesh) {}
    Terrain(std::shared_ptr<Mesh> mesh, float scalar, std::uint32_t renderMethod)
        : BaseModel(mesh, scalar, renderMethod) {}

    // Destructor
    ~Terrain() = default;

    // Overrides
    bool SupportsType(const ModelType type) const override { return type == ModelType::Terrain; };
    void AddMesh(std::shared_ptr<Shader> shader, std::string uniformName) override { if (shader) { } };
    void Update() override { /*std::cout << "I am a Terrain.\n";*/ };

    vec4f GetColor() const override { return {}; };
    void SetColor(const vec4f& color) override {};

    // Methods
};

class Light : public BaseModel
{
public:
    // Constructors
    Light() = default;
    Light(std::shared_ptr<Mesh> mesh)
        : BaseModel(mesh) {}
    Light(std::shared_ptr<Mesh> mesh, float scalar, std::uint32_t renderMethod)
        : BaseModel(mesh, scalar, renderMethod) {}

    // Destructors
    ~Light() = default;

    // Overrides
    bool SupportsType(const ModelType type) const override { return type == ModelType::Light; };
    void AddMesh(std::shared_ptr<Shader> shader, std::string uniformName) override;
    void Update() override;

    // Methods
    void UpdatePosition(); // Updates positon using arrow keys

    // Data Member Methods
    vec4f GetColor() const override { return m_color; }
    void SetColor(const vec4f& color) override { m_color = color; }

private:
    std::unordered_map<std::shared_ptr<Shader>, std::vector<std::string>> m_shaderUpdateMap;
    vec4f m_color = {0.4f, 0.9f, 0.8f, 0.9f};
};
