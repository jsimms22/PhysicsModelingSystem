#pragma once

// vendors
// project headers
#include "../fwd_math.hpp"
#include "../types.hpp"
// std library
#include <memory>
#include <vector>

class IModel;
// TODO: move force update calculations to here

void ApplyForces(std::vector<std::shared_ptr<IModel>>& container);