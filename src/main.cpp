#include "vertexbuffer.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <stdio.h>
#include "Game.h"
#include <iostream>
#include <string>
#include "Gui.h"
#include "shader.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "timer.h"
#include "renderer.h"
#include "texture.h"
#include <iomanip>
#include "camera.h"
#include <random>
#include "mesh.h"
#include <unordered_map>

int WIDTH = 640;
int HEIGHT = 480;

void printMat4(const glm::mat4 &mat)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            std::cout << std::fixed << std::setprecision(2) << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main(void)
{
    Game game(WIDTH, HEIGHT, "Start");
    //game.EnableDebug();

    Gui gui(game.GetWindow(), &game);

    Renderer renderer;

    Shader shader("../assets/shaders/fragment.glsl", "../assets/shaders/vertex.glsl");

    if(!shader.GetStatus()){
        printf("Shader failed!\n");
        exit(0);
    }

    shader.Use();

    Texture texture("../assets/textures/imas.png", 0);
    texture.Bind(0);

    shader.SetUniform1i("u_texture", texture.GetSlotID());

    float dt = 0.0f;

    Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 0.0f), 45.0f, 0.01f, 100.0f, shader);
    bool menuopen = true;

    glm::vec3 t(0.0f);
    int cindex = -1;

    std::vector<Mesh *> meshes;
    std::vector<char *> listinfo;
    shader.SetUniform1i("width", texture.getWidth());
    shader.SetUniform1i("height", texture.getHeight());
    int radius = 5;
    
    while (!game.ShouldClose())
    {
        ImVec2 windSize = {0.0f, 0.0f};
        GLDEBUGCALL(glClearColor(0.094f, 0.094f, 0.094f, 1.0f));
        GLDEBUGCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        for(int i = 0; i < meshes.size(); i++){
            meshes[i]->Draw(renderer, shader);
        }

        gui.NewFrame();

        if (menuopen == true)
        {
            ImGui::SetNextWindowPos({0, 0});
            ImGui::SetNextWindowSize({-1, -1});
            ImGui::Begin("Setting", &menuopen, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);

            {
                ImGui::Text("UpTime: %.3f", game.GetTime());
                ImGui::Text("FTime: %.3f", dt);
                ImGui::Text("FPS: %.f", 1.0f / dt);

                if(ImGui::DragInt("Radius", &radius, 1.0f, 5, 12)){
                    shader.SetUniform1i("radius", radius);
                }

                ImGui::Separator();

                ImGui::DragFloat3("Position", glm::value_ptr(t), 0.01f, -20.0f, 20.0f);

                if(ImGui::Button("Add Cube")){
                    Mesh *mesh = new Mesh(MeshPrimitive::Cube);
                    mesh->Translate(t);
                    meshes.push_back(mesh);
                    char *d = (char *)malloc(10);
                    int si = (int)meshes.size();
                    sprintf(d, "%d", si-1);
                    listinfo.push_back(d);
                }

                
                if (meshes.size() > 0)
                {
                    ImGui::Separator();
                    ImGui::ListBox("##objects", &cindex, listinfo.data(), listinfo.size());

                    if(cindex != -1){
                        if (ImGui::Button("Remove Cube"))
                        {
                            listinfo.erase(listinfo.begin() + cindex);
                            meshes.erase(meshes.begin() + cindex);
                        }
                    }
                   
                }

                windSize = ImGui::GetWindowSize();
            }

            ImGui::End();
        }

        gui.EndFrame();

        camera.Inputs(Game::GetWindow(), windSize, dt);

        if (menuopen == false)
        {
            if (glfwGetKey(game.GetWindow(), GLFW_KEY_M) == GLFW_PRESS)
            {
                menuopen = true;
            }
        }

        game.HandleBufferAndEvent();
        dt = game.Step();
    }

    for(int i = 0; i < meshes.size(); i++){
        delete meshes[i];
        free(listinfo[i]);
    }


    return 0;
}