// vendors
#include <glm/mat4x4.hpp>
// project headers
// std library

class Event;

class Camera
{
public:
    Camera() = default;
    Camera(const glm::mat4& matrix)
        : m_cameraMatrix(matrix) {}

    virtual ~Camera() = default;

    virtual void OnUpdate() = 0;
    virtual void OnEvent(Event& e) = 0;

    const glm::mat4& GetCameraMatrix() const { return m_cameraMatrix; }

protected:
    glm::mat4 m_cameraMatrix{1.0f};
};