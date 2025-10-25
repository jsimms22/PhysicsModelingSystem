#pragma once

// vendors
// project headers
// std library
#include <memory>
#include <vector>

class IModel;
// TODO: move force update calculations to here

void ApplyForces(std::vector<std::shared_ptr<IModel>>& container);