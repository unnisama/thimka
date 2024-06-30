#include "camera.h"

Camera::Camera(int width, int height, Shader* shader)
{
    this->shader = shader;
    model = glm::mat4(1.0f);
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    this->WIDTH = width;
    this->HEIGHT = height;

    projection = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.01f, 1000.0f);

    AddResizeCallback([this](int width, int height){
        this->WindowResizeCallBack(width, height);
    });
    AddMouseWheelCallback([this](double xoff, double yoff){
        this->MouseWheelCallBack(xoff, yoff);
    });
}

void Camera::WindowResizeCallBack(int width, int height)
{
    this->WIDTH = width;
    this->HEIGHT = height;
    projection = glm::perspective(fov, (float)width / (float)height, 0.01f, 100.0f);
    shader->SetMat4f("uprojection", projection);
}

void Camera::SetUniforms()
{
    shader->SetMat4f("umodel", model);
    shader->SetMat4f("uview", view);
    shader->SetMat4f("uprojection", projection);
}

void Camera::Translate(glm::vec3 translate)
{
    view = glm::translate(view, translate);
    shader->SetMat4f("uview", view);
}

void Camera::RotateX(float r)
{
    view = glm::rotate(view, r, glm::vec3(1.0f, 0.0f, 0.0f));
    shader->SetMat4f("uview", view);
}
void Camera::RotateY(float r)
{
    view = glm::rotate(view, r, glm::vec3(0.0f, 1.0f, 0.0f));
    shader->SetMat4f("uview", view);
}
void Camera::RotateZ(float r)
{
    view = glm::rotate(view, r, glm::vec3(0.0f, 0.0f, 1.0f));
    shader->SetMat4f("uview", view);
}

void Camera::MouseWheelCallBack(double xoff, double yoff)
{
    // Translate(glm::vec3(0.0f, 0.0f, yoff));
}

void Camera::Inputs(GLFWwindow *window, ImVec2 wsize)
{
    float rotx = 0.0f;
    float roty = 0.0f;
    float rotz = 0.0f;

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)){
        double xpos;
        double ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        if (xpos < wsize.x && ypos < wsize.y){
            return;
        }

        auto currentpos = glm::vec2(xpos, ypos);

        if(isfirst){
            isfirst = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            prevmouse = currentpos;
        }

        auto diff = currentpos - prevmouse;

        // RotateY((diff.x/(WIDTH/2))*M_PI);
        // RotateX((diff.y/(HEIGHT/2))*M_PI);

        // ImGui::Text("X: %f, Y: %f\n", (diff.x/(WIDTH/2))*M_PI, (diff.y/(HEIGHT/2))*M_PI);

        prevmouse = currentpos;

    }else{
        if(!isfirst){
            isfirst = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

    if(glfwGetKey(window, GLFW_KEY_W)){
        Translate(glm::vec3(0.0f, 0.0f, speed));
    }
    else if(glfwGetKey(window, GLFW_KEY_S)){
        Translate(glm::vec3(0.0f, 0.0f, -speed));
    }
    if(glfwGetKey(window, GLFW_KEY_D)){
        Translate(glm::vec3(-speed, 0.0f, 0.0f));
    }
    else if(glfwGetKey(window, GLFW_KEY_A)){
        Translate(glm::vec3(speed, 0.0f, 0.0f));
    }
    if(glfwGetKey(window, GLFW_KEY_E)){
        Translate(glm::vec3(0.0f, speed, 0.0f));
    }
    else if(glfwGetKey(window, GLFW_KEY_Q)){
        Translate(glm::vec3(0.0f, -speed, 0.0f));
    }

}

Camera::~Camera()
{
}
