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
#include "storagebuffer.h"


int WIDTH = 640;
int HEIGHT = 480;

struct Matrix4 {
    float data[16];
};

bool isEnabled(int x, int y, int z){
    return true;
}

int SetupData(std::vector<Matrix4> &meshes, int blocksize){
    int mesh_count = 0;
    for (int i = 0; i < blocksize; i++)
    {
        for (int j = 0; j < blocksize; j++)
        {
            for (int k = 0; k < blocksize; k++)
            {
                if(isEnabled(i, j, k) == true){
                    
                    glm::mat4 mat(1.0f);
                    mat = glm::translate(mat, glm::vec3(i,j,k));
                    Matrix4 m4;
                    m4.data[0] = mat[0][0];
                    m4.data[1] = mat[0][1];
                    m4.data[2] = mat[0][2];
                    m4.data[3] = mat[0][3];
                    m4.data[4] = mat[1][0];
                    m4.data[5] = mat[1][1];
                    m4.data[6] = mat[1][2];
                    m4.data[7] = mat[1][3];
                    m4.data[8] = mat[2][0];
                    m4.data[9] = mat[2][1];
                    m4.data[10] = mat[2][2];
                    m4.data[11] = mat[2][3];
                    m4.data[12] = mat[3][0];
                    m4.data[13] = mat[3][1];
                    m4.data[14] = mat[3][2];
                    m4.data[15] = mat[3][3];


                    meshes.push_back(m4);
                    mesh_count += 1;
                }
            }
        }
    }
    return mesh_count;
}

int main(void)
{
    Game game(WIDTH, HEIGHT, "Start");
    //game.EnableDebug();

    Gui gui(game.GetWindow(), &game);

    Renderer renderer;

    std::vector<Matrix4> meshes;
    std::vector<char *> listinfo;

    int mesh_count = SetupData(meshes, 30);

    StorageBuffer sb(meshes.data(), meshes.size()*sizeof(Matrix4), GL_STREAM_READ, 3);

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

    // glm::vec3 t(0.0f);
    // int cindex = -1;

    
    shader.SetUniform1i("width", texture.getWidth());
    shader.SetUniform1i("height", texture.getHeight());
    int radius = 5;
    Mesh cube(MeshPrimitive::Cube);

    while (!game.ShouldClose())
    {
        ImVec2 windSize = {0.0f, 0.0f};
        GLDEBUGCALL(glClearColor(0.094f, 0.094f, 0.094f, 1.0f));
        GLDEBUGCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        cube.Draw(renderer, shader, mesh_count);

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

                // if(ImGui::DragInt("Radius", &radius, 0.05f, 5, 12)){
                //     shader.SetUniform1i("radius", radius);
                // }

                // ImGui::Separator();

                // ImGui::DragFloat3("Position", glm::value_ptr(t), 0.01f, -20.0f, 20.0f);

                // if(ImGui::Button("Add Cube")){
                //     mesh_count += 1;
                //     Mesh *mesh = new Mesh(MeshPrimitive::Cube);
                //     mesh->Translate(t);
                //     meshes.push_back(mesh);
                //     char *d = (char *)malloc(10);
                //     sprintf(d, "%d", mesh_count);
                //     listinfo.push_back(d);
                // }

                
                // if (meshes.size() > 0)
                // {
                //     ImGui::Separator();
                //     ImGui::ListBox("##objects", &cindex, listinfo.data(), listinfo.size());

                //     if(cindex != -1){
                //         if (ImGui::Button("Remove Cube"))
                //         {
                //             listinfo.erase(listinfo.begin() + cindex);
                //             meshes.erase(meshes.begin() + cindex);
                //         }
                //     }
                   
                // }

                windSize = ImGui::GetWindowSize();
            }

            ImGui::End();
        }

        gui.EndFrame();
        if (menuopen == false)
        {
            if (glfwGetKey(game.GetWindow(), GLFW_KEY_M) == GLFW_PRESS)
            {
                menuopen = true;
            }
        }

        camera.Inputs(Game::GetWindow(), windSize, dt);

        

        game.HandleBufferAndEvent();
        dt = game.Step();
    }

    // for(int i = 0; i < meshes.size(); i++){
    //     delete meshes[i];
    // }
    // for (int i = 0; i < listinfo.size(); i++)
    // {
    //     free(listinfo[i]);
    // }

    return 0;
}