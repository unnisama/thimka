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


    uint32_t indexes[24] = {
        0, 1, 2,
        2, 3, 0,
    };

    float positions[] = {

    };


    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    

    VertexBuffer vb(vertices, sizeof(float) * 180, GL_STREAM_DRAW);

    ArrayLayout aly;
    aly.AddFloat(3);
    aly.AddFloat(2);

    VertexArray va(&vb, &aly);
    //IndexBuffer ib(indexes, 6);
    Texture texture("../assets/textures/oak.png");
    texture.Bind(0);

    va.Enable();

    Shader shader("../assets/shaders/fragment.glsl", "../assets/shaders/vertex.glsl");

    if(!shader.GetStatus()){
        printf("Shader failed!\n");
        exit(0);
    }

    shader.Use();

    Camera camera(WIDTH, HEIGHT, &shader);

    camera.SetUniforms();

    GLuint time_ = shader.GetUniformLocation("time");
    GLuint freqid = shader.GetUniformLocation("freq");
    shader.SetUniform1i("u_texture", 0);

    GLuint deltatime_ = shader.GetUniformLocation("deltatime");

    bool menuopen = true;

    float freq = 1.0f;
    GLDEBUGCALL(glUniform1f(freqid, freq));

    float dt = game.Step();

    
    
    while (!game.ShouldClose())
    {
        auto t = glm::vec3(0.0f);   
        GLDEBUGCALL(glClearColor(0.094f, 0.094f, 0.094f, 1.0f));
        GLDEBUGCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        GLDEBUGCALL(glUniform1f(deltatime_, dt));
        GLDEBUGCALL(glUniform1f(time_, game.GetTime()));

        renderer.Draw(va, 180, shader);

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

        ImGui::End();

        gui.EndFrame();
        game.HandleBufferAndEvent();
        dt = game.Step();
    }

    return 0;
}