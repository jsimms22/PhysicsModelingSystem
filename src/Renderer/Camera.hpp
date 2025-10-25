// vendors
// project headers
#include "../Types/mat4x4.hpp"
// std library

class Event;

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