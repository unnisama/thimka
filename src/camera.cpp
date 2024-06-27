#include "camera.h"

Camera::Camera(int WIDTH, int HEIGHT, Shader* shader) : transform(1.0f)
{
    this->shader = shader;
    glm::vec3 scale(1.0f, 1.0f, 1.0f);
    glm::mat4 transform(1.0f);
    transform = glm::scale(transform, scale);
    auto eye = glm::vec3(0.0f, 0.0f, 20.0f);
    auto up = glm::vec3(0.0f, 1.0f, 0.0f);
    auto target = glm::vec3(0.0f, 0.0f, 0.0f);
    view = glm::lookAt(eye, target, up);

    projection = glm::perspective(fov, (float)WIDTH / (float)HEIGHT, near, far);

    AddResizeCallback([this](int width, int height){
        this->WindowResizeCallBack(width, height);
    });
}

void Camera::WindowResizeCallBack(int WIDTH, int HEIGHT)
{
    printf("WindowResizeCallBack\n");
    projection = glm::perspective(fov, (float)WIDTH / (float)HEIGHT, near, far);
    SetUniforms();
}

void Camera::SetUniforms()
{
    shader->SetMat4f("utransform", transform);
    shader->SetMat4f("uview", view);
    shader->SetMat4f("uprojection", projection);
}

void Camera::Inputs(GLFWwindow *window)
{
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
}

Camera::~Camera()
{
}
