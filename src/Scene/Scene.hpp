#pragma once

// vendors
// project headers
#include "../types.hpp"
#include "../Scene/Model.hpp"
// std library
#include <unordered_map>

class Scene
{
public:
    Scene();
    ~Scene();

    const std::shared_ptr<IModel>& CreateModel(const std::string& model_desc = {});
    void DestroyModel(IModel& model);

private:
    std::unordered_map<std::string, std::shared_ptr<IModel>> m_modelContainer;
};