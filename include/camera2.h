#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include "shader.h"
#include "imgui.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "callbackevents.h"


class Camera2
{
public:
	// Stores the main vectors of the camera
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec2 prevmouse;
	glm::vec2 firstmouse;
	float fov;
	float near;
	float far;
	Shader* shader;

	// Prevents the camera from jumping around when first clicking left click
	bool firstClick = true;

	// Stores the width and height of the window
	int width;
	int height;

	// Adjust the speed of the camera and it's sensitivity when looking around
	float speed = 0.1f;
	float sensitivity = 0.7f;

	// Camera constructor to set up initial values
	Camera2(int width, int height, glm::vec3 position, float FOVdeg, float nearPlane, float farPlane, Shader& shader);

	// Handles camera inputs
	void Inputs(GLFWwindow* window, ImVec2 size);

	void Update();

	void RotateXY(float rotx, float roty);

	void WindowResizeCallBack(int width, int height);

};
#endif