#include "camera2.h"

Camera2::Camera2(int width, int height, glm::vec3 position, float FOVdeg, float nearPlane, float farPlane, Shader &shader)
{
	Camera2::width = width;
	Camera2::height = height;
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

void Camera2::Inputs(GLFWwindow *window, ImVec2 size)
{
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;
		Update();
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
		Update();
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
		Update();
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
		Update();
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * Up;
		Update();
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += speed * -Up;
		Update();
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.1f;
		sensitivity = 1.5f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.03f;
		sensitivity = 0.7f;
	}

	ImGui::Text("X: %.2f, Y: %.2f, Z: %.2f\n", Position.x, Position.y, Position.z);
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

		
		float rotX = M_PI * sensitivity * (float)diff.y / height;
		float rotY = M_PI * sensitivity * (float)diff.x / width;
		RotateXY(rotX, rotY);

		prevmouse = currentmouse;
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		firstClick = true;
	}
}
void Camera2::Update()
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);

	shader->SetMat4f("uview", view);
}

void Camera2::RotateXY(float rotx, float roty)
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

void Camera2::WindowResizeCallBack(int width, int height)
{
	auto projection = glm::perspective(glm::radians(fov), (float)width / height, near, far);
	Camera2::width = width;
	Camera2::height = height;
	shader->SetMat4f("uprojection", projection);
}
