#pragma once

// vendors
// project headers
#include "../types.hpp"
#include "../Scene/Model.hpp"
// std library
#include <unordered_map>
#include <vector>
#include <string>

class Scene
{
public:
    Scene();
    ~Scene();
    
    // PLACEHOLDER
    const std::vector<std::shared_ptr<IModel>>& Load(const std::string& entityType);
    const std::shared_ptr<IModel>& CreateModel(const std::string& model_desc = {});
    void DestroyModel(IModel& model);

private:
    std::unordered_map<std::string, std::shared_ptr<IModel>> m_modelContainer;
};