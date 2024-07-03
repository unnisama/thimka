#include "camera.h"

Camera::Camera(int width, int height, glm::vec3 position, float FOVdeg, float nearPlane, float farPlane, Shader &shader)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
	near = nearPlane;
	far = farPlane;
	fov = FOVdeg;
	this->shader = &shader;
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	
	view = glm::lookAt(Position, Position + Orientation, Up);
	
	projection = glm::perspective(glm::radians(fov), (float)width / height, near, far);

	
	shader.SetMat4f("uview", view);
	shader.SetMat4f("uprojection", projection);

	AddResizeCallback([this](int width, int height){
        this->WindowResizeCallBack(width, height);
    });
}

void Camera::Inputs(GLFWwindow *window, ImVec2 size, float dt)
{
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation * dt;
		Update();
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up)) * dt;
		Update();
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation * dt;
		Update();
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up)) * dt;
		Update();
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * Up * dt;
		Update();
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += speed * -Up * dt;
		Update();
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = hspeed;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = lspeed;
	}

	
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{

		double mouseX;
		double mouseY;

		glfwGetCursorPos(window, &mouseX, &mouseY);

		if (firstClick)
		{
			prevmouse.x = mouseX;
			prevmouse.y = mouseY;
			firstmouse.x = mouseX;
			firstmouse.y = mouseY;
			firstClick = false;
		}

		if (size.x > firstmouse.x && size.y > firstmouse.y)
		{
			return;
		}

		
		auto currentmouse = glm::vec2(mouseX, mouseY);
		auto diff = currentmouse - prevmouse;

		
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		
		float rotX = M_PI  * (float)diff.y / height;
		float rotY = M_PI * (float)diff.x / width;
		RotateXY(rotX * sensitivity * dt, rotY * sensitivity * dt);

		prevmouse = currentmouse;
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		firstClick = true;
	}
}
void Camera::Update()
{
	glm::mat4 view = glm::lookAt(Position, Position + Orientation, Up);

	shader->SetMat4f("uview", view);
}

void Camera::RotateXY(float rotx, float roty)
{
	glm::vec3 newOrientation = glm::rotate(Orientation, -rotx, glm::normalize(glm::cross(Orientation, Up)));

	if (std::abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
	{
		Orientation = newOrientation;
	}

	// Rotates the Orientation left and right
	Orientation = glm::rotate(Orientation, -roty, Up);
	Update();
}

void Camera::WindowResizeCallBack(int width, int height)
{
	auto projection = glm::perspective(glm::radians(fov), (float)width / height, near, far);
	Camera::width = width;
	Camera::height = height;
	shader->SetMat4f("uprojection", projection);
}
