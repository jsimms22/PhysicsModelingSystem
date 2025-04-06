// vendors
// project headers
#include "../Scene/Model.hpp"
// std library

std::shared_ptr<IModel> CreateModelFactory(ModelType type, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader)
{
    switch (type)
    {   
        case ModelType::Shape:
        {
            std::shared_ptr<Shape> model = std::make_shared<Shape>(mesh);
            model->SetShader(std::move(shader));
            return model;
        }
        case ModelType::Terrain:
        {
            std::shared_ptr<Terrain> model = std::make_shared<Terrain>(mesh);
            model->SetShader(std::move(shader));
            return model;
        }
        case ModelType::Light:
        {
            std::shared_ptr<Light> model = std::make_shared<Light>(mesh);
            model->SetShader(std::move(shader));
            return model;
        }
        default:
        {
            throw std::invalid_argument("Unknown ModelType");
        }
    }
}

std::shared_ptr<IModel> CreateModelFactory(ModelType type, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, vec3d position)
{
    switch (type)
    {   
        case ModelType::Shape:
        {
            std::shared_ptr<Shape> model = std::make_shared<Shape>(mesh);
            model->SetShader(std::move(shader));
            model->SetPosition(position);
            return model;
        }
        case ModelType::Terrain:
        {
            std::shared_ptr<Terrain> model = std::make_shared<Terrain>(mesh);
            model->SetShader(std::move(shader));
            model->SetPosition(position);
            return model;
        }
        case ModelType::Light:
        {
            std::shared_ptr<Light> model = std::make_shared<Light>(mesh);
            model->SetShader(std::move(shader));
            model->SetPosition(position);
            return model;
        }
        default:
        {
            throw std::invalid_argument("Unknown ModelType");
        }
    }
}

std::shared_ptr<IModel> CreateModelFactory(ModelType type, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, vec3d position, float scale){
    switch (type)
    {   
        case ModelType::Shape:
        {
            std::shared_ptr<Shape> model = std::make_shared<Shape>(mesh);
            model->SetShader(std::move(shader));
            model->SetPosition(position);
            model->SetScale(scale);
            return model;
        }
        case ModelType::Terrain:
        {
            std::shared_ptr<Terrain> model = std::make_shared<Terrain>(mesh);
            model->SetShader(std::move(shader));
            model->SetPosition(position);
            model->SetScale(scale);
            return model;
        }
        case ModelType::Light:
        {
            std::shared_ptr<Light> model = std::make_shared<Light>(mesh);
            model->SetShader(std::move(shader));
            model->SetPosition(position);
            model->SetScale(scale);
            return model;
        }
        default:
        {
            throw std::invalid_argument("Unknown ModelType");
        }
    }
}

std::shared_ptr<IModel> CreateModelFactory(ModelType type, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, vec3d position, float scale, uint32_t renderMode)
{
    switch (type)
    {   
        case ModelType::Shape:
        {
            std::shared_ptr<Shape> model = std::make_shared<Shape>(mesh);
            model->SetShader(std::move(shader));
            model->SetPosition(position);
            model->SetScale(scale);
            model->SetRenderMethod(renderMode);
            return model;
        }
        case ModelType::Terrain:
        {
            std::shared_ptr<Terrain> model = std::make_shared<Terrain>(mesh);
            model->SetShader(std::move(shader));
            model->SetPosition(position);
            model->SetScale(scale);
            model->SetRenderMethod(renderMode);
            return model;
        }
        case ModelType::Light:
        {
            std::shared_ptr<Light> model = std::make_shared<Light>(mesh);
            model->SetShader(std::move(shader));
            model->SetPosition(position);
            model->SetScale(scale);
            model->SetRenderMethod(renderMode);
            return model;
        }
        default:
        {
            throw std::invalid_argument("Unknown ModelType");
        }
    }
}

std::shared_ptr<IModel> CreateModelFactory(ModelType type, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, vec3d position, float scale, uint32_t renderMode, bool isPhysicalized)
{
    switch (type)
    {   
        case ModelType::Shape:
        {
            std::shared_ptr<Shape> model = std::make_shared<Shape>(mesh);
            model->SetShader(std::move(shader));
            model->SetPosition(position);
            model->SetScale(scale);
            model->SetRenderMethod(renderMode);
            model->SetIsPhysicalized(isPhysicalized);
            return model;
        }
        case ModelType::Terrain:
        {
            std::shared_ptr<Terrain> model = std::make_shared<Terrain>(mesh);
            model->SetShader(std::move(shader));
            model->SetPosition(position);
            model->SetScale(scale);
            model->SetRenderMethod(renderMode);
            model->SetIsPhysicalized(isPhysicalized);
            return model;
        }
        case ModelType::Light:
        {
            std::shared_ptr<Light> model = std::make_shared<Light>(mesh);
            model->SetShader(std::move(shader));
            model->SetPosition(position);
            model->SetScale(scale);
            model->SetRenderMethod(renderMode);
            model->SetIsPhysicalized(isPhysicalized);
            return model;
        }
        default:
        {
            throw std::invalid_argument("Unknown ModelType");
        }
    }
}

std::shared_ptr<IModel> CreateModelFactory(ModelType type, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, vec3d position, float scale, vec4f color)
{
    switch (type)
    {   
        case ModelType::Shape:
        {
            std::shared_ptr<Shape> model = std::make_shared<Shape>(mesh);
            model->SetShader(std::move(shader));
            model->SetPosition(position);
            model->SetScale(scale);
            model->SetColor(color);
            return model;
        }
        case ModelType::Terrain:
        {
            std::shared_ptr<Terrain> model = std::make_shared<Terrain>(mesh);
            model->SetShader(std::move(shader));
            model->SetPosition(position);
            model->SetScale(scale);
            model->SetColor(color);
            return model;
        }
        case ModelType::Light:
        {
            std::shared_ptr<Light> model = std::make_shared<Light>(mesh);
            model->SetShader(std::move(shader));
            model->SetPosition(position);
            model->SetScale(scale);
            model->SetColor(color);
            return model;
        }
        default:
        {
            throw std::invalid_argument("Unknown ModelType");
        }
    }
}

void Light::Update()
{ 
    //std::cout << "I am a Light.\n"; 

    UpdatePosition();
}

void Light::AddMesh(std::shared_ptr<Shader> shader, std::string uniformName)
{
    // TODO: rework map update to be more robust
    if (shader) { m_shaderUpdateMap[shader].push_back(uniformName); }
}

void Light::UpdatePosition() 
{
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) == GLFW_PRESS) {
        m_position.data[2] -= 1.0;
    }

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN) == GLFW_PRESS) {
        m_position.data[2] += 1.0;
    }

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT) == GLFW_PRESS) {
        m_position.data[0] -= 1.0;
    } 

    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
        m_position.data[0] += 1.0;
    } 
}