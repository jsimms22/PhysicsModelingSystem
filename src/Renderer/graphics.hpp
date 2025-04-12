#pragma once

// vendors
// project headers
#include "../fwd_math.hpp"
// std library

std::vector<vertex> FloorVertex(std::uint32_t vertexCount, double length, double width);

std::vector<std::uint32_t> FloorIndex(std::uint32_t vertexCount);