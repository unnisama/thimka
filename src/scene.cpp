#include "scene.h"

Scene::Scene(GLFWwindow *window, Gui *gui)
{
    this->window = window;
    this->gui = gui;
}

void Scene::Run(float dt)
{
    ImVec2 windSize = {0.0f, 0.0f};
    Update(dt);
    Draw();

    if(menuopen == true){
        gui->NewFrame();
        ImGui::SetNextWindowPos({0, 0});
        ImGui::SetNextWindowSize({-1, -1});
        ImGui::Begin("Setting", &menuopen, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);
        onGui(dt);
        windSize = ImGui::GetWindowSize();
        ImGui::End();
        gui->EndFrame();
    }else{
        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        {
            menuopen = true;
        }
    }
    if(camera != nullptr){
        camera->Inputs(window, windSize, dt);
    }
}

Scene::~Scene()
{
    
}
