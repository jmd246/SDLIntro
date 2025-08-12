#include <Camera.hpp>
Camera::Camera(glm::vec3 position ,
    glm::vec3 up ,
    float yaw ,
    float pitch )
{
    m_mouse_sensitivity = 0.1f;
    m_camera_speed = 1.0f;
    Zoom = 45.0f;
    m_pos = position;
    m_world_up = up;
    m_yaw = yaw;
    m_pitch = pitch;
    updateCameraVectors();
}
void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= m_mouse_sensitivity;
    yoffset *= m_mouse_sensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    if (constrainPitch)
    {
        if (m_pitch > 89.0f) m_pitch = 89.0f;
        if (m_pitch < -89.0f) m_pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::ProcessKeyboard(const char direction, float deltaTime) {
    float velocity = m_camera_speed * deltaTime;
    if (direction =='w')
        m_pos += m_front * velocity;
    if (direction == 's')
        m_pos -= m_front * velocity;
    if (direction == 'a')
        m_pos -= m_right * velocity;
    if (direction == 'd')
        m_pos += m_right * velocity;
}
void	Camera::updateCameraVectors(){
glm::vec3 front;
front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
front.y = sin(glm::radians(m_pitch));
front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
m_front = glm::normalize(front);
m_right = glm::normalize(glm::cross(m_front, m_world_up));
m_up = glm::normalize(glm::cross(m_right, m_front));

}
// Mouse scroll (zoom)
void Camera::ProcessMouseScroll(float yoffset) {
    Zoom -= yoffset;
    if (Zoom < 1.0f) Zoom = 1.0f;
    if (Zoom > 45.0f) Zoom = 45.0f;
}
glm::mat4   Camera::GetViewMatrix() {
    return  glm::lookAt(m_pos, m_pos + m_front, m_up);
}
glm::mat4 Camera::GetProjectionMatrix(float aspectRatio) {
    return glm::perspective(glm::radians(Zoom), aspectRatio, 0.1f, 100.0f);
}
