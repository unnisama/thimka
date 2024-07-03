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
         0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 0.0f, 1.0f,

    };

    uint32_t indexes[36] = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        1, 5, 6,
        6, 2, 1,

        0, 4, 7,
        7, 3, 0,

        4, 5, 8,
        8, 9, 4,

        6, 7, 11,
        11, 10, 6
    };
    std::default_random_engine dre;
    std::uniform_real_distribution<float> dist(-4.0, 4.0);

    glm::vec3 cubeposs[5] = {
        glm::vec3(dist(dre), dist(dre), dist(dre)),
        glm::vec3(dist(dre), dist(dre), dist(dre)),
        glm::vec3(dist(dre), dist(dre), dist(dre)),
        glm::vec3(dist(dre), dist(dre), dist(dre)),
        glm::vec3(dist(dre), dist(dre), dist(dre)),
    };

    VertexBuffer vb(positions, sizeof(float) * 60, GL_STREAM_DRAW);

    ArrayLayout aly;
    aly.AddFloat(3);
    aly.AddFloat(2);

    Texture texture("../assets/textures/imas.png", 0);
    texture.Bind(0);


    VertexArray va(&vb, &aly);
    IndexBuffer ib(indexes, 36, GL_STREAM_DRAW);
  
    va.Enable();

    Shader shader("../assets/shaders/fragment.glsl", "../assets/shaders/vertex.glsl");

    if(!shader.GetStatus()){
        printf("Shader failed!\n");
        exit(0);
    }

    shader.Use();

    Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, 0.0f), 45.0f, 0.01f, 100.0f, shader);

    GLuint time_ = shader.GetUniformLocation("time");
    GLuint freqid = shader.GetUniformLocation("freq");
    shader.SetUniform1f("width", (float)texture.getWidth());
    shader.SetUniform1f("height", (float)texture.getHeight());
    shader.SetUniform1i("u_texture", 0);
    // shader.SetUniform1i("u_textureblur", 1);

    GLuint deltatime_ = shader.GetUniformLocation("deltatime");

    bool menuopen = false;

    float freq = 0.05f;
    GLDEBUGCALL(glUniform1f(freqid, freq));

    float dt = game.Step();
    glm::mat4 model(1.0f);
    float scale = 1.0f;
    shader.SetUniform1f("scale", scale);

    int radius = 3;

    

    while (!game.ShouldClose())
    {
        ImVec2 windSize = {0.0f, 0.0f};
        GLDEBUGCALL(glClearColor(0.094f, 0.094f, 0.094f, 1.0f));
        GLDEBUGCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        GLDEBUGCALL(glUniform1f(deltatime_, dt));
        GLDEBUGCALL(glUniform1f(time_, game.GetTime()));

        model = glm::rotate(model, freq*dt, glm::vec3(0.0f, 1.0f, 0.0f));

        shader.SetMat4f("umodel", model);
        renderer.Draw(va, ib, shader);

        for(int i = 0; i < 5; i++){
            auto nmodel = glm::translate(glm::mat4(1.0f), cubeposs[i]) * model;
            shader.SetMat4f("umodel", nmodel);
            renderer.Draw(va, ib, shader);
        }

        gui.NewFrame();

        if(menuopen == true){
            ImGui::SetNextWindowPos({0, 0});
            ImGui::SetNextWindowSize({-1, -1});
            ImGui::Begin("Setting", &menuopen, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
            if (ImGui::DragFloat("Freq", &freq, 0.001f, 0.0f, M_PI*2.0f))
            {
                GLDEBUGCALL(glUniform1f(freqid, freq));
            }

            ImGui::Text("UpTime: %.3f", game.GetTime());
            ImGui::Text("FTime: %.3f", dt);
            ImGui::Text("FPS: %.f", 1.0f / dt);

            windSize = ImGui::GetWindowSize();

            

            if (ImGui::DragFloat("Scale", &scale, 0.03, 0.1f, 2.0f))
            {
                shader.SetUniform1f("scale", scale);
            }

            if (ImGui::DragInt("Radius", &radius, 0.03f, 3.0f, 20.0f))
            {
                shader.SetUniform1i("radius", radius);
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