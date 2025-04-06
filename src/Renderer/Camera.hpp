// vendors
// project headers
#include "../fwd_math.hpp"
#include "../types.hpp"
#include "../Renderer/Shader.hpp"
#include "../Events/Event.hpp"
// std library
#include <cmath>

class Camera
{
public:
    Camera() = default;
    Camera(const mat4x4d& matrix)
        : m_cameraMatrix(matrix) {}

    virtual ~Camera() = default;

    virtual void OnUpdate() = 0;
    virtual void OnEvent(Event& e) = 0;

    const mat4x4d& GetCameraMatrix() const { return m_cameraMatrix; }

protected:
    mat4x4d m_cameraMatrix{1.0f};
};