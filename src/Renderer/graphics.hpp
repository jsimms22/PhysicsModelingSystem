#pragma once

// vendors
// project headers
#include "../fwd_math.hpp"
// std library

std::vector<vertex> FloorVertex(uint32_t vertexCount, double length, double width);

std::vector<uint32_t> FloorIndex(uint32_t vertexCount);