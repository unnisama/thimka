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
    game.EnableDebug();

    Gui gui(game.GetWindow(), &game);

    Renderer renderer;

    float positions[] = {
        0.5f, 0.5f, 0.5f,
        1.0f, 1.0f,

        -0.5f,
        0.5f,
        0.5f,
        0.0f,
        1.0f,

        -0.5f,
        -0.5f,
        0.5f,
        0.0f,
        0.0f,

        0.5f,
        -0.5f,
        0.5f,
        1.0f,
        0.0f,

        0.5f,
        0.5f,
        -0.5f,
        0.0f,
        1.0f,

        -0.5f,
        0.5f,
        -0.5f,
        1.0f,
        1.0f,

        -0.5f,
        -0.5f,
        -0.5f,
        1.0f,
        0.0f,

        0.5f,
        -0.5f,
        -0.5f,
        0.0f,
        0.0f,

        -0.5f,
        0.5f,
        0.5f,
        1.0f,
        0.0f,

        0.5f,
        0.5f,
        0.5f,
        0.0f,
        0.0f,

        -0.5f,
        -0.5f,
        0.5f,
        1.0f,
        1.0f,

        0.5f,
        -0.5f,
        0.5f,
        0.0f,
        1.0f,
    };


    std::vector<Mesh_Vertex> verts;
    std::vector<Mesh_Triangle> tris = {
        {0, 1, 2},
        {2, 3, 0},

        {4, 5, 6},
        {6, 7, 4},

        {1, 5, 6},
        {6, 2, 1},

        {0, 4, 7},
        {7, 3, 0},

        {4, 5, 8},
        {8, 9, 4},

        {6, 7, 11},
        {11, 10, 6}
    };

    Mesh_Vertex* mvp = (Mesh_Vertex*)&positions;

    for(int i = 0; i < 12; i++){
        verts.push_back(mvp[i]);
    }


    

    Shader shader("../assets/shaders/fragment.glsl", "../assets/shaders/vertex.glsl");

    if(!shader.GetStatus()){
        printf("Shader failed!\n");
        exit(0);
    }

    shader.Use();

    Mesh mesh(verts, tris);

    Renderer render;

    Texture texture("../assets/textures/oak.png", 0);
    texture.Bind(0);

    shader.SetUniform1i("u_texture", 0);

    float dt = 0.0f;

    Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 0.0f), 45.0f, 0.01f, 100.0f, shader);
    bool menuopen = true;

    glm::mat4 model(1.0f);

    shader.SetMat4f("umodel", model);

    while (!game.ShouldClose())
    {
        ImVec2 windSize = {0.0f, 0.0f};
        GLDEBUGCALL(glClearColor(0.094f, 0.094f, 0.094f, 1.0f));
        GLDEBUGCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        mesh.Draw(render, shader);

        gui.NewFrame();

        if (menuopen == true)
        {
            ImGui::SetNextWindowPos({0, 0});
            ImGui::SetNextWindowSize({-1, -1});
            ImGui::Begin("Setting", &menuopen, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

            {
                ImGui::Text("UpTime: %.3f", game.GetTime());
                ImGui::Text("FTime: %.3f", dt);
                ImGui::Text("FPS: %.f", 1.0f / dt);

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

    return 0;
}