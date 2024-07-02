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
#include "camera2.h"

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
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    };

    uint32_t indexes[36] = {
        8, 11, 4,
        4, 7, 8,

        2, 6, 5,
        5, 9, 2,

        10, 12, 0,
        0, 2, 10,

        3, 4, 14,
        14, 13, 3,

        0, 16, 6,
        6, 2, 0,

        7, 4, 3,
        3, 1, 15
    };

    VertexBuffer vb(positions, sizeof(float) * 180, GL_STREAM_DRAW);

    ArrayLayout aly;
    aly.AddFloat(3);
    aly.AddFloat(2);

    VertexArray va(&vb, &aly);
    IndexBuffer ib(indexes, 36);
    Texture texture("../assets/textures/imas.png");
    texture.Bind(0);

    va.Enable();

    Shader shader("../assets/shaders/fragment.glsl", "../assets/shaders/vertex.glsl");

    if(!shader.GetStatus()){
        printf("Shader failed!\n");
        exit(0);
    }

    shader.Use();

    Camera2 camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 10.0f), 45.0f, 0.01f, 100.0f, shader);

    GLuint time_ = shader.GetUniformLocation("time");
    GLuint freqid = shader.GetUniformLocation("freq");
    shader.SetUniform1i("u_texture", 0);

    GLuint deltatime_ = shader.GetUniformLocation("deltatime");

    bool menuopen = true;

    float freq = 0.0f;
    GLDEBUGCALL(glUniform1f(freqid, freq));

    float dt = game.Step();

    glm::mat4 model(1.0f);


    while (!game.ShouldClose())
    {
        GLDEBUGCALL(glClearColor(0.094f, 0.094f, 0.094f, 1.0f));
        GLDEBUGCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        GLDEBUGCALL(glUniform1f(deltatime_, dt));
        GLDEBUGCALL(glUniform1f(time_, game.GetTime()));

        renderer.Draw(va, ib, shader);

        gui.NewFrame();

        ImGui::SetNextWindowPos({0, 0});
        ImGui::SetNextWindowSize({-1, -1});
        ImGui::Begin("Setting", &menuopen, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        if (ImGui::SliderFloat("Freq", &freq, 0.0f, 6.0f))
        {
            GLDEBUGCALL(glUniform1f(freqid, freq));
        }

        ImGui::Text("UpTime: %.3f", game.GetTime());
        ImGui::Text("FTime: %.3f", dt);
        ImGui::Text("FPS: %.f", 1.0f / dt);

        camera.Inputs(Game::GetWindow(), ImGui::GetWindowSize());

        model = glm::rotate(model, freq*dt, glm::vec3(1.0f, 1.0f, 0.0f));

        shader.SetMat4f("umodel", model);
        ImGui::End();

        gui.EndFrame();
        game.HandleBufferAndEvent();
        dt = game.Step();
    }

    return 0;
}