#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "Game.h"
#include "Gui.h"
#include "scene.h"
#include <functional>

class App{
private:
    Game *game;
    Gui *gui;
    std::vector<Scene*> scenes;
    std::string assetspath;
    
public:
    App(int WIDTH, int HEIGHT, const char *title, std::string assetspath);
    void Run(int index);
    void AddScene(std::function<Scene *(GLFWwindow *, Gui *, std::string)> func);
    ~App();
};

