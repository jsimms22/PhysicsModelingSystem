// vendors
// project headers
#include "../fwd_math.hpp"
#include "../types.hpp"
#include "../Renderer/Shader.hpp"
// std library
#include <cmath>

class Camera
{
public:
    Camera() = default;
    Camera(const mat4x4f& matrix)
        : m_cameraMatrix(matrix) {}

    virtual ~Camera() = default;

    const mat4x4f& GetCameraMatrix() const { return m_cameraMatrix; }

protected:
    mat4x4f m_cameraMatrix{1.0f};
};