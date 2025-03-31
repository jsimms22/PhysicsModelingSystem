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

std::shared_ptr<IModel> CreateModelFactory(ModelType type, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, vec3f position)
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

std::shared_ptr<IModel> CreateModelFactory(ModelType type, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, vec3f position, float scale){
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

std::shared_ptr<IModel> CreateModelFactory(ModelType type, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, vec3f position, float scale, uint32_t renderMode)
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

std::shared_ptr<IModel> CreateModelFactory(ModelType type, std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader, vec3f position, float scale, uint32_t renderMode, bool isPhysicalized)
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

void Light::Update()
{ 
    //std::cout << "I am a Light.\n"; 

    UpdatePosition();

    for (std::pair<std::shared_ptr<Shader>, std::vector<std::string>> shaderPair : m_shaderUpdateMap)
    {
        shaderPair.first->Bind();
        for (std::string& name : shaderPair.second) { UpdateUniform(shaderPair.first->GetID(), name); }
        shaderPair.first->Unbind();
    }
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

void Light::UpdateUniform(const uint32_t shaderID, const std::string uniformName) 
{
    if (uniformName == "lightColor") {
        glUniform4f(glGetUniformLocation(shaderID, "lightColor"),
                    m_color.data[0], 
                    m_color.data[1], 
                    m_color.data[2], 
                    m_color.data[3]);
    }
    
    if (uniformName == "lightPosition") {
        glUniform3f(glGetUniformLocation(shaderID, "lightPosition"), 
                    m_position.data[0], 
                    m_position.data[1], 
                    m_position.data[2]);
    }
}