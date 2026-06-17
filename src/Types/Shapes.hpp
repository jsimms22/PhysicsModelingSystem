#pragma once

// vendor
#include <glm/vec4.hpp>
// project headers
// std library
#include <cstdint>

template <typename UNIT>
struct Sphere
{
	UNIT radius{ static_cast<UNIT>(1) };
	std::uint32_t segments{ 16 };
};

template <typename UNIT>
struct Box
{
	glm::vec<3, UNIT> extents{ static_cast<UNIT>(1), 
								static_cast<UNIT>(1), 
								static_cast<UNIT>(1) };
};

template <typename UNIT>
struct Capsule
{
	UNIT radius{ static_cast<UNIT>(1) };
	UNIT height{ static_cast<UNIT>(4) };
	std::size_t segments = 16;
};

template <typename UNIT>
struct Plane
{
	UNIT width{ static_cast<UNIT>(10) };
	UNIT depth{ static_cast<UNIT>(10) };
};

