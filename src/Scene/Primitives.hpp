#pragma

// project header
#include "../Types/Shapes.hpp"
// std library
#include <variant>

template<typename UNIT>
class PrimitiveShape
{
public:
	using ShapeVariant = std::variant<Sphere<UNIT>, Box<UNIT>, Capsule<UNIT>, Plane<UNIT>>;

	PrimitiveShape() = default;

	template<typename Shape>
	PrimitiveShape(const Shape& shape) : m_shape(shape) {}

    template<typename Shape>
    bool is() const { return std::holds_alternative<Shape>(m_shape); }

    template<typename Shape>
    Shape& get() { return std::get<Shape>(m_shape); }

    template<typename Shape>
    const Shape& get() const { return std::get<Shape>(m_shape); }

private:
	ShapeVariant m_shape;
};

