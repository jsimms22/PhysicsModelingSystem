#pragma once

// vendors
// project headers
#include "../fwd_math.hpp"
// std library

std::vector<vertexf> FloorVertex(uint32_t vertexCount, float length, float width);

std::vector<uint32_t> FloorIndex(uint32_t vertexCount);