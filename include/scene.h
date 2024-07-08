#pragma once
#include "renderer.h"
#include "texture.h"
#include "mesh.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include "camera.h"
#include "Gui.h"

class Scene{
protected:
    Renderer renderer;
    bool menuopen = true;
    Camera *camera = nullptr;
    Gui *gui;
    GLFWwindow *window;

public:
    Scene(GLFWwindow *window, Gui* gui);
    void Run(float dt);
    virtual void Update(float dt) = 0;
    virtual void Draw() = 0;
    virtual void onGui(float dt) = 0;
    virtual void End() = 0;
    ~Scene();
};