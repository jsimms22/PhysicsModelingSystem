#pragma once

// project headers
#include "../fwd_math.hpp"
#include "../Renderer/Mesh.hpp"
#include "../Types/Shapes.hpp"
// std library
#include <cstdint>
#include <memory>
#include <vector>

namespace Geometry 
{
    class Generator
    {
    public:
        template <typename UNIT>
        static std::shared_ptr<Mesh> Create(const Sphere<UNIT>& sphere)
        {
            std::vector<vertex> vertices;
            std::vector<std::uint32_t> indices;
            const std::uint32_t vertexCount = (sphere.segments + 1) * (sphere.segments + 1);
            const std::uint32_t indexCount = sphere.segments * sphere.segments * 6;
            vertices.reserve(vertexCount);
            indices.reserve(indexCount);

            for (std::size_t y = 0; y <= sphere.segments; ++y)
            {
                for (std::size_t x = 0; x <= sphere.segments; ++x)
                {
                    const UNIT u = static_cast<UNIT>(x) / sphere.segments;
                    const UNIT v = static_cast<UNIT>(y) / sphere.segments;

                    const UNIT theta = u * 2.0f * PI;
                    const UNIT phi = v * PI;

                    const vec3<UNIT> pos{ sphere.radius * sin(phi) * cos(theta),
                                          sphere.radius * cos(phi),
                                           sphere.radius * sin(phi) * sin(theta) };
                    const vec3<UNIT> normal = vec3_normal(pos);

                    vertices.emplace_back(vertex{ pos, normal });
                }
            }

            const std::uint32_t stride = static_cast<std::uint32_t>(sphere.segments + 1);
            for (std::uint32_t y = 0; y < sphere.segments; ++y)
            {
                for (std::uint32_t x = 0; x < sphere.segments; ++x)
                {
                    const std::uint32_t v0 = y * stride + x;
                    const std::uint32_t v1 = v0 + 1;
                    const std::uint32_t v2 = (y + 1) * stride + x;
                    const std::uint32_t v3 = v2 + 1;

                    // triangle 1
                    indices.push_back(v0);
                    indices.push_back(v2);
                    indices.push_back(v1);
                    // triangle 2
                    indices.push_back(v1);
                    indices.push_back(v2);
                    indices.push_back(v3);
                }
            }

            return std::make_shared<Mesh>(std::move(vertices), std::move(indices));
        }

        template <typename UNIT>
        static std::shared_ptr<Mesh> Create(const Box<UNIT>& box)
        {
            const UNIT hx = box.extents.data[0] * UNIT(0.5);
            const UNIT hy = box.extents.data[1] * UNIT(0.5);
            const UNIT hz = box.extents.data[2] * UNIT(0.5);

            const std::vector<vertex> vertices =
            {
                {{-hx,-hy,-hz}, {-1,-1,-1}},
                {{ hx,-hy,-hz}, { 1,-1,-1}},
                {{ hx, hy,-hz}, { 1, 1,-1}},
                {{-hx, hy,-hz}, {-1, 1,-1}},

                {{-hx,-hy, hz}, {-1,-1, 1}},
                {{ hx,-hy, hz}, { 1,-1, 1}},
                {{ hx, hy, hz}, { 1, 1, 1}},
                {{-hx, hy, hz}, {-1, 1, 1}}
            };

            const std::vector<uint32_t> indices =
            {
                4,5,6, 4,6,7,
                0,2,1, 0,3,2,
                0,4,7, 0,7,3,
                1,2,6, 1,6,5,
                3,7,6, 3,6,2,
                0,1,5, 0,5,4
            };

            return std::make_shared<Mesh>(std::move(vertices), std::move(indices));
        }

        template <typename UNIT>
        static std::shared_ptr<Mesh> Create(const Capsule<UNIT>& capsule)
        {
            std::vector<vertex> vertices;
            std::vector<std::uint32_t> indices;

            const std::uint32_t segments =static_cast<std::uint32_t>(capsule.segments);
            const std::uint32_t rings = segments;
            const UNIT radius = capsule.radius;
            const UNIT cylinderHeight =std::max(UNIT(0),capsule.height - radius * UNIT(2));
            const UNIT halfCylinder =cylinderHeight * UNIT(0.5);

            vertices.reserve((segments + 1) * (rings + 1));
            indices.reserve(segments * rings * 6);

            for (std::uint32_t y = 0; y <= rings; ++y)
            {
                const UNIT v = static_cast<UNIT>(y) / static_cast<UNIT>(rings);
                const UNIT phi = v * PI;
                for (std::uint32_t x = 0; x <= segments; ++x)
                {
                    const UNIT u = static_cast<UNIT>(x) / static_cast<UNIT>(segments);
                    const UNIT theta = u * UNIT(2) * PI;

                    vec3<UNIT> normal
                    {
                        std::sin(phi) * std::cos(theta),
                        std::cos(phi),
                        std::sin(phi) * std::sin(theta)
                    };

                    vec3<UNIT> position = vec3_scale(radius, normal);

                    if (normal.data[1] > UNIT(0))
                    {
                        position.data[1] += halfCylinder;
                    }
                    else
                    {
                        position.data[1] -= halfCylinder;
                    }

                    vertices.emplace_back(vertex{position,normal});
                }
            }

            const std::uint32_t stride = segments + 1;
            for (std::uint32_t y = 0; y < rings; ++y)
            {
                for (std::uint32_t x = 0; x < segments; ++x)
                {
                    const std::uint32_t v0 = y * stride + x;
                    const std::uint32_t v1 = v0 + 1;
                    const std::uint32_t v2 = (y + 1) * stride + x;
                    const std::uint32_t v3 = v2 + 1;

                    indices.push_back(v0);
                    indices.push_back(v2);
                    indices.push_back(v1);

                    indices.push_back(v1);
                    indices.push_back(v2);
                    indices.push_back(v3);
                }
            }

            return std::make_shared<Mesh>(std::move(vertices), std::move(indices));
        }

        template <typename UNIT>
        static std::shared_ptr<Mesh> Create(const Plane<UNIT>& plane)
        {
            const UNIT halfWidth = plane.width * UNIT(0.5);
            const UNIT halfDepth = plane.depth * UNIT(0.5);

            std::vector<vertex> vertices;
            vertices.reserve(4);

            vertices.emplace_back(vertex{ {-halfWidth, 0, -halfDepth}, {0, 1, 0} });
            vertices.emplace_back(vertex{ { halfWidth, 0, -halfDepth}, {0, 1, 0} });
            vertices.emplace_back(vertex{ { halfWidth, 0,  halfDepth}, {0, 1, 0} });
            vertices.emplace_back(vertex{ {-halfWidth, 0,  halfDepth}, {0, 1, 0} });

            const std::vector<std::uint32_t> indices = { 0, 2, 1, 0, 3, 2 };
            return std::make_shared<Mesh>(std::move(vertices), std::move(indices));
        }
        
    };
}
