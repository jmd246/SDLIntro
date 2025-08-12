#ifndef CAMERA_HPP
#define CAMERA_HPP
#include	<iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
class Camera{
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		float yaw = -90.0f,
		float pitch = 0.0f);
	//front
	glm::vec3	m_front;
	//up
	glm::vec3	m_up;
	//world	up
	glm::vec3	m_world_up;
	//right
	glm::vec3	m_right;

	//direction
	glm::vec3	m_direction;

	//position
	glm::vec3	m_pos;

	float	m_yaw, m_pitch;
	//settings
	float	m_camera_speed;
	float	m_mouse_sensitivity;
	float	Zoom;
	
	void ProcessMouseScroll(float yoffset);
	glm::mat4 GetViewMatrix();
	// Returns the projection matrix
	glm::mat4 GetProjectionMatrix(float aspectRatio);
	void ProcessKeyboard(const char direction, float deltaTime);
	// Recalculate the Front, Right, and Up vectors from the camera's (updated) Euler angles
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch);
private:
	void updateCameraVectors();


};
#endif