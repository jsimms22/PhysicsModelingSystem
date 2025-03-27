#pragma once

#include <memory>
#include <vector>

#include "modelClass.hpp"
#include "types.hpp"
#include "fwd_math.hpp"

// TODO: move force update calculations to here

void ApplyForces(std::vector<std::shared_ptr<BaseModel>>& container, const std::shared_ptr<BaseModel>& floor);