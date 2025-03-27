#pragma once

// std library
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <unordered_map>
// project headers
#include "fwd_math.hpp"
#include "meshClass.hpp"
#include "shaderClass.hpp"
// vendors
#define GLFW_INCLUDE_NONE
#include "../vendor/GL/include/glew.h"
#include "../vendor/GLFW/include/glfw3.h"

class IModel;

enum class ModelType
{
    Shape,
    Terrain,
    Light
};

std::shared_ptr<IModel> CreateModelFactory(ModelType type, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader);
std::shared_ptr<IModel> CreateModelFactory(ModelType type, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, vec3f position);

std::shared_ptr<IModel> CreateModelFactory(ModelType type, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, vec3f position, float scale);
std::shared_ptr<IModel> CreateModelFactory(ModelType type, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, vec3f position, float scale, unsigned int renderMode);
std::shared_ptr<IModel> CreateModelFactory(ModelType type, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, vec3f position, float scale, unsigned int renderMode, bool isPhysicalized);

// TODO: Think about how much upkeep I really want to do later on
//std::shared_ptr<IModel> CreateModelFactory(ModelType type, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, vec3f position, unsigned int renderMode);
//std::shared_ptr<IModel> CreateModelFactory(ModelType type, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, vec3f position, unsigned int renderMode, bool isPhysicalized);
//std::shared_ptr<IModel> CreateModelFactory(ModelType type, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, vec3f position, unsigned int renderMode, bool isPhysicalized, float scale);

//std::shared_ptr<IModel> CreateModelFactory(ModelType type, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, vec3f position, bool isPhysicalized);
//std::shared_ptr<IModel> CreateModelFactory(ModelType type, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, vec3f position, bool isPhysicalized, float scale);
//std::shared_ptr<IModel> CreateModelFactory(ModelType type, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, vec3f position, bool isPhysicalized, float scale, unsigned int renderMode);

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
    virtual void SetMesh(std::shared_ptr<Mesh> _mesh) = 0;

    virtual std::shared_ptr<Shader> GetShader() const = 0;
    virtual void SetShader(std::shared_ptr<Shader> _shader) = 0;

    virtual vec3f GetPosition() const = 0;
    virtual void SetPosition(const vec3f& _positionVec) = 0;

    virtual vec3f GetRotation() const = 0;
    virtual void SetRotation(const vec3f& _rotationVec) = 0;

    virtual float GetScale() const = 0;
    virtual void SetScale(float _scalarVec) = 0;

    virtual unsigned int GetRenderMethod() const = 0;
    virtual void SetRenderMethod(unsigned int _rendMethod) = 0;
    
    virtual bool IsPhysicalized() const = 0;
    virtual void SetIsPhysicalized(bool _enablePhysics) = 0;
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

    // Overrides from interface
    virtual void DestroyMesh() override { m_modelMesh->VAO.Destroy(); }
    virtual bool SupportsType(const ModelType type) const override = 0;
    virtual void AddMesh(std::shared_ptr<Shader> shader, std::string uniformName) override = 0;
    virtual void Update() override { std::cout << "I am a BaseModel.\n"; }

    // Data Member Methods
    std::shared_ptr<Mesh> GetMesh() const override { return m_modelMesh; }
    void SetMesh(std::shared_ptr<Mesh> _mesh) override
    { 
        if (!_mesh) { return; } 
        m_modelMesh= _mesh; 
    }

    std::shared_ptr<Shader> GetShader() const override { return m_modelShader; }
    void SetShader(std::shared_ptr<Shader> _shader) override
    { 
        if (!_shader) { return; } 
        m_modelShader= _shader; 
    }

    vec3f GetPosition() const override { return m_position; }
    void SetPosition(const vec3f& _positionVec) override { m_position = _positionVec; }

    vec3f GetRotation() const override { return m_rotation; }
    void SetRotation(const vec3f& _rotationVec) override { m_rotation = _rotationVec; }

    float GetScale() const override { return m_scale; }
    void SetScale(float _scalarVec) override { m_scale = _scalarVec; }

    unsigned int GetRenderMethod() const override { return m_renderMethod; }
    void SetRenderMethod(unsigned int _rendMethod) override { m_renderMethod = _rendMethod; }

    bool IsPhysicalized() const override { return m_enablePhysics; }
    void SetIsPhysicalized(bool _enablePhysics) override { m_enablePhysics = _enablePhysics; }

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
    bool SupportsType(const ModelType type) const override { return type == ModelType::Shape; };
    void AddMesh(std::shared_ptr<Shader> shader, std::string uniformName) override {};
    void Update() override { std::cout << "I am a Shape.\n"; };

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
    bool SupportsType(const ModelType type) const override { return type == ModelType::Terrain; };
    void AddMesh(std::shared_ptr<Shader> shader, std::string uniformName) override {};
    void Update() override { std::cout << "I am a Terrain.\n"; };

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
    bool SupportsType(const ModelType type) const override { return type == ModelType::Light; };
    void AddMesh(std::shared_ptr<Shader> shader, std::string uniformName) override;
    void Update() override;

    // Methods
    void UpdatePosition(); // Updates positon using arrow keys
    void UpdateUniform(const unsigned int& shaderID, const std::string& uniform); // Updates named shader uniform

    // Data Member Methods
    vec4f GetColor() const { return m_color; }
    void SetColor(const vec4f& _color) { m_color = _color; }

private:
    std::unordered_map<std::shared_ptr<Shader>, std::vector<std::string>> m_shaderUpdateMap;
    vec4f m_color = {0.9f, 0.9f, 0.8f, 1.0f};
};
