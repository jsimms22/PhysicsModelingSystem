#pragma once

// vendors
// project headers
#include "../Types/vertex.hpp"
// std library
#include <cstdint>
#include <vector>

std::vector<vertex> FloorVertex(std::uint32_t vertexCount, double length, double width);

std::vector<std::uint32_t> FloorIndex(std::uint32_t vertexCount);