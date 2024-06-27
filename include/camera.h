#pragma once
#include "debug.h"
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "shader.h"
#include "callbackevents.h"
#include <GLFW/glfw3.h>

class Camera{

private:
    glm::mat4 transform;
    glm::mat4 view;
    glm::mat4 projection;
    float fov = M_PI/2.0f;
    float near = 0.01f;
    float far = 10000.0f;
    Shader *shader;

public:
    Camera(int WIDTH, int HEIGHT, Shader* shader);
    void WindowResizeCallBack(int WIDTH, int HEIGHT);
    void SetUniforms();
    void Inputs(GLFWwindow *window);
    ~Camera();
};