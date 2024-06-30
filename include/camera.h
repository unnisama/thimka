#pragma once
#include "debug.h"
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "shader.h"
#include "callbackevents.h"
#include <GLFW/glfw3.h>
#include "imgui.h"

class Camera{

private:
    glm::mat4 view;
    glm::mat4 projection;
    float fov = 45.0f;
    Shader *shader;
    glm::vec2 prevmouse;
    float speed = 0.04f;
    int WIDTH;
    int HEIGHT;
    bool isfirst = true;
    glm::vec2 startpos;

public:
    Camera(int width, int height, Shader* shader);
    void WindowResizeCallBack(int width, int height);
    void SetUniforms();
    void Translate(glm::vec3 translate);
    void RotateX(float r);
    void RotateY(float r);
    void RotateZ(float r);
    void MouseWheelCallBack(double xoff, double yoff);
    void Inputs(GLFWwindow *window, ImVec2 wsize);
    ~Camera();
public:
    glm::mat4 model;
};